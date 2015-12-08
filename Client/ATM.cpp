//#define NDEBUG

#include "ATM.h"

#include <iostream>
using namespace std;

#include <boost/asio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/noncopyable.hpp>
#include <boost/make_shared.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <sstream>
std::stringstream ss;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"
#include "../Requests/LogoutRequest.h"
#include "../Requests/GetBalanceRequest.h"
#include "../Requests/WithdrawRequest.h"
#include "../Requests/GetAdvertRequest.h"
#include "../Requests/GetDataAboutRequest.h"
#include "../Requests/SendMoneyToRequest.h"

#include "../Responses/Response.h"

BOOST_CLASS_EXPORT_GUID(Request, "request")
BOOST_CLASS_EXPORT_GUID(LoginRequest, "login_request")
BOOST_CLASS_EXPORT_GUID(LogoutRequest, "logout_request")
BOOST_CLASS_EXPORT_GUID(GetBalanceRequest, "get_balance_request")
BOOST_CLASS_EXPORT_GUID(WithdrawRequest, "withdraw_request")
BOOST_CLASS_EXPORT_GUID(GetAdvertRequest, "get_advert_request")
BOOST_CLASS_EXPORT_GUID(GetDataAboutRequest, "get_data_about_request")
BOOST_CLASS_EXPORT_GUID(SendMoneyToRequest, "send_money_to_request")

ATM::ATM(const string& bankHost, const unsigned bankPort):
    _bankHost(bankHost),
    _bankPort(bankPort),
    _sessionKey(""),
    _innerCash(new InnerCash())
{
#ifndef NDEBUG
    cout << "ATM created." << endl;
#endif
}

ATM::~ATM()
{
#ifndef NDEBUG
    cout << "ATM deleated." << endl;
#endif
    delete _innerCash;
}

ATM& ATM::getInstance(const string& bankHost, const unsigned bankPort)
{
    static ATM instance(bankHost, bankPort);
    return instance;
}

bool ATM::canWithdraw(size_t sum)
{
    return (sum < getBalance() && _innerCash->canWithdraw(sum));
}
void connect(boost::asio::ip::tcp::socket& socket)
{

}

bool ATM::withdraw(const size_t sum, const bool useCreditMoney)
{
    Response resp;
    processRequest(boost::make_shared<WithdrawRequest>(_sessionKey, sum, useCreditMoney), resp);
    if(resp.wasSuccessful())
    {
        _innerCash->withdraw(sum);
    }
    return resp.wasSuccessful();
}

bool ATM::logIn(const string cardN, const unsigned PIN)
{
    Response resp;
    processRequest(boost::make_shared<LoginRequest>(cardN, PIN), resp);
    if(resp.wasSuccessful())
    {
        _sessionKey = resp.getMessage();
    }
    return resp.wasSuccessful();
}

double ATM::getBalance()
{
    Response resp;
    processRequest(boost::make_shared<GetBalanceRequest>(_sessionKey), resp);
    return resp.wasSuccessful() ? atof(resp.getMessage().c_str()) : -1;
}

bool ATM::logOut()
{
    Response resp;
    processRequest(boost::make_shared<LogoutRequest>(_sessionKey), resp);
    if(resp.wasSuccessful())
    {
        _sessionKey = "";
    }
    return resp.wasSuccessful();
}

string ATM::getAdvert()
{
    Response resp;
    processRequest(boost::make_shared<GetAdvertRequest>(), resp);
    return resp.getMessage();
}
string ATM::getDataAbout(const string cardN)
{
    Response resp;
    processRequest(boost::make_shared<GetDataAboutRequest>(_sessionKey, cardN), resp);
    return resp.getMessage();
}

bool ATM::sendMoneyTo(const double sum, const string cardN)
{
    Response resp;
    processRequest(boost::make_shared<SendMoneyToRequest>(_sessionKey,sum, cardN), resp);
    return resp.wasSuccessful();
}

void sendRequest(const boost::shared_ptr<Request>& req, boost::asio::ip::tcp::socket& socket)
{
    boost::asio::streambuf buf;
    std::ostream os( &buf );
    boost::archive::text_oarchive ar( os );
    ar & boost::serialization::make_nvp("item", req);

    const size_t header = buf.size();
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back( boost::asio::buffer(&header, sizeof(header)) );
    buffers.push_back( buf.data() );
    boost::asio::write(socket, buffers);
}

