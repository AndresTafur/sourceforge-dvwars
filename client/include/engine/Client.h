#ifndef _Client_
#define _Client_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


#include "Thread.h"
#include "AbstractClient.h"


#define SOCKET int

/**
 * Handles a OS specific client socket.
 */
class Client : public DaVinciWars::Thread, public AbstractClient
{
public:
        /** Default constructor */
        Client();

        void Connect(std::string address, unsigned int port);

        void run();

        void Send(std::string data);

        inline void addListener(ClientListener *obj) {  m_attenders.push_back(obj); }

        void removeListener(ClientListener *obj);

        /** Default destructor */
        virtual ~Client();

protected:

        std::vector<std::string> parseParams(std::string data);



private:
  SOCKET m_sock;
  struct sockaddr_in m_address;
  bool m_running;
  std::vector<ClientListener*> m_attenders;
};

#endif // _WAR_SERVER_H_
