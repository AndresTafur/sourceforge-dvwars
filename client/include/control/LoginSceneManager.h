#ifndef _LOGINSCENEMANAGER_
#define _LOGINSCENEMANAGER_

#include <Ogre.h>

#include <entity/Game.h>

#include <engine/Client.h>
#include <engine/ClientListener.h>

/**
 * Handles the login Scene
 */
class LoginSceneManager : public ClientListener, public Ogre::FrameListener
{
public:

        LoginSceneManager(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd);

        /**
         * Creates scene object (currently empty, will create the museum)
         */
        void createScene();


        void disable();


        void doLogin(std::string user, std::string password);

        void doRegister(std::string user, std::string password, std::string mail, std::string side);


        void attend(std::vector<std::string> &data);

        void connect(std::string host, unsigned short port);



        bool frameRenderingQueued(const Ogre::FrameEvent &evt);


        virtual ~LoginSceneManager();



        inline unsigned int getStatus() { return mStatus; }

        inline void setStatus( unsigned int status) { mStatus = status; }


private:

Client             *mClient;

Ogre::Light        *mLight;
Ogre::RenderWindow *mWindow;

Ogre::SceneManager *mSceneMgr;
Ogre::SceneNode    *mTableNode;
Ogre::SceneNode    *mCameraNode;
Ogre::SceneNode    *mMuseumNode;
Ogre::SceneNode    *mScrollNode;


Ogre::Entity       *mTable;
Ogre::Entity       *mScroll;
Ogre::Entity       *mMuseum;

short               mFrameCount;
unsigned int        mStatus;
};

#endif // _LOGINSCENEMANAGER_
