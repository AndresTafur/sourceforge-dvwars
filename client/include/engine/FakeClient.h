#ifndef _FakeClient_
#define _FakeClient_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Client.h"
#include <util/ConfigReader.h>

/**
 * Fakes a connection
 */
class FakeClient : public AbstractClient, protected DaVinciWars::Thread
{
public:
        /** Default constructor */
        FakeClient();


        void Connect(std::string address, unsigned int port);

        void run();

        void Send(std::string data);

        inline void addListener(ClientListener *obj) {  mAnttenders.push_back(obj); }

        inline void removeListener(ClientListener *obj) {}

        static void destroy();

        /** Default destructor */
        virtual ~FakeClient();

protected:
        std::vector<std::string> parseParams(std::string data);
        std::vector <ClientListener*> mAnttenders;
        ConfigReader  mReader;
        std::string mCurrentState;
        std::string mData;
        volatile bool mSleep;
};

#endif // _WAR_SERVER_H_

