#ifndef _TERRAIN_BASE_H_
#define _TERRAIN_BASE_H_

#include <libnoise/noise.h>
#include "noiseutils.h"

const float MAP_SIZE = 4.0;
const float MAP_SIZE_2 = MAP_SIZE / 2.0;
const float IMG_SIZE = 513;

class Terrain
{
    public:
        Terrain(unsigned int seed);
        virtual ~Terrain();
        virtual int generate() = 0;
        int render(); 
        utils::Image getHeightMap();
        utils::Image getColorMap();
    protected:
        unsigned int mSeed;
        std::map<float,utils::Color> mRegions;
        utils::Image mHeightMap;
        utils::Image mColorMap;
        utils::NoiseMap mNoiseMap;
        utils::NoiseMapBuilderPlane mHeightMapBuilder;
};

#endif // _TERRAIN_BASE_H_
