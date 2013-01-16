#ifndef _UNIT_H_
#define _UNIT_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "boid/Vector2.h"
#include "boid/Boid.h"

class Squad;

/**
 * Represents an ingame unit, use boids for behaviour.
 * @see Boids
 */
class Unit : public Boid
{
public:

        Unit(unsigned long id,Squad *sqd);


        Vector2 getVelocity();

        void setPosition(Vector2 pos);

        void setVelocity(Vector2 vel);

        virtual ~Unit();


private:
 unsigned long   mID;
 Vector2         mVelocity;
 Squad          *mSquad;
};

#endif // _UNIT_H_
