#ifndef _BOIDCONTEXT__
#define _BOIDCONTEXT__


#include <vector>
#include <Thread.h>

#include "Crowd.h"
#include "Rule.h"
#include "BoidObstacle.h"


#define CHAOS_SIZE 10000

/**
 * Defines an environment where Boids interact
 */
class BoidContext : public DaVinciWars::Thread
{
public:

        BoidContext();

        void addCrowd(boost::shared_ptr<Crowd> crd);

        void addObstacle(BoidObstacle *obj);

        void addRule(boost::shared_ptr<Rule> rule);


        /**
         *
         * Starts context simulation (rules apply each pass).
         */
        void run();

        inline int randomInteger() { return(chaos[mChaosCounter++%CHAOS_SIZE]);}


        inline void lock() { mMutex.lock(); }

        inline void unlock() { mMutex.unlock(); }

        virtual ~BoidContext();

public:
short mDomainMatrix[1500][1500];

private:
int chaos[CHAOS_SIZE];
unsigned int mChaosCounter;

std::vector< boost::shared_ptr<Crowd> >  mCrowds;
std::vector< boost::shared_ptr<Rule> >  mRules;
Vector2 mTarget;
boost::mutex        mMutex;
};

#endif // _BOIDCONTEXT__
