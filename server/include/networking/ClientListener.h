#ifndef _CLIENTLISTENER_H_
#define _CLIENTLISTENER_H_


class ClientListener
{
    public:

        virtual void onConnectionDown() = 0;

    private:
};

#endif // _CLIENTLISTENER_H_
