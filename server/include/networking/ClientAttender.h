#ifndef _CLIENTATTENDER_H_
#define _CLIENTATTENDER_H_

#include "Client.h"
#include "security/Cripto.h"

#include "util/Thread.h"
#include "RequestManager.h"

/**
 * Handles threaded client attention
 */
class ClientAttender : public DaVinciWars::Thread
{
public:

        virtual void attend(std::string data) = 0;

        inline  void setClient(Client *clt) { m_client = clt;}

        virtual inline Client* getClient() { return m_client;}

        virtual void onClose() = 0;

        /**
         * Adds new request handlers to be notified.
         * @param list new request handlers.
         */
        void addRequestCtrl(std::map<std::string,RequestManager*> list);

        /**
         * Adds new request handlers to be notified.
         * @param proto Call this handler when proto opcode has arrived.
         * @param obj    Handler.
         */
        void addRequestCtrl(std::string proto, RequestManager *obj);


        /**
         * remove Request handlers based on protocol id.
         * @param proto protocol to be removed.
         */
        void removeRequestCtrl(std::string proto);



        virtual ~ClientAttender();

protected:

        void run();

protected:
Client *m_client;
std::map<std::string,RequestManager*> m_controllers;
};

#endif // _CLIENTATTENDER_H_
