#include "Server.h"
#include <fcntl.h>

#include <netinet/tcp.h>

#include <iostream>


Server* Server::sm_instance = 0;


Server::Server()
{
  m_sock    = socket(AF_INET, SOCK_STREAM, 0);
  m_builder = 0;
}


        Server* Server::getInstancePtr()
        {
            if(!sm_instance)
                sm_instance = new Server();

            return sm_instance;
        }


        Server& Server::getInstance()
        {
            if(!sm_instance)
                sm_instance = new Server();

            return *sm_instance;
        }


        void Server::Listen(unsigned int port)
        {
            int override = 1;

                    m_address.sin_family = AF_INET;
                    m_address.sin_port   = htons(port);
                    m_address.sin_addr.s_addr =INADDR_ANY;


                    if (setsockopt(m_sock,SOL_SOCKET,SO_REUSEADDR,&override,sizeof(int)) == -1)
                            throw NetworkException();

                    if( bind (m_sock, (struct sockaddr *)&m_address, sizeof (m_address)) != 0 )
                            throw NetworkException();

                    if (listen (m_sock, 1000) != 0)
                            throw NetworkException();

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

                            if( !m_builder)
                            {
                                    std::cerr << "\nNo Client Attention Builder registered sever will not be able to manage clients.\n";
                                    continue;
                            }

                            clt = new Client(clientSocket,clienteAddress);
                            obj = m_builder->getClientAttender();
                            obj->setClient(clt);
                            obj->startThread();

                            m_clients.push_back(obj);
                    }
        }


        void Server::sendMulticast(std::string data)
        {
            for(unsigned int i=0; i < m_clients.size();i++)
                  m_clients[i]->getClient()->Send(data);
        }


        void Server::destroy()
        {
            if(sm_instance)
                delete sm_instance;
        }


Server::~Server()
{
  ClientAttender *ptr;


            for(unsigned int i=0; i < m_clients.size();i++)
            {
                    ptr = m_clients[i];
                    delete ptr;
            }

            m_clients.clear();

            close(m_sock);
            m_sock = -1;

            this->stopThread();
}
