#ifndef _TERRAIN_BASE_H_
#define _TERRAIN_BASE_H_

#include <libnoise/noise.h>
#include "noiseutils.h"

const float MAP_SIZE = 4.0;
const float MAP_SIZE_2 = MAP_SIZE / 2.0;
const float IMG_SIZE = 513;

/**
 * An abstract class used to generate terrain.
 * Can generate terrain and render color and height map.
 */
class Terrain
{
    public:
	/**
	 * Constructor.
	 *
	 * @param seed Seed used to generate map.
	 */
        Terrain(unsigned int seed);

	/**
	 * Virtual destructor.
	 */
        virtual ~Terrain();

	/**
	 * A pure virtual member.
	 * Will generate noise map using \ref mSeed "seed" number.
	 * 
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        virtual int generate() = 0;

	/**
	 * Will render height and color map using noise map.

	 * @pre generate() has been previously called.
	 *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int render(); 

        /**
         *  Returns the height map of the image.
         *
         *  @return The height map of the image.
         */
        utils::Image getHeightMap();

        /**
         *  Returns the color map of the image.
         *
         *  @return The color map of the image.
         */
        utils::Image getColorMap();

    protected:
	/// Seed used to generate map
        unsigned int mSeed;

	/// Container used for storing pairs of height:color
        std::map<float,utils::Color> mRegions;

	/// Height map image
        utils::Image mHeightMap;

	/// Color map image
        utils::Image mColorMap;

	/// Base noise map
        utils::NoiseMap mNoiseMap;

	/// Builder used to create noise map
        utils::NoiseMapBuilderPlane mNoiseMapBuilder;
};

#endif // _TERRAIN_BASE_H_
