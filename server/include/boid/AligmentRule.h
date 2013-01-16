#ifndef _ALIGMENTRULE_H_
#define _ALIGMENTRULE_H_

#include <Rule.h>

/**
 *
 *  Boids Aligment rule, to keep them orientated.
 *  @see Rule
 */

class AligmentRule : public Rule
{
public:

        /**
         * Default constructor.
         */
        AligmentRule();

        /**
         *  Apply current rule to mainBoid, based on boids positions.
         *  @param  mainBoid Boid to apply this rule.
         *  @param  boids Other boids in context.
         *  @return Vector2 "Velocity" to be added to the boid.
         */
        Vector2 apply(Boid *mainBoid, std::vector<Boid*> boids);


        virtual ~AligmentRule();

};

#endif // _ALIGMENTRULE_H_
