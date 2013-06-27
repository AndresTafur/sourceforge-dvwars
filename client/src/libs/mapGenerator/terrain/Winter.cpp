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

#include "Winter.h"

WinterTerrain::WinterTerrain(unsigned int seed)
:Terrain(seed), mWinterBound(DEFAULT_WINTER_BOUND)
{
    mRegions.insert (std::make_pair (-1.00, utils::Color (230, 230, 230, 255)));
    mRegions.insert (std::make_pair (0.00, utils::Color (230, 230, 230, 255)));
    mRegions.insert (std::make_pair (1.0, utils::Color (39, 25, 25, 255)));
}

int WinterTerrain::generate()
{
    module::Billow snowTerrain;
    snowTerrain.SetFrequency (0.67);
    snowTerrain.SetSeed(mSeed);

    module::ScaleBias scaledSnowTerrain;
    scaledSnowTerrain.SetSourceModule (0, snowTerrain);
    scaledSnowTerrain.SetScale (0.35);
    scaledSnowTerrain.SetBias (-0.6);

    module::RidgedMulti mountainTerrain;
    mountainTerrain.SetFrequency(2.2);
    mountainTerrain.SetSeed(mSeed);

    module::ScaleBias scaledMountainTerrain;
    scaledMountainTerrain.SetSourceModule (0, mountainTerrain);
    scaledMountainTerrain.SetScale(0.8);
    scaledMountainTerrain.SetBias (0.15);

    module::Perlin terrainType;
    terrainType.SetSeed(mSeed);
    terrainType.SetFrequency (0.6);
    terrainType.SetPersistence (0.5);
    
    module::Select finalTerrain;
    finalTerrain.SetSourceModule (0, scaledSnowTerrain);
    finalTerrain.SetSourceModule (1, scaledMountainTerrain);
    finalTerrain.SetControlModule (terrainType);
    finalTerrain.SetBounds (mWinterBound, 10.0);
    finalTerrain.SetEdgeFalloff (0.125);

    mHeightMapBuilder.SetSourceModule (finalTerrain);
    mHeightMapBuilder.Build ();

    return 0;
}
