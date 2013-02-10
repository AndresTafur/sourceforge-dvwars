#ifndef _LOGINSCENEMANAGER_
#define _LOGINSCENEMANAGER_

#include <Ogre.h>

#include <engine/Scene.h>
#include <engine/AbstractClient.h>
#include <util/SingletonContainer.h>

/**
 * Handles the login Scene
 */
class LoginSceneManager : public ClientListener, public Ogre::FrameListener
{
public:

        LoginSceneManager(Ogre::SceneManager *mgr, Ogre::RenderTarget *wnd, Scene *scn);

        /**
         * Creates scene object (currently empty, will create the museum)
         */
        void createScene();


        void doLogin(std::string user, std::string password);

        void doRegister(std::string user, std::string password, std::string mail, std::string side);


        void attend(std::vector<std::string> &data);

        void connect(std::string host, unsigned short port);


        bool frameRenderingQueued(const Ogre::FrameEvent &evt);


        virtual ~LoginSceneManager();



        inline unsigned int getStatus() { return mStatus; }

        inline void setStatus( unsigned int status) { mStatus = status; }


        inline void queueSceneEnd(Scene *scn, unsigned int status = 0) { mSceneEnding = true; mScene = scn;mStatus = status;}


private:

AbstractClient     *mClient;
Scene              *mScene;

Ogre::Light        *mLight;
Ogre::RenderTarget *mWindow;

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
bool                mSceneEnding;
};

#endif // _LOGINSCENEMANAGER_
