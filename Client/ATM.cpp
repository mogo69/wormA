#define NDEBUG

#include "ATM.h"

#include <iostream>
using namespace std;

#include <boost/asio.hpp>

#include <sstream>
std::stringstream ss;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"


void load(Response& res)
{
    text_iarchive ia(ss);
    res.getFrom(ia);
}

string toString(int x)
{
    ss.str("");
    ss<<x;
    string res = ss.str();
    ss.str("");
    return res;
}

//This will be removed after moving to boost sockets
string getSerializedString(const Request& req)
{

    ss.str("");
    text_oarchive oa(ss);
    req.putInto(oa);
    string res = ss.str();
    ss.str("");
    return res;
}


ATM::ATM():
    _sesionKey(""),
    _innerCash(new InnerCash(50000))
 //   _connector(new TCPConnector()),
  //  _stream(_connector->connect("localhost", 9999))
{
#ifndef NDEBUG
    cout << "ATM created." << endl;
    if (_stream) cout<<"Connection to server established"<<endl;
#endif
}

ATM::~ATM()
{
#ifndef NDEBUG
    cout << "ATM deleated." << endl;
#endif
    delete _innerCash;
    delete _connector;
}

ATM& ATM::getInstance()
{
    static ATM instance;
    return instance;
}

//=========================Inner Cash===============================================
ATM::InnerCash::InnerCash(double cashAmount):
    _cashAmount(cashAmount), _pockets(new Pocket[4])
{
#ifndef NDEBUG
    cout << _pockets->_quantity << endl;
#endif

}
ATM::InnerCash::~InnerCash()
{
    delete [] _pockets;
}

bool ATM::InnerCash::canWithdraw(const double sum)
{
    //Temprorary solution
    return (_cashAmount <= sum);
}
void ATM::InnerCash::withdraw(const double sum)
{
    //Temprorary solution
    _cashAmount -= sum;
}
//==================================================================================
bool ATM::logIn(const string cardN, const size_t PIN)
{
 /*   LoginRequest req(cardN, toString(PIN));
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
*/
//  If something was received
    LoginRequest req(cardN, toString(PIN));
    boost::asio::streambuf buf;
    std::ostream os( &buf );
    boost::archive::text_oarchive ar( os );
    ar & req;

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket( io_service );
    const short port = 9999;
    socket.connect(
            boost::asio::ip::tcp::endpoint(
                boost::asio::ip::address::from_string( "127.0.0.1" ),
                port
                )
            );

    const size_t header = buf.size();
    std::cout << "buffer size " << header << " bytes" << std::endl;

    // send header and buffer using scatter
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back( boost::asio::buffer(&header, sizeof(header)) );
    buffers.push_back( buf.data() );
    const size_t rc = boost::asio::write(
            socket,
            buffers
            );
    std::cout << "wrote " << rc << " bytes" << std::endl;;
    return rc > 1;
}

