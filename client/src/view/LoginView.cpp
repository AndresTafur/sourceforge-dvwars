#include "LoginView.h"

LoginView::LoginView(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd)
{
    mSceneMgr  = mgr;
    mWindow    = wnd;

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
    InputSystem::getInstancePtr()->getKeyboard()->setBuffered(true);
}


        void LoginView::createCamera()
        {
           mCamera      = mSceneMgr->createCamera("Login Camera");
           mCameraNode  = mSceneMgr->createSceneNode("Camera Node");
           mCameraNode->attachObject(mCamera);


           mLogSceneMgr = new LoginSceneManager(mSceneMgr,mWindow);
           mViewPort    = mWindow->addViewport(mCamera);

           mViewPort->setOverlaysEnabled(true);
           mViewPort->setBackgroundColour(Ogre::ColourValue(0,0,0));

           mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
           mCamera->setNearClipDistance(1);
           mLogSceneMgr->createScene();
        }


        void LoginView::createGui()
        {
          GUI *guiMgr =  GUI::getInstancePtr();

                guiMgr->loadLayout("Login.gui");

                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Close")->eventMouseButtonClick        = MyGUI::newDelegate(this, &LoginView::onClose);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showLogin")->eventMouseButtonClick    = MyGUI::newDelegate(this, &LoginView::showLogin);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showRegister")->eventMouseButtonClick = MyGUI::newDelegate(this, &LoginView::showRegister);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Login")->eventMouseButtonClick = MyGUI::newDelegate(this, &LoginView::doLogIn);

                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("regOK")->eventMouseButtonClick        = MyGUI::newDelegate(this, &LoginView::doRegister);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("regCancel")->eventMouseButtonClick    = MyGUI::newDelegate(this, &LoginView::regCancel);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Back")->eventMouseButtonClick         = MyGUI::newDelegate(this, &LoginView::showMain);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("connectBtn")->eventMouseButtonClick   = MyGUI::newDelegate(this, &LoginView::onConnect);
        }


        void LoginView::onConnect(MyGUI::Widget* btn)
        {
          std::string val;

            try
            {
                    val =  MyGUI::Gui::getInstance().findWidget<MyGUI::StaticText>("ipAddress")->getCaption();

                    mLogSceneMgr->connect(val,2588);

                    MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Close")->setVisible(true);
                    MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showLogin")->setVisible(true);
                    MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showRegister")->setVisible(true);
                    MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("ipConnectionWnd")->setVisible(false);

            }
            catch(std::string ex)
            {
                MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Unable to connect, please try again later."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
            }
        }


        void LoginView::onClose(MyGUI::Widget* btn)
        {
                Ogre::Root::getSingletonPtr()->queueEndRendering();
        }


        void LoginView::regCancel(MyGUI::Widget* btn)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("registerWnd")->setVisible(false);
        }


        void LoginView::showMain(MyGUI::Widget* btn)
        {
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showLogin")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showRegister")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Close")->setVisible(true);

                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("userLbl")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("passLbl")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("user")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("pass")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Login")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Back")->setVisible(false);
       }

        void LoginView::showLogin(MyGUI::Widget* btn)
        {
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showLogin")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("showRegister")->setVisible(false);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Close")->setVisible(false);

                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("userLbl")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("passLbl")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("user")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("pass")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Login")->setVisible(true);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Back")->setVisible(true);
        }


        void LoginView::showRegister(MyGUI::Widget* btn)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("registerWnd")->setVisible(true);
        }


        void LoginView::doRegister(MyGUI::Widget* btn)
        {
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
                            MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Passwords doesn't match please verify."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            return;
                        }

                        uname = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regUsername")->getCaption();
                        email = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("regEmail")->getCaption();
                        mLogSceneMgr->doRegister(uname,pass,email, side);
                }
                catch(std::string)
                {
                    msg = MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Unable to connect, please try again later."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                }
        }


        void LoginView::doLogIn(MyGUI::Widget* btn)
        {
          MyGUI::Gui        *bgy =  MyGUI::Gui::getInstancePtr();
          MyGUI::MessagePtr  msg;
          std::string str;

                try
                {
                     mLogSceneMgr->doLogin(bgy->findWidget<MyGUI::Edit>("user")->getCaption(), bgy->findWidget<MyGUI::Edit>("pass")->getCaption() );
                }
                catch(std::string)
                {
                    msg = MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Unable to connect, please try again later."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                }
        }


        bool LoginView::frameEnded(const Ogre::FrameEvent& evt)
        {
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
                            mChallengeView = boost::shared_ptr<ChallengeView>(new ChallengeView(mSceneMgr));
                            Ogre::Root::getSingletonPtr()->removeFrameListener(mLogSceneMgr);
                        }
                        else if( status == 200)
                        {
                            MyGUI::Message::createMessageBox("Message",Ogre::String("Register"),Ogre::String("User registered sucessfully."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            MyGUI::Gui::getInstance().findWidget<MyGUI::Window>("registerWnd")->setVisibleSmooth(false);
                            mLogSceneMgr->setStatus(0);
                        }
                        else if( status == 404)
                        {
                            MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("Incorrect user/password."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            mLogSceneMgr->setStatus(0);
                        }
                        else if( status == 409)
                        {
                            MyGUI::Message::createMessageBox("Message",Ogre::String("Error"),Ogre::String("User already registered."), MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                            mLogSceneMgr->setStatus(0);
                        }

            return true;
        }



LoginView::~LoginView()
{
    //dtor
}
