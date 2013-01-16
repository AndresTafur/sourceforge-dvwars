#ifndef _CLIENTATTENDER_H_
#define _CLIENTATTENDER_H_

#include "Client.h"
//#include "security/Cripto.h"

#include "util/Thread.h"
#include "RequestManager.h"
#include "NetworkException.h"

/**
 * Handles threaded client attention
 */
class ClientAttender
{
public:


        virtual void attend(std::string data) = 0;

        virtual void onClose() = 0;

        virtual void handleError(NetworkException ex) = 0;


        inline  void setClient(Client *clt) { m_client = clt;}

        virtual inline Client* getClient() { return m_client;}

        virtual ~ClientAttender() {};

protected:
Client *m_client;

};

#endif // _CLIENTATTENDER_H_
