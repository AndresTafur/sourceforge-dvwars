#ifndef _ISLANDS_H_
#define _ISLANDS_H_

#include "TerrainBase.h"

const float RELATIVE_ISLAND_SIZE = 0.7;

/**
 * Generator of islands terrain.
 * Class used to generate and render terrain with a islands theme.
 */
class IslandsTerrain : public Terrain
{
    public:

	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 * @param islandCount Number of islands to be generated.
	 */
        IslandsTerrain (unsigned int seed, unsigned int islandCount = 2);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate();
    private:
        unsigned int mIslandCount;
};

#endif // _ISLANDS_H_
