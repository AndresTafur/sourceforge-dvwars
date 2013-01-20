#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include <Ogre.h>

class Indicator
{
public:

        Indicator(std::string type);

        void setPosition(Ogre::Vector3 pos);

        void setVisible(bool flag);

        virtual ~Indicator();



private:
Ogre::ParticleSystem *mParticles;
Ogre::SceneNode      *mNode;
};

#endif // _INDICATOR_H_
