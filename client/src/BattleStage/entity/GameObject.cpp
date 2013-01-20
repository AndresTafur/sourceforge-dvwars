#include <GameObject.h>

unsigned int GameObject::sm_num = 0;


GameObject::GameObject(unsigned int player, Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name)
{
        if(name.empty())
        {
            char temp[30];
            sprintf(temp,"Mesh%i",GameObject::getMeshNum());
            name = temp;
        }

        m_entity   = sceneMgr->createEntity( name, mesh);
        m_node     = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
        m_sceneMgr = sceneMgr;
        mPlayer    = player;

        m_node->attachObject(m_entity);
        m_entity->setCastShadows(true);

}


GameObject::GameObject(Ogre::SceneManager *sceneMgr, Ogre::Entity *entity,std::string name)
{
       if(name.empty())
       {
            char temp[30];
            sprintf(temp,"Mesh%i",GameObject::getMeshNum());
            name = temp;
       }

        m_entity =  entity->clone(name);
        m_node   = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
        m_node->attachObject(m_entity);
        m_entity->setCastShadows(true);
}


        void GameObject::setPosition(Ogre::Vector3 pos)
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
					pos.y =  it->worldFragment->singleIntersection.y+m_node->getScale().y*4.2;

  		    	m_node->setPosition(pos);
        }




GameObject::~GameObject()
{
        m_sceneMgr->destroyEntity(m_entity);
        m_sceneMgr->destroySceneNode(m_node);
}
