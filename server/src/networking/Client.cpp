#include "Client.h"
#include <stdio.h>

Client::Client()
{

}

Client::Client(SOCKET sock)
{
    m_sock = sock;
}

Client::Client(SOCKET sock, struct sockaddr address)
{
    m_sock = sock;
    m_address = address;
}


    void Client::lock()
    {
            mMutex.lock();
    }


    void Client::unlock()
    {
        mMutex.unlock();
    }


    void Client::Send(std::string data)
    {
        send(m_sock,data.c_str(),500,MSG_CONFIRM);
    }



Client::~Client()
{
    //dtor
}
