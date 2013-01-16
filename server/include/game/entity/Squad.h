#ifndef _SQUAD_H_
#define _SQUAD_H_

#include <string>
#include <vector>

#include <entity/Unit.h>
#include <boid/Crowd.h>

class Game;

/**
 * Encapsulates Squad properties and it's units
 */
class Squad : public Crowd
{
public:

        Squad(unsigned int units, unsigned int speed, unsigned int id);


        inline unsigned int getID() { return mID;}

        inline void  setID(unsigned int id) { mID = id;}


        /**
         * Monetary cost.
         * @return Cost.
         */
        inline unsigned long getCost() { return mCost; }

        inline void setCost(unsigned long cost) { mCost = cost; }


        /**
         * Time cost.
         * @return time to be produced.
         */
        inline unsigned int getTime() { return mTime; }

        inline void setTime(unsigned int time) { mTime = time; }



         Unit* getUnit(unsigned int pos);



        inline unsigned int getSpeed() { return mSpeed;}


        /**
         * Sets the model to be applied on clients.
         * @param mesh Model.
         */
        inline void setMesh(std::string mesh) { mMesh = mesh; }


        /**
         * gets the model to be applied on clients.
         * @return Model.
         */
        inline std::string getMesh() { return mMesh; }


        inline void setGame(Game* gm) { mGame = gm; }

        inline Game* getGame() { return mGame; }

        virtual ~Squad();


private:

 unsigned int mSpeed;

 unsigned int mID;

 unsigned int mTime;

 unsigned long mCost;

 unsigned int mOwner;

 std::string  mMesh;

 Game *mGame;
};

#endif // _SQUAD_H_
