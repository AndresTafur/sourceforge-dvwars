#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_


#include <map>
#include <queue>

#include <entity/Game.h>
#include <entity/Squad.h>
#include <GameRequest.h>

#include <Player.h>
#include <RequestManager.h>
#include <ClientAttender.h>


/**
 * Handles game operations.
 */
class GameManager : public RequestManager, public DaVinciWars::Thread
{
 public:

        GameManager(ClientAttender* pl1, ClientAttender* pl2);

        /**
         * attends client datta
         */
        void manage(ClientAttender* attender, std::vector<std::string> &params);

        /**
         * Queues game start.
         */
        void startGame();


        void run();


        inline std::string getControllerName() { return "GameManager"; }

        inline ClientAttender* getAttender1()  {  return mAttender1; }

        inline ClientAttender* getAttender2()  {  return mAttender2; }

        virtual ~GameManager();

protected:

        /**
         * Auxiliar method to create workshops.
         */
        void createWorkShops();

        void createNature();


private:
ClientAttender  *mAttender1;
ClientAttender  *mAttender2;
Game            *mGame;
unsigned short   mStart;
std::queue<GameRequest*>  mPendingRequests;

};

#endif // _GAMEMANAGER_H_
