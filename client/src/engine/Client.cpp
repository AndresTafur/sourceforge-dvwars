#include "Client.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>


Client* Client::sm_instance = 0;


Client::Client()
{
    m_sock    = socket(AF_INET, SOCK_STREAM, 0);
    m_running = true;
}


        Client* Client::getInstancePtr()
        {
            if(!sm_instance)
                sm_instance = new Client();

            return sm_instance;
        }

        Client& Client::getInstance()
        {
            if(!sm_instance)
                sm_instance = new Client();

            return *sm_instance;
        }


        void Client::Connect(std::string address, unsigned int port)
        {
          struct hostent *host;
          int flag;

                host  = gethostbyname(address.c_str());

                m_address.sin_family = AF_INET;    // Ordenación de bytes de la máquina
                m_address.sin_port = htons(port);  // short, Ordenación de bytes de la red
                m_address.sin_addr = *((struct in_addr *)host->h_addr);

                flag = fcntl(m_sock, F_GETFL, O_NONBLOCK);
                fcntl(m_sock, F_SETFL, O_NONBLOCK);

                if( connect(m_sock, (struct sockaddr *)&m_address,sizeof(struct sockaddr)) != 0 )
                    if( connect(m_sock, (struct sockaddr *)&m_address,sizeof(struct sockaddr)) != 0 )
                    {
                        fcntl(m_sock, F_SETFL, flag);
                        throw std::string("Connect Error");
                    }

                fcntl(m_sock, F_SETFL, flag);

                this->startThread();
        }


        void Client::run()
        {
          char buffer[500];
          std::vector<std::string> params;


                while(m_running)
                {
                    if( recv(m_sock, buffer, 500, MSG_WAITALL) == 0)
                    {
                        std::cerr << "\nSocket has been shuted unexpectly down.\n";
                        m_running = false;
                    }
                    else
                    {
                        fprintf(stderr,"Attending data: %s\n", buffer);
                        params = parseParams(buffer);
                        for(unsigned int iter=0; iter < m_attenders.size();iter++)
                            m_attenders[iter]->attend(params);
                    }
                }
        }


        void Client::Send(std::string data)
        {
            send(m_sock,data.c_str(),500,MSG_OOB);
        }


        void Client::removeListener(ClientListener *obj)
        {
            std::vector<ClientListener*>::iterator iter;

                        for( iter = m_attenders.begin(); iter != m_attenders.end(); iter++  )
                                if(  (*iter) == obj)
                                {
                                        m_attenders.erase(iter);
                                        break;
                                }
        }


        std::vector<std::string> Client::parseParams(std::string data)
        {
            std::string buff;
            size_t iter;
            std::vector<std::string> params;


                    while( (iter = data.find("|")) != std::string::npos )
                    {
                        buff = data.substr(0,iter);
                        params.push_back(buff);
                        data = data.substr(iter+1);
                    }

                    params.push_back(data);
                    return params;
        }



        void Client::destroy()
        {
            if(sm_instance)
                delete sm_instance;
        }


Client::~Client()
{
  close(m_sock);
}
