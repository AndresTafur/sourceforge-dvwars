#ifndef _COAST_H_
#define _COAST_H_

#include "TerrainBase.h"

/**
 * Generator of coast terrain.
 * Class used to generate and render terrain with a coast theme.
 */
class CoastTerrain : public Terrain
{
    public:
	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 */
        CoastTerrain (unsigned int seed);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate ();
};

#endif // _COAST_H_
