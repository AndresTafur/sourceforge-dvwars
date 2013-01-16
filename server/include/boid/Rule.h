#ifndef _RULE_H_
#define _RULE_H_

#include <vector>


#include "Vector2.h"
#include "Boid.h"


/**
 * Interface to define rules.
 */
class Rule
{
public:

        /**
         *  Apply current rule to mainBoid, based on boids positions.
         *  @param  mainBoid Boid to apply this rule.
         *  @param  boids Other boids in context.
         *  @return Vector2 "Velocity" to be added to the boid.
         */
        virtual Vector2 apply(Boid *mainBoid, std::vector<Boid*> boids) = 0;

private:

};

#endif // _RULE_H_
