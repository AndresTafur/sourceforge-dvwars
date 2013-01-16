#include <iostream>

#include "Server.h"
#include "DWClientBuilder.h"
#include "LoginAdapter.h"


int main()
{
Server           *serv;
DWClientBuilder  *bldr;
LoginAdapter     *obj;
ConfigReader      cfgReader;

std::string       user;
std::string       passwd;
std::string       schema;
std::string       host;

unsigned int      port   = 2588;
unsigned int      dbPort;

        try
        {


             //Reading configurations.
             cfgReader.openFile("config.xml");

             host   = cfgReader.getAttribute("/descendant::Option[@name='database']/child::property[@name='host']");
             dbPort = atoi(cfgReader.getAttribute("/descendant::Option[@name='database']/child::property[@name='port']").c_str());
             schema = cfgReader.getAttribute("/descendant::Option[@name='database']/child::property[@name='schema']");
             user   = cfgReader.getAttribute("/descendant::Option[@name='database']/child::property[@name='user']");
             passwd = cfgReader.getAttribute("/descendant::Option[@name='database']/child::property[@name='password']");

             port   = atoi( cfgReader.getAttribute("/descendant::Option[@name='network']/child::property[@name='port']").c_str() );


             if( !MySQL::getInstancePtr()->connect(user,passwd,schema.c_str(), host, dbPort) )
             {
                    printf("Failed stabilishing database connection, username: [%s], passwd: [%s], schema: [%s], port [%i], host [%s]. aborting...\n",
                           user.c_str(),passwd.c_str(),schema.c_str(), dbPort, host.c_str() );
                    return -1;
             }


             //TODO: change this initialization
             Cripto::initialize();
             Cripto::getInstancePtr()->setKey("B8AH6857E832C42Z");
             Cripto::getInstancePtr()->setIv("E5Z6AD15508FP10B");


             //Creating network handlers
             serv = Server::getInstancePtr();
             bldr = DWClientBuilder::getInstancePtr();


             obj  = new LoginAdapter();

             //registering starting protocols.
             bldr->addRequestCtrl("600", obj);
             bldr->addRequestCtrl("601", obj);
             bldr->addRequestCtrl("602", obj);

             //running server.
             printf("Starting server on port: %i...",port);
             serv->Listen(port);
             serv->setClientBuilder(bldr);
             printf("ready\n");

             //waiting to exit
             getchar();
             serv->destroy();
        }
        catch(NetworkException ex)
        {
            std::cerr << "\tNetwork Error: " << ex.what() << std::endl;
            return -1;
        }
        catch(DBException ex)
        {
            std::cerr << "\tDatabase Error: " << ex.what() << std::endl;
            return -1;
        }
        catch(std::string str)
        {
            std::cerr << str << std::endl;
            return -1;
        }

        return 0;
}
