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

#include "LoginSceneManager.h"

LoginSceneManager::LoginSceneManager(Ogre::SceneManager *mgr, Ogre::RenderTarget *wnd)
{
    mSceneMgr   = mgr;
    mWindow     = wnd;

    mFrameCount = 0;
    mStatus     = 0;

    mCameraNode = mgr->getSceneNode("Camera Node");
    mClient     = Client::getInstancePtr();

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

        void LoginSceneManager::doLogin(std::string user, std::string password)
        {
                     fprintf(stderr,"\nSending Login Data\n");
                     mClient->Send("601|" + user + "|"+ password);
        }


        void LoginSceneManager::doRegister(std::string user, std::string password, std::string mail, std::string side)
        {
          std::string str;

                    fprintf(stderr,"\nSending registration data\n");
                    str = "600|" + user + "|" + password + "|" + mail + "|" + side;
                    mClient->Send( str );
        }


        void LoginSceneManager::createScene()
        {
                mLight = mSceneMgr->createLight("MainLight");

                mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
                mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
                mSceneMgr->setShadowColour(Ogre::ColourValue(0.5,0.5,0.5));

                mLight->setPosition(100,100,100);
                mLight->setSpecularColour(0.7,0.6,0);
                mLight->setCastShadows(true);


                mMuseum     = mSceneMgr->createEntity( "Museo.mesh"  );
                mMuseumNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                mMuseumNode->attachObject(mMuseum);
                mMuseumNode->setPosition(0,0,0);

                mTable      = mSceneMgr->createEntity( "Pedestal.mesh"  );
                mTableNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                mTableNode->attachObject(mTable);
                mTableNode->setPosition(30,-10,250);


                mScroll     = mSceneMgr->createEntity( "Scroll.mesh"  );
                mScrollNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                mScroll->setCastShadows(false);
                mScrollNode->attachObject(mScroll);
                mScrollNode->setPosition(34,-1,247);


                mCameraNode->setPosition( Ogre::Vector3(-70,80,-70) );
                mSceneMgr->getCamera("Main Camera")->lookAt( Ogre::Vector3(0,50,0) );
        }


        void LoginSceneManager::connect(std::string host, unsigned short port)
        {
                    std::cerr << "Connecting: {" << host <<"}"<< std::endl;

                    mClient->addListener(this);
                    mClient->Connect(host, port);
        }


        void LoginSceneManager::attend(std::vector<std::string> &data)
        {
                //TODO: change for a chainOfCommand
                if( data[0] == "409")
                    mStatus = 409;
                else if( data[0] == "200")
                    mStatus = 200;
                else if( data[0] == "201" )
                    mStatus = 201;
                else if( data[0] == "404")
                    mStatus = 404;
                else if( data[0] == "700")
                {
                    mStatus = 700;
                }
        }



        bool LoginSceneManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
        {

                        if( !mSceneEnding )
                            mCameraNode->rotate( Ogre::Vector3(0,1,0), Ogre::Radian( evt.timeSinceLastFrame*0.25 ) );

                        else if( mCameraNode->getPosition().distance(Ogre::Vector3(30,8,240)) > 2 )
                        {
                                mCameraNode->setPosition( mCameraNode->getPosition() +(Ogre::Vector3(30,8,240) - mCameraNode->getPosition() )*evt.timeSinceLastFrame);
                                mSceneMgr->getCamera("Main Camera")->lookAt(30,2,245);
                        }
                        else if(mScene){

                              Ogre::Vector3 vect =  mCameraNode->getPosition();
                              Ogre::Quaternion quat = mSceneMgr->getCamera("Main Camera")->getOrientation();
                              Ogre::Vector3  dir  =   mSceneMgr->getCamera("Main Camera")->getDirection();


                                    fprintf(stderr,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Position:[%f, %f, %f], Orient:[%f,%f,%f,%f], Dir:[%f,%f,%f]",vect.x,vect.y,vect.z,
                                                        quat.w,quat.x,quat.y,quat.z, dir.x, dir.y,dir.z
                                                    );


                                mScene->endScene(0);
                        }


            return true;
        }



LoginSceneManager::~LoginSceneManager()
{
       Client::getInstancePtr()->removeListener(this);
       Ogre::Root::getSingletonPtr()->removeFrameListener(this);

       mSceneMgr->destroyLight(mLight);
       mSceneMgr->destroySceneNode(mMuseumNode);
       mSceneMgr->destroySceneNode(mTableNode);
       mSceneMgr->destroySceneNode(mScrollNode);
       mSceneMgr->destroyAllEntities();
}
