#ifndef _WAR_SERVER_H_
#define _WAR_SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

//#include "Cripto.h"
#include "Thread.h"
#include "ClientAttenderBuilder.h"
#include "NetworkException.h"
#include "ClientPoller.h"

#define SOCKET int

/**
 * Defines an operative system server socket.
 * @see ClientSocket
 */
class Server : public DaVinciWars::Thread
{
private:
        /** Default constructor */
        Server();

public:

        static Server *getInstancePtr();

        static Server &getInstance();

        void Listen(unsigned int port);

        void run();

        /**
         * Send to every client.
         * @param data Data to be sent.
         */
        void sendMulticast(std::wstring data);


        /**
         * Sets the clientAttender Builder
         * @param blder new Builder to be set.
         */
        inline void setClientBuilder(ClientAttenderBuilder *blder) { mBuilder = blder;}

        static void destroy();


        /** Default destructor */
        virtual ~Server();



private:
  SOCKET m_sock;
  ClientAttenderBuilder *mBuilder;
  ClientPoller          *mPoller;

  struct sockaddr_in     mAddress;
  static Server*    smInstance;

};

#endif // _WAR_SERVER_H_

