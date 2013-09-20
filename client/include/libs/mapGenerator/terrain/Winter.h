#ifndef _WINTER_H_
#define _WINTER_H_

#include "TerrainBase.h"

const float DEFAULT_WINTER_BOUND = 0.5; // <-1.0, 0.5> = 75%

/**
 * Generator of winter terrain.
 * Class used to generate and render terrain with a winter theme.
 */
class WinterTerrain : public Terrain
{
    public:

	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 */
        WinterTerrain (unsigned int seed);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate ();
    private:
        float mWinterBound;
};

#endif // _WINTER_H_
