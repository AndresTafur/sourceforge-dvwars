#ifndef _GAME_H_
#define _GAME_H_


#include <map>
#include <Player.h>
#include <entity/Squad.h>
#include <boid/BoidContext.h>

/**
 * Entity that handles every element created within the game
 */
class Game
{
public:

        Game();


        void addPlayer(Player *ply);


        /**
         * Adds new squad to player
         *
         * @param playerId Player to be added the new squad.
         * @param obj Squad to be added.
         */
        void addSquad(Squad *obj, unsigned int playerId = 0);


        inline Player* getPlayer(unsigned int playerId) { return mPlayers[playerId];}

        inline std::vector<Player*> getPlayers() { return mPlayers; }


        int indexOf(Player *obj);


        void sendMulticast(std::string command);


        /**
         *  returns a Squad based on its id.
         *  @param id Squad id.
         *  @return A Squad  or NULL if not found.
         */
        Squad* getSquad(unsigned int id);


        inline boost::shared_ptr<BoidContext> getBoidContext() { return mContext;}


        virtual ~Game();


private:
std::vector<Player*> mPlayers;
boost::shared_ptr<BoidContext> mContext;
};

#endif // _GAME_H_
