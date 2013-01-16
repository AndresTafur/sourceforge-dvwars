#include "Game.h"

Game *Game::smInstance = 0;

Game::Game()
{
  Ogre::StaticGeometry *geom = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager")->createStaticGeometry("TreeBatch");
        mStaticBatchs.insert( std::make_pair<std::string,GameStaticObjectBatch>("Tree.mesh_batch", geom)  );

}


        Game* Game::getInstancePtr()
        {
                if( !smInstance )
                    smInstance = new Game();
                return smInstance;
        }

        GameStaticObjectBatch Game::getObjectBatch(std::string type)
        {
                return mStaticBatchs[type];
        }


        void Game::addStaticBatch(std::string mName, GameStaticObjectBatch batch)
        {
            mStaticBatchs.insert( std::make_pair<std::string,GameStaticObjectBatch>(mName, batch)  );
        }

Game::~Game()
{
    //dtor
}
