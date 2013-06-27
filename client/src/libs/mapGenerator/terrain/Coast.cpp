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

#include "Circle.h"
#include "Coast.h"

CoastTerrain::CoastTerrain(unsigned int seed)
:Terrain(seed)
{
    mRegions.insert (std::make_pair (-1.00, utils::Color (0, 2, 230, 255)));
    mRegions.insert (std::make_pair (-0.40, utils::Color (0, 2, 130, 255)));
    mRegions.insert (std::make_pair (-0.30, utils::Color (224, 224, 0, 255)));
    mRegions.insert (std::make_pair (-0.20, utils::Color (32, 160, 0, 255)));
    mRegions.insert (std::make_pair (0.20, utils::Color (2, 210, 12, 255)));
    mRegions.insert (std::make_pair (0.43, utils::Color (32, 120, 21, 255)));
    mRegions.insert (std::make_pair (0.63, utils::Color (22, 140, 41, 255)));
    mRegions.insert (std::make_pair (0.75, utils::Color (128, 128, 128, 255)));
    mRegions.insert (std::make_pair (1.00, utils::Color (255, 255, 255, 255)));
}

//TODO use cylinders module instead of circle in the future
// (cylinders bug already reported on libnoise tracker)
int CoastTerrain::generate()
{
    module::Circle coast;
    coast.SetRadius(MAP_SIZE * 1.2);

    module::TranslatePoint translateCoast;
    translateCoast.SetSourceModule(0, coast);
    translateCoast.SetXTranslation(-MAP_SIZE);

    module::Turbulence terrainType;
    terrainType.SetSourceModule(0, translateCoast);
    terrainType.SetFrequency(1.5);
    terrainType.SetPower(0.9);
    terrainType.SetSeed(mSeed);


    module::Billow water;
    water.SetFrequency (0.6);
    water.SetSeed(mSeed);

    module::ScaleBias waterScale;
    waterScale.SetSourceModule (0, water);
    waterScale.SetScale (0.15);
    waterScale.SetBias (-0.7);


    module::Billow baseFlatTerrain;
    baseFlatTerrain.SetSeed (mSeed);
    baseFlatTerrain.SetFrequency (1.1);

    module::ScaleBias flatTerrain;
    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.4);
    flatTerrain.SetBias (0.3);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule (0, waterScale);
    finalTerrain.SetSourceModule (1, flatTerrain);
    finalTerrain.SetControlModule (terrainType);
    finalTerrain.SetBounds (0.0 , 10.0);
    finalTerrain.SetEdgeFalloff (0.325);
    
    mHeightMapBuilder.SetSourceModule (finalTerrain);
    mHeightMapBuilder.Build ();

    return 0;
}
