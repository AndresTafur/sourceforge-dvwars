#ifndef _GRASS_H_
#define _GRASS_H_

#include "TerrainBase.h"

const float DEFAULT_GRASS_BOUND = 0.6; // <-1.0, 0.6> = 80%

class GrassTerrain : public Terrain
{
    public:
        GrassTerrain(unsigned int seed);
        int generate();
    private:
        float mGrassBound;
};

#endif // _GRASS_H_
