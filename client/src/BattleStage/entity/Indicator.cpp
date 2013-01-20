#include "Indicator.h"

Indicator::Indicator(std::string type)
{
  Ogre::SceneManager *mgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");

        mNode = mgr->getRootSceneNode()->createChildSceneNode();

        if( !mgr->hasParticleSystem(type+"PSys") )
            mParticles = mgr->createParticleSystem(type+"PSys", type);
        else
            mParticles = mgr->getParticleSystem(type+"PSys");

        mNode->attachObject( mParticles  );
        mNode->setVisible(true);
}


    void Indicator::setPosition(Ogre::Vector3 pos)
    {
      Ogre::SceneManager  *mgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
	  Ogre::RaySceneQuery *raySceneQuery = mgr->createRayQuery( Ogre::Ray( Ogre::Vector3(0,0,0), Ogre::Vector3::NEGATIVE_UNIT_Y));
	  Ogre::RaySceneQueryResult::iterator it;
	  Ogre::RaySceneQueryResult &qryResult = raySceneQuery->execute();

                pos.y = 0;
				raySceneQuery->setRay( Ogre::Ray(pos, Ogre::Vector3::UNIT_Y) );
				raySceneQuery->execute();

                it = qryResult.begin();

                if (it != qryResult.end() && it->worldFragment)
					pos.y =  it->worldFragment->singleIntersection.y;

  		    	mNode->setPosition(pos);
    }


    void Indicator::setVisible(bool flag)
    {
      size_t size = mParticles->getNumEmitters();

            for(size_t i=0; i < size; i++)
                mParticles->getEmitter(i)->setEnabled(flag);

            mNode->setVisible(flag);
    }

Indicator::~Indicator()
{
    delete mNode;
    delete mParticles;
}
