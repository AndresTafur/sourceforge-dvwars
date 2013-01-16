#ifndef _SQUADBUILDER_H_
#define _SQUADBUILDER_H_


#include "util/ConfigReader.h"
#include "entity/Squad.h"

/**
 * Build a squad. it use ConfigReader to get it's atributes.
 * @see ConfigReader.
 */
class SquadBuilder
{
public:

        SquadBuilder();

        Squad* createSquad(std::string type);

        virtual ~SquadBuilder();

private:
static unsigned int mSquadId;
};

#endif // _SQUADBUILDER_H_
