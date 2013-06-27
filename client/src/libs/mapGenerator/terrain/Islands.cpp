/*
 *  Copyright (C) 2013 Jan Havran (sonicpp).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.    If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <cmath>
#include <stdexcept>

#include "Circle.h"

#define _USE_MATH_DEFINES

#include "Islands.h"
#include "Vect2f.h"

IslandsTerrain::IslandsTerrain(unsigned int seed, unsigned int islandCount)
:Terrain(seed),mIslandCount(islandCount)
{
    if (!mIslandCount) throw std::invalid_argument("Wrong number of islands");

    mRegions.insert (std::make_pair (-1.00, utils::Color (0, 2, 230, 255)));
    mRegions.insert (std::make_pair (-0.40, utils::Color (0, 2, 130, 255)));
    mRegions.insert (std::make_pair (-0.25, utils::Color (224, 224, 0, 255)));
    mRegions.insert (std::make_pair (-0.10, utils::Color (32, 160, 0, 255)));
    mRegions.insert (std::make_pair (0.10, utils::Color (43, 178, 32, 255)));
    mRegions.insert (std::make_pair (0.23, utils::Color (12, 120, 15, 255)));
    mRegions.insert (std::make_pair (0.43, utils::Color (32, 150, 31, 255)));
    mRegions.insert (std::make_pair (0.63, utils::Color (52, 160, 51, 255)));
    mRegions.insert (std::make_pair (0.85, utils::Color (128, 128, 128, 255)));
    mRegions.insert (std::make_pair (1.00, utils::Color (255, 255, 255, 255)));
}

int IslandsTerrain::generate()
{
    float angle = 2.0 * M_PI / mIslandCount;
    float ordinate = fabs(2.0 / cos(angle / 2.0));
    float hypotenuse = sqrt(ordinate * ordinate - 4.0) * 2.0;
    float radius;
    float lenToCenter;

    if (4 % mIslandCount == 0) {
        radius = MAP_SIZE / (2.0 + ((mIslandCount % 2 == 0)
	    ? sqrt(mIslandCount) : 0.0));
        lenToCenter = (MAP_SIZE_2 - radius) * M_SQRT2;
    }
    else {
        radius = (hypotenuse * MAP_SIZE_2) / ((ordinate + ordinate
	    + hypotenuse));
        lenToCenter = MAP_SIZE_2 - radius;
    }

    module::TranslatePoint islands[mIslandCount];
    module::Max maxims[(mIslandCount == 1) ? 1 : (mIslandCount - 1)];
    Vect2f vect(1.0, -1.0);
    vect.norm();
    vect = vect * lenToCenter;

    module::Circle circle;
    circle.SetRadius(radius * RELATIVE_ISLAND_SIZE);

    for (unsigned int i = 0; i < mIslandCount; i++) {
        islands[i].SetSourceModule(0, circle);
        islands[i].SetZTranslation(vect.x);
        islands[i].SetXTranslation(vect.y);
        vect.rotate(angle);

        if (i != 0) {
            if (i != 1)
	maxims[i - 1].SetSourceModule(0, maxims[i - 2]);

            maxims[i - 1].SetSourceModule(1, islands[i]);
        }
        else {
            maxims[0].SetSourceModule(0, islands[0]);
            maxims[0].SetSourceModule(1, islands[0]);
        }
    }

    module::Turbulence terrainType;
    terrainType.SetSourceModule(0, maxims[(mIslandCount == 1) ? 0 : (mIslandCount - 2)]);
    terrainType.SetFrequency(1.7);
    terrainType.SetPower(0.2);
    terrainType.SetSeed(mSeed);

    module::Billow water;
    water.SetFrequency (0.6);
    water.SetSeed(mSeed);

    module::ScaleBias waterBias;
    waterBias.SetSourceModule (0, water);
    waterBias.SetScale (0.25);
    waterBias.SetBias (-0.7);

    module::Billow grass;
    grass.SetFrequency (1.2);
    grass.SetSeed(mSeed);

    module::ScaleBias grassBias;
    grassBias.SetSourceModule (0, grass);
    grassBias.SetScale(0.4);
    grassBias.SetBias (0.4);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule (0, waterBias);
    finalTerrain.SetSourceModule (1, grassBias);
    finalTerrain.SetControlModule (terrainType);
    finalTerrain.SetBounds (0.0 , 10.0);
    finalTerrain.SetEdgeFalloff (0.325);

    mHeightMapBuilder.SetSourceModule (finalTerrain);
    mHeightMapBuilder.Build ();

    return 0;
}
