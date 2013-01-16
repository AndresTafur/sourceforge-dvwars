#include "ClientPoller.h"
#include <poll.h>



ClientPoller::ClientPoller()
{
    mTimeOut = 300;
}


    void ClientPoller::run()
    {
      struct pollfd   *descriptors;
      size_t currentClients;
      std::string data;

                while(!m_stoprequested)
                {
                            currentClients = mClients.size();
                            descriptors    = new struct pollfd[ currentClients  ];

                            for(size_t i=0; i < currentClients; i++)
                            {
                                    descriptors[i].fd     = mClients[i]->getClient()->getSocket();
                                    descriptors[i].events = POLLIN|POLLRDHUP|POLLPRI;
                            }

                            if(  poll(descriptors, currentClients, mTimeOut) == 0)
                            {
                                    usleep(100);
                                    continue;
                            }


                            for(size_t i=0; i < currentClients; i++)
                            {
                                try
                                {

                                    if(  descriptors[i].revents & POLLRDHUP )
                                    {
                                                mClients[i]->onClose();
                                                mClients.erase(mClients.begin()+i);
                                    }
                                    else if(  descriptors[i].revents & POLLIN || descriptors[i].revents & POLLPRI )
                                    {
                                             data = mClients[i]->getClient()->Receive();
                                             mClients[i]->attend(data);
                                    }

                                }
                                catch(NetworkException ex)
                                {
                                    mClients[i]->handleError(ex);
                                }


                            }

                            delete descriptors;

                }

    }


ClientPoller::~ClientPoller()
{
  ClientAttender *ptr;


            for(unsigned int i=0; i < mClients.size();i++)
            {
                    ptr = mClients[i];
                    delete ptr;
            }

            this->stopThread();
            mClients.clear();
}
