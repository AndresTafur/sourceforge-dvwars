#include "DWClientAttender.h"

#include <iostream>
#include <stdio.h>


        void DWClientAttender::attend(std::string data)
        {
         RequestManager* ctr;

            m_params.clear();
            data = data.substr(0, data.find("ZZZ"));
            parseParams(data);

            ctr = m_controllers[m_params[0]];

            if(ctr)
              ctr->manage(this,m_params);
        }


        void DWClientAttender::setPlayer(Player* ply)
        {
            ply->setSocket(m_client->getSocket());
            ply->setAddress(m_client->getAddress());

            delete m_client;
            m_client = ply;
            m_player = ply;
        }


        void DWClientAttender::onClose()
        {
                    if(m_player)
                    {
                        std::cerr << "=== User connection down.. closing ===\n" << std::endl;
                    }
        }



        void DWClientAttender::parseParams(std::string data)
        {
            std::string buff;
            size_t iter;


                    while( (iter = data.find("|")) != std::string::npos )
                    {
                        buff = data.substr(0,iter);
                        m_params.push_back(buff);
                        data = data.substr(iter+1);
                    }
                    m_params.push_back(data);
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

