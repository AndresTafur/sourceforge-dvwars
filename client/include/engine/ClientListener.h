#ifndef CLIENTLISTENER_H
#define CLIENTLISTENER_H

#include <string>
#include <vector>


class ClientListener
{
public:

        virtual void attend(std::vector<std::string> &data) = 0;


};

#endif // CLIENTListener_H

