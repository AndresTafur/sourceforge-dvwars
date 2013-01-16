#ifndef _CLIENTPOLLER_H_
#define _CLIENTPOLLER_H_

#include "Thread.h"

#include "ClientAttenderBuilder.h"

class ClientPoller : public DaVinciWars::Thread
{
    public:
        ClientPoller();

        void run();

        virtual ~ClientPoller();


        inline std::vector<ClientAttender*> getClients() { return mClients; }


        inline void addClient(ClientAttender* attender) { mClients.push_back(attender);}

private:
std::vector<ClientAttender*> mClients;
unsigned int mTimeOut;


};

#endif // _CLIENTPOLLER_H_
