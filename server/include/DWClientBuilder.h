#ifndef _WS_DWCLIENTBUILDER_H_
#define _WS_DWCLIENTBUILDER_H_

#include <map>

#include "DWClientAttender.h"
#include "ClientAttenderBuilder.h"


/**
 * Concrete game AttenderBuilder
 * @see ClientAttenderBuilder
 */
class DWClientBuilder  : public ClientAttenderBuilder
{
private:

        /** Default constructor */
        DWClientBuilder();

public:

        static DWClientBuilder* getInstancePtr();

        ClientAttender* getClientAttender();


        void addRequestCtrl(std::string proto, RequestManager *obj);

        /** Default destructor */
        ~DWClientBuilder();

private:
std::map<std::string,RequestManager*> m_reqCtrl;
static DWClientBuilder *sm_instance;
};

#endif // _WS_CLIENTSBUILDER_H_
