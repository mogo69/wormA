#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

#include <string>
#include <netinet/in.h>
#include "TCPStream.h"

using namespace std;

class TCPAcceptor
{
    int    m_lsd;
    size_t    m_port;
    string m_address;
    bool   m_listening;

  public:
    TCPAcceptor(size_t port, const char* address="");
    ~TCPAcceptor();

    int        start();
    TCPStream* accept();

  private:
    TCPAcceptor() {}
};

#endif
