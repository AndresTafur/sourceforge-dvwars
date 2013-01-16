#ifndef _SQUAD_H
#define _SQUAD_H

#include <Ogre.h>
#include "entity/Unit.h"

class SquadBuilder;


/**
 *  This class contains the entity batch of a squad and its operations
 *  @see SquadBuilder
 */
class Squad
{
protected:


        /**
         * Default constructor.
         * Create a squad (called by SquadBuilder) with its batch instance.
         *
         * @param batch BatchInstance.
         * @see SquadBuilder.
         */
        Squad(unsigned int id, unsigned short owner, unsigned int speed);


public:


        void addUnit(Unit* unit);

        Unit* getUnit(size_t id);


        inline unsigned int getID() { return mID; }

        inline void setID(unsigned int val) { mID = val;}


        void setSelected(bool val);


        inline unsigned short getOwner() { return mOwner;}

        inline void setOwner(unsigned short owner) { mOwner = owner;}

        virtual ~Squad();

private:
 std::map<size_t,Unit*>   mUnits;

 unsigned int   mID;
 unsigned short mOwner;
 Ogre::Vector3  mPos;
 unsigned int   mSpeed;

//TODO: Remove this?, fix positions when creating?
 static int     mSquadCount;
 friend class   SquadBuilder;
 };

#endif // _SQUAD_H
