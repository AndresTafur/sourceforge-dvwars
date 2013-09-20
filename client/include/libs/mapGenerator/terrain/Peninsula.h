#ifndef _PENINSULA_H_
#define _PENINSULA_H_

#include "TerrainBase.h"

const float RELATIVE_PENINSULA_SIZE = 0.7;

/**
 * Generator of peninsula terrain.
 * Class used to generate and render terrain with a peninsula theme.
 */
class PeninsulaTerrain : public Terrain
{
    public:

	/**
	 * Constructor
	 *
	 * @param seed Seed used to generate map.
	 * @param peninsulaCount Number of peninsulas to be generated.
	 */
        PeninsulaTerrain (unsigned int seed, unsigned int peninsulaCount = 2);

	/**
	 * Will generate noise map using \ref Terrain::mSeed "seed" number.
         *
	 * @return 0 on Success.
	 * @return 1 on Failure.
	 */
        int generate();
    private:

	/**
	 * Computes and returns <i>epsilon</i>.
	 * Will compute <i>epsilon</i> number of number <i>x</i> with <i>sigdig</i>
	 * precision.
	 *
	 * @param x Number for which will be epsilon number calculated.
	 * @param sigdig Precision for calculated epsilon.
	 * @return Calculated epsilon for given number.
	 */

        float getEpsilon(float x, int sigdig);

	/**
	 * Computes and returns radius of circle by given content.
	 * Will compute radius of circle in the corner by given content.
	 *
	 * @param content Content of circle.
	 * @param lenToCenter Distance from corner to middle of circle.
	 * @param sigdig Precision for calculated radius.
	 * @return Calculated radius for given circle.
	 */
        float getRadiusFromContent(float content, float lenToCenter, int sigdig);

        unsigned int mPeninsulaCount;
};

#endif // _PENINSULA_H_