void receiveResponse(Response& resp, boost::asio::ip::tcp::socket& socket)
{
    size_t header;
    boost::asio::read(socket, boost::asio::buffer(&header, sizeof(header)));

    boost::asio::streambuf buf;
    boost::asio::read(socket, buf.prepare( header ));
    buf.commit( header );

    istream is( &buf );
    boost::archive::text_iarchive ar( is );

    ar & resp;
}

void ATM::processRequest(const boost::shared_ptr<Request>& req, Response& resp)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(_bankHost), _bankPort));
    sendRequest(req, socket);
    receiveResponse(resp, socket);
    socket.close();
}

//=========================Inner Cash===============================================

ATM::InnerCash::InnerCash(const array<size_t,5> values,
                          const array<size_t,5> ammounts):
    _numOfPockets(5),
    _pockets(new Pocket[_numOfPockets])
{
#ifndef NDEBUG
#endif
    for(size_t i = 0; i < _numOfPockets; i++)
    {
        _pockets[i]._value = values[i];
        _pockets[i]._ammount = ammounts[i];
    }
}
ATM::InnerCash::~InnerCash()
{
    delete [] _pockets;
}

bool ATM::InnerCash::canWithdraw(const size_t sum)
{
    vector<array<size_t,5>> sols = findSolutions(sum);
    /*#ifndef NDEBUG
    cout <<"InnerCash canWithdraw " <<sum<<":" << endl;
    for (size_t i = 0; i < sols.size(); i++)
    {
        //cout<< "size = " << sols[i].size() << endl;
        for (size_t j = 0; j < sols[i].size(); j++)
        {
        cout<< sols[i][j]<<',';
        }
        cout << endl;
    }
    #endif*/
    return !sols.empty();

}
bool ATM::InnerCash::withdraw(const size_t sum)
{
    array<size_t,5> combination = chooseBestCombination(findSolutions(sum));
    for(size_t i = 0; i < _numOfPockets; i++)
    {
        _pockets[i]._ammount -= combination[i];
    }
    #ifndef NDEBUG
    cout << "===Banknotes in AMT: " << endl;
    for(size_t i = 0; i < _numOfPockets; i++)
    {
        cout << _pockets[i]._value << " = " << _pockets[i]._ammount << endl;
    }
    cout << "=====================" << endl;
    #endif // NDEBUG
    return true;
}
vector<array<size_t,5>> ATM::InnerCash::findSolutions(const size_t sum, size_t position, array<size_t,5> combination)
{
        vector<array<size_t,5>> solutions;
		size_t value = calculate(combination);
		if (value < sum) {
			for (size_t i = position; i < _numOfPockets; i++)
			{
				if (_pockets[i]._ammount > combination[i])
				{
					array<size_t,5> newCombination = combination;
					newCombination[i]++;
					vector<array<size_t,5>> newSolutions = findSolutions(sum, i, newCombination);
					if (!newSolutions.empty())
					{
						solutions.insert( solutions.end(), newSolutions.begin(), newSolutions.end() );
					}
				}
			}
		} else if (value == sum) {
			solutions.push_back(combination);
		}
		return solutions;
}
size_t ATM::InnerCash::calculate(const array<size_t,5> &combination) {
		size_t sum = 0;
		for (size_t i = 0; i < combination.size(); i++)
		{
			sum += _pockets[i]._value * combination[i];
		}
		return sum;
}
array<size_t,5> ATM::InnerCash::chooseBestCombination(const vector<array<size_t,5>> &solutions)
{
    size_t bestCombination = 0;
    for(size_t i = 1; i < solutions.size(); i++)
    {
        if(sum(solutions[i]) < sum(solutions[bestCombination])) bestCombination = i;
    }
    return solutions[bestCombination];
}
size_t ATM::InnerCash::sum(const array<size_t,5> &combination)
{
    size_t result = 0;
    for(size_t i = 0; i < combination.size(); i++)
    {
        result += combination[i];
    }
    return result;
}
//==================================================================================
