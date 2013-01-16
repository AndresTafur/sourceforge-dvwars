#include "ClientAttender.h"
#include <iostream>
#include <fcntl.h>

        void ClientAttender::run()
        {
          SOCKET sock = m_client->getSocket();
          char buffer[500];

                fcntl(sock, F_SETFL, O_NONBLOCK);

                while(!m_stoprequested)
                {
                    strcpy(buffer,"");
                    if( recv(sock, buffer, 500, MSG_WAITALL) == 0)
                    {
                        //TODO: Inform Server about this so its been remove from the multicast queue.
                        std::cerr << "\nSocket has been shuted unexpectly down.\n";
                        onClose();
                        return;
                    }
                    else
                        attend( buffer);
                }
        }



        void ClientAttender::addRequestCtrl(std::map<std::string,RequestManager*> list)
        {
          std::map<std::string,RequestManager*>::iterator it;


                    for ( it=list.begin() ; it != list.end(); it++ )
                    {
                        m_controllers.insert(*it);
                        std::cerr << "Request Attender Registered: " << (*it).second->getControllerName()
                                  << " Protocol: " << (*it).first << std::endl;
                    }
        }


        void ClientAttender::addRequestCtrl(std::string proto, RequestManager *obj)
        {
             m_controllers.insert( std::make_pair<std::string,RequestManager*>(proto,obj));
        }

        void ClientAttender::removeRequestCtrl(std::string proto)
        {
            m_controllers.erase(proto);
        }


        ClientAttender::~ClientAttender()
        {
            close(m_client->getSocket());
            std::cerr << strerror(errno);
            stopThread();
            delete m_client;
        }
