#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <GameObject.h>
#include <DaVinciGlobals.h>


/**
 * Draws a Building
 */
class Building : public GameObject
{
public:

        Building(unsigned int player, Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name = "");


        inline void setName(std::string val) { mName = val; }

        inline std::string getName() { return mName; }


        virtual ~Building();

private:
std::string   mName;
};

#endif // _BUILDING_H_
