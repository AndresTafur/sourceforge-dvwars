#ifndef _WINTER_H_
#define _WINTER_H_

#include "TerrainBase.h"

const float DEFAULT_WINTER_BOUND = 0.5; // <-1.0, 0.5> = 75%

class WinterTerrain : public Terrain
{
    public:
        WinterTerrain (unsigned int seed);
        int generate ();
    private:
        float mWinterBound;
};

#endif // _WINTER_H_
