#ifndef _PENINSULA_H_
#define _PENINSULA_H_

#include "TerrainBase.h"

const float RELATIVE_PENINSULA_SIZE = 0.7;

class PeninsulaTerrain : public Terrain
{
    public:
        PeninsulaTerrain (unsigned int seed, unsigned int peninsulaCount = 2);
        int generate();
    private:
        unsigned int mPeninsulaCount;
        float getEpsilon(float x, int sigdig);
        float getRadiusFromContent(float content, float lenToCenter, int sigdig);
};

#endif // _PENINSULA_H_
