#include "SquadBuilder.h"

unsigned long SquadBuilder::mUCount = 0;

SquadBuilder::SquadBuilder()
{


    if (Ogre::Root::getSingleton ().getRenderSystem ()->getCapabilities ()->hasCapability (Ogre::RSC_VERTEX_PROGRAM) == false)
           OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "Your video card doesn't support batching", "DaVinciWars::SquadBuilder");
}


        Squad* SquadBuilder::createSquad(std::string meshName, unsigned int id, unsigned short owner, unsigned int batchDimensions, unsigned int speed)
        {
          Ogre::Entity       *baseEntity;
          Ogre::Entity       *entity;
          Ogre::SceneNode    *node;
          Ogre::SceneManager *mgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
          Squad              *sqd;
          Unit               *unit;
          char                buff[100];


                baseEntity = mgr->createEntity(meshName+"_Unit",meshName);
               // setupInstancedMaterialToEntity(baseEntity);

                sqd = new Squad(id,owner,speed);

                for(unsigned long i = 0; i < batchDimensions; i++)
                {
                        sprintf(buff,"%s_%li%li",baseEntity->getName().c_str(), i,SquadBuilder::mUCount++);
                        entity  = baseEntity->clone(buff);
                        unit    = new Unit(entity,i);
                        sqd->addUnit(unit);
                }
                mgr->destroyEntity (baseEntity);
                return sqd;
	}

	void SquadBuilder::setupInstancedMaterialToEntity(Ogre::Entity *ent)
	{
		for (Ogre::uint i = 0; i < ent->getNumSubEntities(); ++i)
		{
			Ogre::SubEntity* se = ent->getSubEntity(i);
			Ogre::String materialName= se->getMaterialName();
			se->setMaterialName(buildInstancedMaterial(materialName));
		}

	}

    Ogre::String SquadBuilder::buildInstancedMaterial(const Ogre::String &originalMaterialName)
	{

		if (Ogre::StringUtil::endsWith (originalMaterialName, "/instanced"))
			return originalMaterialName;

		Ogre::MaterialPtr originalMaterial = Ogre::MaterialManager::getSingleton ().getByName (originalMaterialName);

		// if originalMat doesn't exists use "Instancing" material name
        const Ogre::String instancedMaterialName (originalMaterial.isNull() ? "Instancing" : originalMaterialName + "/Instanced");
		Ogre::MaterialPtr  instancedMaterial = Ogre::MaterialManager::getSingleton ().getByName (instancedMaterialName);

		// already exists ?
		if (instancedMaterial.isNull())
		{
			instancedMaterial = originalMaterial->clone(instancedMaterialName);
			instancedMaterial->load();
			Ogre::Technique::PassIterator pIt = instancedMaterial->getBestTechnique ()->getPassIterator();

			while (pIt.hasMoreElements())
			{
				Ogre::Pass * const p = pIt.getNext();
				p->setVertexProgram("Instancing", true);
                p->setShadowCasterVertexProgram("InstancingShadowCaster");
			}
		}
		instancedMaterial->load();
		return instancedMaterialName;
	}




SquadBuilder::~SquadBuilder()
{
    //dtor
}
