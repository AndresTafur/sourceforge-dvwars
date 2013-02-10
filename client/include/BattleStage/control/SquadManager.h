#ifndef SQUAD_MANAGER_H
#define SQUAD_MANAGER_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <map>

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include <engine/AbstractClient.h>

#include <util/Cripto.h>
#include <util/SingletonContainer.h>

#include <Squad.h>
#include <SquadBuilder.h>
#include <SelectionManager.h>


/**
 * Manages Squads.
 */
class SquadManager : public SelectionListener
{
    public:


        SquadManager();


        /**
         *
         * Checks if the selected object it's a squad and handles its respective command.
         */
        //TODO: decouple with OIS, set a new const for this in InputSystem.
        void onSelection(Ogre::MovableObject* ent,  OIS::MouseButtonID id);


        /**
         *
         * Checks if the selected object it's a squad and handles its respective command.
         */
        //TODO: decouple with OIS, set a new const for this in InputSystem?.
        void onWorldSelection(Ogre::SceneQuery::WorldFragment* ent,  OIS::MouseButtonID id);


        void createSquad(std::string type, int id, unsigned short owner, int size, unsigned int speed);


        Squad* getSquad(unsigned int idSquad);

            //TODO: Quitar esto
        inline std::map<int,Squad*> getSquads() { return mSquads;}

        virtual ~SquadManager();


private:

Ogre::SceneManager   *mScnMgr;
Ogre::Camera         *mCamera;

Squad                *mSelected;
SquadBuilder         *mSqBuilder;

std::map<int, Squad*> mSquads;
};

#endif // UNIT_MANAGER_H
