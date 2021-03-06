/*
 *  Copyright (C) 2011-2013 Jorge A. Tafur Q. (jatafurq).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Client.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>


Client::Client()
{
    m_sock    = socket(AF_INET, SOCK_STREAM, 0);
    m_running = true;
}



        void Client::Connect(std::string address, unsigned int port)
        {
          struct hostent *host;
          int flag;


                if( address.size() == 0  )
                    return;


                host  = gethostbyname(address.c_str());

                m_address.sin_family = AF_INET;
                m_address.sin_port = htons(port);
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



Client::~Client()
{
  close(m_sock);
}
