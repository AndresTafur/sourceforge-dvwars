#ifndef _ISLANDS_H_
#define _ISLANDS_H_

#include "TerrainBase.h"

const float RELATIVE_ISLAND_SIZE = 0.7;

class IslandsTerrain : public Terrain
{
    public:
        IslandsTerrain (unsigned int seed, unsigned int islandCount = 2);
        int generate();
    private:
        unsigned int mIslandCount;
};

#endif // _ISLANDS_H_
