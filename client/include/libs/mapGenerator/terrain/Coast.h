#ifndef _COAST_H_
#define _COAST_H_

#include "TerrainBase.h"

class CoastTerrain : public Terrain
{
    public:
        CoastTerrain (unsigned int seed);
        int generate ();
};

#endif // _COAST_H_
