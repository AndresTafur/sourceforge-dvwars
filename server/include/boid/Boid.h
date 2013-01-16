#ifndef _BOID_H_
#define _BOID_H_

#include "Vector2.h"
#include <boost/shared_ptr.hpp>

#define PATH 1
#define MAX_PATHS 1000
#define INITIAL_TENDENCY 20000
#define VENTANA_MAX_X 1500
#define VENTANA_MAX_Y 1500


class BoidContext;
class Crowd;


/**
 * Interface defining boids default methods.
 */
class Boid
{
public:

        Boid();

        void setCaptain( boost::shared_ptr<Boid> cap);

        void setContext(BoidContext *context);


        inline void setCrowd(boost::shared_ptr<Crowd> crd) { mBelongCrowd = crd; }

        void makePath();

        int pathFinder(Vector2 target);

        /**
         * Returns its position
         * @return Vector of current position
         */
        virtual Vector2 getPosition() {return mPos;}

        /**
         * Sets current boid position
         * @param pos Position of current boid.
         */
        virtual void setPosition( Vector2 pos) { mPos = pos;}


        void move(Vector2 target);

        /**
         * Returns current vectorial velcity.
         * @return current velocity.
         */

        virtual Vector2 getVelocity() = 0;


        virtual void setVelocity( Vector2 pos) = 0;


        virtual void setTendency(int tend ) { mTendency = tend;}

        virtual int getTendency() { return mTendency;}


protected:
BoidContext *mContext;
boost::shared_ptr<Boid>  mCapitan;
boost::shared_ptr<Crowd> mBelongCrowd;

short   mPathMatrix[VENTANA_MAX_X/PATH][VENTANA_MAX_Y/PATH][2];
int   mMyPath[MAX_PATHS][2];
int   mPathCounter;
int   mTendency;
Vector2 mPos;

};

#endif // _BOID_H_
