#ifndef _CREATIONLISTENER_H_
#define _CREATIONLISTENER_H_

#include <Squad.h>
#include <Building.h>

/**
 * Interface to provide progress and create observers
 */
class CreationListener
{
public:

       virtual void onProgressUpdate(size_t val) = 0;

       inline virtual void onCreateSquad(Squad *squad) { };

       inline virtual void onCreateBuilding(Building *building) { };

};

#endif // _PROGRESSLISTENER_H_
