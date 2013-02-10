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


#include "LoginView.h"

void LoginView::create(Ogre::RenderTarget* wnd)
{
            Scene::create(wnd);
            Ogre::Root::getSingletonPtr()->addFrameListener(this);
            InputSystem::getInstancePtr()->getKeyboard()->setBuffered(true);
}

        std::string LoginView::getName() {
            return "Login";
        }


        void LoginView::createSceneObjects()
        {
           mLogSceneMgr = new LoginSceneManager(mSceneMgr,mWindow,this);
           mLogSceneMgr->createScene();
        }


        void LoginView::createGui()
        {
          GUI *guiMgr =  GUI::getInstancePtr();


                GUI::getInstancePtr()->initialize(mWindow,mSceneMgr);

                //Create widgets and set callbacks
                mLayout = guiMgr->loadLayout("Login.gui");
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("exit")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginView::onExit);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showRegister")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginView::showRegister);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Login")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginView::onConnect);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("regOK")->eventMouseButtonClick     += MyGUI::newDelegate(this, &LoginView::doRegister);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("regCancel")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginView::regCancel);
        }


        void LoginView::onConnect(MyGUI::Widget* btn)
        {
          std::string val;
          MyGUI::Gui  *bgy =  MyGUI::Gui::getInstancePtr();


                    //TCP Connection
                    try
                    {
                            val =  MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("server")->getCaption();

                            if( val.size() == 0 )
                            {
                                bgy->findWidget<MyGUI::TextBox>("errorMsg")->setCaption("Server name shouldn't be empty.");
                                return;
                            }
                            mLogSceneMgr->connect(val,2588);
                    }
                    catch(std::string ex)
                    {
                            MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::TextBox>("errorMsg")->setCaption("Unable to connect, please try again later.");
                            return;
                    }

                    //Actual Login
                    try
                    {
                            bgy->findWidget<MyGUI::TextBox>("errorMsg")->setCaption("Sending login data...");
                            mLogSceneMgr->doLogin(bgy->findWidget<MyGUI::EditBox>("user")->getCaption(), bgy->findWidget<MyGUI::EditBox>("pass")->getCaption() );
                    }
                    catch(std::string)
                    {
                            bgy->findWidget<MyGUI::TextBox>("errorMsg")->setCaption("Login failed, please check your data.");
                    }
        }


        void LoginView::onExit(MyGUI::Widget* btn)
        {
           endScene(0);
        }


        void LoginView::regCancel(MyGUI::Widget* btn)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("registerWnd")->setVisible(false);
        }


        void LoginView::showRegister(MyGUI::Widget* btn)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("registerWnd")->setVisible(true);
        }


        void LoginView::doRegister(MyGUI::Widget* btn)
        {/*
          MyGUI::MessagePtr  msg;
          std::string pass, pass2, uname, email, side;
          size_t sideIndex;

                try
                {
                        pass      = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regPasswd")->getCaption();
                        pass2     = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regConfirm")->getCaption();
                        sideIndex = MyGUI::Gui::getInstance().findWidget<MyGUI::ComboBox>("regSide")->getIndexSelected();
                        side      = MyGUI::Gui::getInstance().findWidget<MyGUI::ComboBox>("regSide")->getItemNameAt(sideIndex);


                        if( pass.compare(pass2) != 0)
                        {
//                            MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Passwords doesn't match please verify."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            return;
                        }

                        uname = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regUsername")->getCaption();
                        email = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regEmail")->getCaption();
                        mLogSceneMgr->doRegister(uname,pass,email, side);
                }
                catch(std::string)
                {
//                    msg = MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Unable to connect, please try again later."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                }*/
        }


        void LoginView::setMessage(std::string message)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("errorMsg")->setCaption(message);
        }


        void LoginView::setErrorMessage(std::string error)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("errorMsg")->setCaption(error);
        }



        bool LoginView::frameEnded(const Ogre::FrameEvent& evt)
        {/*
          unsigned int status   = mLogSceneMgr->getStatus();

                        if( status == 700)
                        {
                          MyGUI::Gui *bgy =  MyGUI::Gui::getInstancePtr();

                                mWindow->removeAllViewports();
                                mSceneMgr->destroyAllCameras();
                                mSceneMgr->destroyAllLights();
                                mSceneMgr->destroySceneNode("Camera Node");

                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("showLogin"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("showRegister"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("userLbl"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("passLbl"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("user"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("pass"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("Login"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("Close"));
                                bgy->destroyWidget(bgy->findWidget<MyGUI::Widget>("Back"));

                                mMainView = new MainView(mSceneMgr,mWindow);
                                mMainView->createGui();

                                Client::getInstancePtr()->Send( "501");
                                Ogre::Root::getSingletonPtr()->removeFrameListener(this);
                                mLogSceneMgr->setStatus(0);

                                mLogSceneMgr->disable();
                                mChallengeView->disable();
                                Ogre::Root::getSingletonPtr()->removeFrameListener(this);
                        }
                        else if( status == 201 )
                        {
                            mLogSceneMgr->setStatus(0);
                            mChallengeView = boost::shared_ptr<LobbyView>(new LobbyView(mSceneMgr));
                            Ogre::Root::getSingletonPtr()->removeFrameListener(mLogSceneMgr);
                        }
                        else if( status == 200)
                        {
//                            MyGUI::Message::createMessageBox("Message",Ogre::String("Register"),Ogre::String("User registered sucessfully."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            MyGUI::Gui::getInstance().findWidget<MyGUI::Window>("registerWnd")->setVisibleSmooth(false);
                            mLogSceneMgr->setStatus(0);
                        }
                        else if( status == 404)
                        {
//                            MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Incorrect user/password."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            mLogSceneMgr->setStatus(0);
                        }
                        else if( status == 409)
                        {
 //                           MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("User already registered."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            mLogSceneMgr->setStatus(0);
                        }
*/




            return true;
        }


        void LoginView::unloadLayout()
        {
                GUI::getInstancePtr()->unloadLayout(mLayout);
        }


        void LoginView::destroy()
        {
            Ogre::Root::getSingletonPtr()->removeFrameListener(this);
            unloadLayout();
            GUI::getInstancePtr()->clean();
            delete mLogSceneMgr;


            Scene::destroy();
        }

LoginView::~LoginView()
{
    //dtor
}
