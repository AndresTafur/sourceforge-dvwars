#ifndef _GAME_H_
#define _GAME_H_

#include <GameObject.h>
#include <GameStaticObjectBatch.h>


/**
 * Handles current game information.
 **/
class Game
{

private:

            Game();

public:
            static Game* getInstancePtr();


            GameStaticObjectBatch getObjectBatch(std::string type);

            void addStaticBatch(std::string mName, GameStaticObjectBatch batch);


            inline void setActivePlayer(unsigned short id) { mIdActivePlayer = id; }

            inline unsigned short getActivePlayer() { return mIdActivePlayer;}


            inline void setWorkShop1(GameObject *wshop) { mWShop1 = wshop; }

            inline GameObject* getWorkShop1() { return mWShop1; }


            inline void setWorkShop2(GameObject *wshop) { mWShop2 = wshop; }

            inline GameObject* getWorkShop2() { return mWShop2; }



            virtual ~Game();


private:
static Game*     smInstance;
unsigned short   mIdActivePlayer;
GameObject*      mWShop1;
GameObject*      mWShop2;
std::map<std::string, GameStaticObjectBatch> mStaticBatchs;
};

#endif // _GAME_H_
