#ifndef _CROWD_H_
#define _CROWD_H_

#include <vector>
#include <Vector2.h>
#include <boost/shared_ptr.hpp>

#include "Boid.h"

class Boid;
class BoidContext;


class Crowd
{
public:

        Crowd();

        void addBoid(Boid *boid ) { mBoidsArray.push_back( boost::shared_ptr<Boid>(boid));}

        void moveTo(Vector2 target);


        inline std::vector< boost::shared_ptr<Boid> > getBoids() { return mBoidsArray;}
        unsigned int getSize();


        void setPosition(Vector2 target);

        void setBoidContext(BoidContext *cont);

        inline BoidContext* getContext() { return mContext;}

protected:
std::vector< boost::shared_ptr<Boid> > mBoidsArray;
BoidContext *mContext;
};

#endif // _CROWD_H_
