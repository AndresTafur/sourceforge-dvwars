#ifndef _ABSTRACTCLIENT_H
#define _ABSTRACTCLIENT_H


#include <util/Storable.h>
#include "ClientListener.h"


class AbstractClient : public Storable
{
    public:


        virtual void Connect(std::string address, unsigned int port) = 0;

        virtual void Send(std::string data) = 0;


        virtual void addListener(ClientListener *obj) = 0;

        virtual void removeListener(ClientListener *obj) = 0;


    private:
};

#endif // _ABSTRACTCLIENT_H
