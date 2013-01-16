#ifndef PLAYER_H
#define PLAYER_H

#include <Client.h>
#include <entity/Squad.h>
#include <entity/Workshop.h>
#include <userManager/User.h>


#include <map>

/**
 * represents a game player.
 */
class Player : public Client, public User
{
    public:

        /** Default constructor */
        Player();

        /** Constructs a player based on it's User object*/
        Player(User &usr);


        Player(std::string name);

        /**
         * Adds a new squad to this player.
         *
         *  @param obj New squad to be added.
         */
        void addSquad(Squad *obj);

        inline std::map<unsigned int, Squad*> getSquads() { return mSquads;}


        void setGold(unsigned long gold);


        unsigned long getGold() { return mGold;}

        /**
         * Looks for a specific squad of this player.
         *
         * @param squadId Squad to be find-
         * @return Squad if found, NULL otherwise.
         */

        Squad* findSquad(unsigned int squadId);


        inline void setWorkshop(Workshop *obj) { mWorkShop = obj; }

        inline Workshop* getWorkshop() { return mWorkShop;}


        /** Default destructor */
        virtual ~Player();

    private:

    unsigned long  mGold;
    unsigned long  mPoints;
    Workshop      *mWorkShop;

    std::map<unsigned int, Squad*> mSquads;


};

#endif // PLAYER_H
