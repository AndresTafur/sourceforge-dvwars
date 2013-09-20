#ifndef _DESERT_H_
#define _DESERT_H_

#include "TerrainBase.h"

const float DEFAULT_DESERT_BOUND = 0.6; // <-1.0, 0.6> = 80%

/**
 * Generator of desert terrain.
 * Class used to generate and render terrain with a desert theme.
 */
class DesertTerrain : public Terrain
{
    public:
	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 */
        DesertTerrain(unsigned int seed);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate();
    private:
        float mDesertBound;
};

#endif // _DESERT_H_
