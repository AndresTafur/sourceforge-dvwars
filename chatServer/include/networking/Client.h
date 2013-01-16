#ifndef _DVWARS_CLIENT_H__
#define _DVWARS_CLIENT_H__

#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <boost/thread.hpp>

#include <ClientListener.h>

#define SOCKET int


/**
 * Handles a os dependant client socket.
 */
class Client
{
public:


        /** Default constructor */
        Client();

        Client(SOCKET sock);

        Client(SOCKET sock, struct sockaddr address);


        inline void   setSocket(SOCKET sock) { m_sock = sock;}

        inline SOCKET getSocket() { return m_sock;}

        inline void   setAddress(struct sockaddr addr) { m_address = addr;}

        inline struct sockaddr getAddress() { return m_address;}



        void lock();

        void unlock();

        void Send(std::wstring data);

        std::string Receive();

        void closeSocket();

        /** Default destructor */
        virtual ~Client();


private:
SOCKET m_sock;
boost::mutex    mMutex;
struct sockaddr m_address;
std::vector<ClientListener*> mClients;
};

#endif
