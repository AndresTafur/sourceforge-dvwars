#include <cstdlib>
#include <iostream>

#include "Server.h"


class TestAttender : public ClientAttender
{

        void attend(std::string data)
        {

            std::cout << data;

        }


        void onClose()
        {
            std::cout << "lefu" << std::endl;

        }


        void handleError(NetworkException ex)
        {

            std::cout << ex.what();

        }

};


class TestBuilder : public ClientAttenderBuilder
{

         ClientAttender* getClientAttender()
         {

                return new TestAttender();
         }


};




int main(int argc, char* argv[])
{
    try
    {
        Server *server =  Server::getInstancePtr();
        TestBuilder *tab = new TestBuilder();




            server->setClientBuilder(tab);
            server->Listen(8809);
            server->run();


    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}

