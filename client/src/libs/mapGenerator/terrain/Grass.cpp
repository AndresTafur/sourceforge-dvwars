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

#include "Grass.h"

GrassTerrain::GrassTerrain(unsigned int seed)
    :Terrain(seed), mGrassBound(DEFAULT_GRASS_BOUND)
{
    mRegions.insert (std::make_pair (-1.00, utils::Color (121, 178, 9, 255)));
    mRegions.insert (std::make_pair (-0.85, utils::Color (88, 164, 20, 255)));
    mRegions.insert (std::make_pair (-0.25, utils::Color (55, 114, 3, 255)));
    mRegions.insert (std::make_pair (-0.0, utils::Color (61, 167, 24, 255)));
    mRegions.insert (std::make_pair (0.30, utils::Color (17, 142, 41, 255)));
    mRegions.insert (std::make_pair (0.55, utils::Color (52, 81, 53, 255)));
    mRegions.insert (std::make_pair (0.70, utils::Color (108, 128, 108, 255)));
    mRegions.insert (std::make_pair (0.85, utils::Color (63, 98, 58, 255)));
    mRegions.insert (std::make_pair (1.00, utils::Color (125, 155, 125, 255)));
}

int GrassTerrain::generate()
{
    module::RidgedMulti mountainTerrain;
    mountainTerrain.SetSeed (mSeed);
    mountainTerrain.SetFrequency (1.45);

    module::Billow baseFlatTerrain;
    baseFlatTerrain.SetSeed (mSeed);
    baseFlatTerrain.SetFrequency (0.8);

    module::ScaleBias flatTerrain;
    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.525);
    flatTerrain.SetBias (-0.4);

    module::ScaleBias flatMountain;
    flatMountain.SetSourceModule (0, mountainTerrain);
    flatMountain.SetScale (0.65);
    flatMountain.SetBias (0.55);

    module::Perlin terrainType;
    terrainType.SetFrequency (1.2);
    terrainType.SetPersistence (0.15);
    terrainType.SetSeed (mSeed);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule (0, flatTerrain);
    finalTerrain.SetSourceModule (1, flatMountain);
    finalTerrain.SetControlModule (terrainType);
    finalTerrain.SetBounds (mGrassBound, 10.0);
    finalTerrain.SetEdgeFalloff (0.225);

    mHeightMapBuilder.SetSourceModule (finalTerrain);
    mHeightMapBuilder.Build ();

    return 0;
}
