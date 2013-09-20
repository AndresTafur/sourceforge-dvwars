#ifndef _GRASS_H_
#define _GRASS_H_

#include "TerrainBase.h"

const float DEFAULT_GRASS_BOUND = 0.6; // <-1.0, 0.6> = 80%

/**
 * Generator of grass terrain.
 * Class used to generate and render terrain with a grass theme.
 */
class GrassTerrain : public Terrain
{
    public:

	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 */
        GrassTerrain(unsigned int seed);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate();
    private:
        float mGrassBound;
};

#endif // _GRASS_H_
