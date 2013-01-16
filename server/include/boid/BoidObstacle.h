#ifndef _BOIDOBSTACLE_H_
#define _BOIDOBSTACLE_H_

#include "Vector2.h"

class BoidObstacle
{
public:

        BoidObstacle();

        BoidObstacle(int x, int y);

        /**
         * Returns its position
         * @return Vector of current position
         */
        virtual Vector2 getPosition();

        /**
         * Sets current obstacle position
         * @param pos Position of current boid.
         */
        virtual void setPosition( Vector2 pos);


private:
Vector2 mPosition;
};

#endif // _BOIDOBSTACLE_H_
