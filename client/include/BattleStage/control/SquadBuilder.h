#ifndef _SQUADBUILDER_H
#define _SQUADBUILDER_H

#include <Ogre.h>

#include <Squad.h>


/**
 * Build fast squads on demand using GPU instancing.
 */
class SquadBuilder
{
public:

        SquadBuilder();

        /**
         *  Handles GPU batch creation.
         *  This classes generates a new batch only if it's mesh has not been in a batch before,
         *  if the mesh is in a previous batch this one will be cloned and will be use the previous batchDimension value.
         *
         *  @param meshName  Mesh to be set in the batch.
         *  @param batchDimensions Size of each batch.
         *  @return A new Squad object pointer.
         */
        Squad* createSquad(std::string meshName, unsigned int id,unsigned short owner, unsigned int batchDimensions = 10, unsigned int speed = 10);


        virtual ~SquadBuilder();

protected:

        /**
         * Attach material to entity.
         * Utility method called by createSquad to set the mesh texture and material.
         *
         * @param entity Entity to setup it's material
         */
        void setupInstancedMaterialToEntity(Ogre::Entity* entity);


        /**
         *  Construct every 'material pass' defined for the material name.
         *  If the material has been already invoked, it will clone it.
         *
         *  @param originalMaterialName material to be obtined
         *  @return instanced material name.
         */
        Ogre::String buildInstancedMaterial(const Ogre::String &originalMaterialName);

private:
  long  pos;
  static unsigned long mUCount;
};

#endif // _SQUADBUILDER_H
