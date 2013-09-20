#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <iostream>

/**
 * Generator of height and color maps.
 * This class can generate, render and save multiple types of maps.
 */
class MapGenerator
{
    public:

        /**
         * Static method used to generate, render and save map.
         * This method will generate (using seed), render and save
         * multiple types of maps into specified location.
         *
         * @param type Type of map which will be generated:
         * - \ref CoastTerrain "Coast"
         * - \ref DesertTerrain "Desert"
         * - \ref GrassTerrain "Grass"
         * - \ref IslandsTerrain "Islands"
         * - \ref PeninsulaTerrain "Peninsula"
         * - \ref WinterTerrain "Winter"
         * @param location Location where map images will be saved.
         * @param seed Seed used to generate map.
         * @see Terrain
         */
        static void generateMap (std::string type, std::string location, int seed);
};

#endif // _MAP_GENERATOR_H_
