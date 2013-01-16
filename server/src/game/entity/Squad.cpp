#include "entity/Squad.h"



Squad::Squad(unsigned int units, unsigned int speed, unsigned int id) : Crowd()
{
  Unit *unit;

        mID    = id;
        mSpeed = speed;

        for(unsigned int iter = 0; iter < units; iter++)
        {
            unit = new Unit(iter,this);
            addBoid(unit);
            unit->setCrowd( boost::shared_ptr<Crowd>(this));
            unit->setCaptain(mBoidsArray[0]);
        }
}


    Unit* Squad::getUnit(unsigned int pos)
    {
       boost::shared_ptr<Boid> object;


            if( pos < mBoidsArray.size() )
                   object = mBoidsArray[pos];

            return static_cast<Unit*>(object.get());
    }


 Squad::~Squad()
{
    //dtor
}
