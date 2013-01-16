#include "Client.h"
#include <stdio.h>
#include <fcntl.h>

#include "NetworkException.h"

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


    std::string Client::Receive()
    {
         char buffer[1024];
         std::string data;
         size_t num;

                    fcntl(m_sock, F_SETFL, O_NONBLOCK);

                    if( (num = recv(m_sock, buffer, 1024, MSG_WAITALL) ) == 0)
                    {
                        throw NetworkException("\nSocket has been unexpectly shuted down");
                    }
                    else
                        data = buffer; //ensuring that it is an std::string

                    return data.substr(0,num);
   }


    void Client::Send(std::wstring data)
    {
        send(m_sock,data.c_str(),500,MSG_CONFIRM);
    }


    void Client::closeSocket()
    {
        close(m_sock);
    }


Client::~Client()
{
    //dtor
}
