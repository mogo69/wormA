# wormA

#include <iostream>
using namespace std;
#include <string>
#include "TCPConnector.h"
#include "TCPAcceptor.h"


class ChangePin
{
private: 
	string _newPin;
	string _cardNumber;
	string _localHost;
	string _port;
	string _message;
	char line[256];
public:
	ChangePin(const string& newPin, const string& cardNumber, const string& localHost, const string& port): _newPin(newPin), _cardNumber(cardNumber), _localHost(localHost), _port(port){};
	~ChangePin();
	bool execute()
	{
		TCPConnector* connector = new TCPConnector();
		TCPStream* stream = connector->connect(_localhost, _port);
		if (stream) {
        message = "Change" + _newPin + "CardNumber" + _cardNumber;
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
		return len;
		}

	}
};
#endif
