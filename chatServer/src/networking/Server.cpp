#include "Server.h"
#include <fcntl.h>

#include <netinet/tcp.h>

#include <iostream>


Server* Server::smInstance = 0;


Server::Server()
{
  m_sock    = socket(AF_INET, SOCK_STREAM, 0);
  mBuilder  = 0;
  mPoller   = new ClientPoller();
}


        Server* Server::getInstancePtr()
        {
            if(!smInstance)
                smInstance = new Server();

            return smInstance;
        }


        Server& Server::getInstance()
        {
            if(!smInstance)
                smInstance = new Server();

            return *smInstance;
        }


        void Server::Listen(unsigned int port)
        {
            int override = 1;

                    mAddress.sin_family = AF_INET;
                    mAddress.sin_port   = htons(port);
                    mAddress.sin_addr.s_addr =INADDR_ANY;


                    if (setsockopt(m_sock,SOL_SOCKET,SO_REUSEADDR,&override,sizeof(int)) == -1)
                            throw NetworkException();

                    if( bind (m_sock, (struct sockaddr *)&mAddress, sizeof (mAddress)) != 0 )
                            throw NetworkException();

                    if (listen (m_sock, 1000) != 0)
                            throw NetworkException();

                    mPoller->startThread();
                    this->startThread();

        }



        void Server::run()
        {
          struct sockaddr clienteAddress;
          SOCKET clientSocket;
          socklen_t clientLength;
          ClientAttender *obj;
          Client *clt;



                    clientLength = sizeof( (struct sockaddr*)&clienteAddress);

                    while(!m_stoprequested)
                    {
                            clientSocket = accept (m_sock, &clienteAddress, &clientLength);

                            if (clientSocket < 0)
                                std::cerr << "Error acepting socket";

                            std::cerr << "Client Connected\n";

                            if( !mBuilder)
                            {
                                    std::cerr << "\nNo Client Attention Builder registered sever will not be able to manage clients.\n";
                                    continue;
                            }

                            clt = new Client(clientSocket,clienteAddress);
                            obj = mBuilder->getClientAttender();
                            obj->setClient(clt);

                            mPoller->addClient(obj);
                    }
        }


        void Server::sendMulticast(std::wstring data)
        {
          std::vector<ClientAttender*> mClients = mPoller->getClients();

                for(unsigned int i=0; i < mClients.size();i++)
                    mClients[i]->getClient()->Send(data);
        }


        void Server::destroy()
        {
            if(smInstance)
                delete smInstance;
        }


Server::~Server()
{
    this->stopThread();
    close(m_sock);
    m_sock = -1;

    delete mPoller;
}
