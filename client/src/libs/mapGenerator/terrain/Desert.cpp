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

#include "Desert.h"

DesertTerrain::DesertTerrain(unsigned int seed)
:Terrain(seed), mDesertBound(DEFAULT_DESERT_BOUND)
{
    mRegions.insert (std::make_pair (-1.00, utils::Color (200, 154, 30, 255)));
    mRegions.insert (std::make_pair (-0.40, utils::Color (196, 186, 23, 255)));
    mRegions.insert (std::make_pair (-0.15, utils::Color (181, 173, 14, 255)));
    mRegions.insert (std::make_pair (-0.08, utils::Color (157, 164, 16, 255)));
    mRegions.insert (std::make_pair (0.1, utils::Color (118, 137, 3, 255)));
    mRegions.insert (std::make_pair (0.20, utils::Color (54, 98, 16, 255)));
    mRegions.insert (std::make_pair (0.35, utils::Color (62, 90, 12, 255)));
    mRegions.insert (std::make_pair (0.55, utils::Color (75, 77, 56, 255)));
    mRegions.insert (std::make_pair (1.0, utils::Color (112, 91, 63, 255)));
}

int DesertTerrain::generate()
{
    module::Billow sandTerrain;
    sandTerrain.SetFrequency (1.2);
    sandTerrain.SetSeed(mSeed);

    module::RidgedMulti mountainTerrain;
    mountainTerrain.SetSeed(mSeed);

    module::ScaleBias flatSand;
    flatSand.SetSourceModule (0, sandTerrain);
    flatSand.SetScale (0.3);
    flatSand.SetBias (-0.5);

    module::ScaleBias flatMountain;
    flatMountain.SetSourceModule (0, mountainTerrain);
    flatMountain.SetScale (0.6);
    flatMountain.SetBias (0.25);

    module::Perlin terrainType;
    terrainType.SetSeed(mSeed);
    terrainType.SetFrequency (0.8);
    terrainType.SetPersistence (0.5);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule (0, flatSand);
    finalTerrain.SetSourceModule (1, flatMountain);
    finalTerrain.SetControlModule (terrainType);
    finalTerrain.SetBounds (mDesertBound, 10.0);
    finalTerrain.SetEdgeFalloff (0.125);
    
    mNoiseMapBuilder.SetSourceModule (finalTerrain);
    mNoiseMapBuilder.Build ();

    return 0;
}
