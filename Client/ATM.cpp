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

#include "../Responses/Response.h"
#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"
//#include "../Requests/LogoutRequest.h"

BOOST_CLASS_EXPORT_GUID(Request, "request")
BOOST_CLASS_EXPORT_GUID(LoginRequest, "login_request")

ATM::ATM():
    _sesionKey(""),
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

ATM& ATM::getInstance()
{
    static ATM instance;
    return instance;
}

bool ATM::canWithdraw(size_t sum)
{
    _innerCash->canWithdraw(sum);
}
bool ATM::withdraw(const size_t sum, const bool useCreditMoney)
{
    _innerCash->withdraw(sum);
}

void ATM::sendRequest(const boost::shared_ptr<Request>& req, boost::asio::ip::tcp::socket& socket)
{
    boost::asio::streambuf buf;
    std::ostream os( &buf );
    boost::archive::text_oarchive ar( os );
    ar & boost::serialization::make_nvp("item", req);

    const size_t header = buf.size();

    // send header and buffer using scatter
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back( boost::asio::buffer(&header, sizeof(header)) );
    buffers.push_back( buf.data() );
    boost::asio::write(socket, buffers);
}

void ATM::receiveResponse(Response& resp, boost::asio::ip::tcp::socket& socket)
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

//==================================================================================
bool ATM::logIn(const string cardN, const unsigned PIN)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    socket.connect(
            boost::asio::ip::tcp::endpoint(
                boost::asio::ip::address::from_string( "127.0.0.1" ),
                9999
                )
            );
    sendRequest(boost::make_shared<LoginRequest>(cardN, PIN), socket);
    Response resp;
    receiveResponse(resp, socket);
    socket.close();
    cout<<resp.getMessage()<<endl;
    return resp.wasSuccessful();
}
/*
bool ATM::logOut()
{

    LogoutRequest req(_sessionKey);
    _stream -> send(getSerializedString(req).c_str(), getSerializedString(req).size());
    char answer[255];
    size_t len = _stream->receive(answer, sizeof(answer));
    answer[len] = '\0';

    ss<<answer;

    Response res;
    load(res);

    cout<<boolalpha;
    cout<<"Successful: "<<res.wasSuccessful()<<endl;
    cout<<"Message: "<<res.getMessage()<<endl;

    if(res.wasSuccessful()) _sessionKey = "";w
    return res.wasSuccessful();
}

*/
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
