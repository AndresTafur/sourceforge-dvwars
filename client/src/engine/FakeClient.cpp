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

#include "FakeClient.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>


FakeClient::FakeClient()
{
 mReader.openFile("fakeClient.xml");
}


        void FakeClient::Connect(std::string address, unsigned int port)
        {

          std::string str = mReader.getAttribute("/descendant::state[@name='connect']/child::response");


                 if( address.size() == 0  )
                   return;

                 if( str != "connected" )
                 {
                     throw std::string("Connect Error");
                 }

                mCurrentState = "0";
                mSleep = true;
                this->startThread();
        }


        void FakeClient::run()
        {
          std::vector<std::string> params;
          std::string parsed;

                    while( !m_stoprequested )
                    {
                            if( mSleep )
                            {
                                sleep(2);
                                continue;
                            }

                            parsed =  "/descendant::state[@name='"+mCurrentState+"']/child::request[@data='"+mData+"']";
                            parsed =  mReader.getAttribute(parsed);


                            mCurrentState =  "/descendant::state[@name='"+mCurrentState+"']/child::request[@nextVal]/@nextVal";
                            mCurrentState =  mReader.getAttribute(mCurrentState);

                            fprintf(stderr,"Attending data: %s\n", parsed.c_str());
                            params = parseParams(parsed.c_str());

                            for(unsigned int iter=0; iter < mAnttenders.size();iter++)
                                mAnttenders[iter]->attend(params);

                            mSleep = true;
                    }




        }


        void FakeClient::Send(std::string data)
        {
            std::cout << "\n\n\n\n\n Sending data: " << data << "\n";
            mData  = data;
            mSleep = false;
        }



        std::vector<std::string> FakeClient::parseParams(std::string data)
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



FakeClient::~FakeClient()
{

}
