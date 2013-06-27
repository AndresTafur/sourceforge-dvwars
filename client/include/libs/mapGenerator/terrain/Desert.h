#ifndef _DESERT_H_
#define _DESERT_H_

#include "TerrainBase.h"

const float DEFAULT_DESERT_BOUND = 0.6; // <-1.0, 0.6> = 80%

class DesertTerrain : public Terrain
{
    public:
        DesertTerrain(unsigned int seed);
        int generate();
    private:
        float mDesertBound;
};

#endif // _DESERT_H_
