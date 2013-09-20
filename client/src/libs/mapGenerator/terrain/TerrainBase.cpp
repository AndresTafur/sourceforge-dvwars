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

#include "TerrainBase.h"

Terrain::Terrain(unsigned int seed)
:mSeed(seed)
{
    mNoiseMapBuilder.SetDestNoiseMap (mNoiseMap);
    mNoiseMapBuilder.SetDestSize (IMG_SIZE, IMG_SIZE);
    mNoiseMapBuilder.SetBounds (
            -MAP_SIZE_2, MAP_SIZE_2, -MAP_SIZE_2, MAP_SIZE_2);
}

Terrain::~Terrain()
{
}

utils::Image Terrain::getHeightMap()
{
    return mHeightMap;
}

utils::Image Terrain::getColorMap()
{
    return mColorMap;
}

int Terrain::render()
{
    utils::RendererImage renderHeight, renderColor;
    
    renderHeight.SetSourceNoiseMap (mNoiseMap);
    renderHeight.SetDestImage (mHeightMap);
    renderHeight.Render ();

    renderColor.SetSourceNoiseMap (mNoiseMap);
    renderColor.SetDestImage (mColorMap);
    renderColor.ClearGradient ();

    std::map < float, utils::Color >::iterator i;
    for (i = mRegions.begin (); i != mRegions.end (); i++)
        renderColor.AddGradientPoint (i->first, i->second);

    renderColor.EnableLight ();
    renderColor.SetLightContrast (3.0);
    renderColor.SetLightBrightness (2.0);
    renderColor.Render ();

    return 0;
}
