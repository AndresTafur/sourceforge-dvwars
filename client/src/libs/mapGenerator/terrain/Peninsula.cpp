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

#include "Peninsula.h"
#include "Vect2f.h"

PeninsulaTerrain::PeninsulaTerrain(unsigned int seed, unsigned int peninsulaCount)
:Terrain(seed),mPeninsulaCount(peninsulaCount)
{
    if (!mPeninsulaCount) throw std::invalid_argument("Wrong number of peninsulas");

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

float PeninsulaTerrain::getEpsilon(float x, int sigdig)
{
    double eps = fabs (x);
    int i = 0;

    // eps needed in interval <0; 10)
    if (eps >= 10) {
        while (eps > 10)
            eps /= 10;
    }
    else if (eps < 0) {
        while (eps < 0)
            eps *= 10;
    }

    /* x /= 10^sigdig */
    while (i <= sigdig) {
        x = x / 10.0;
        i++;
    }

    return x / eps;
}

// compute radius from content using Newton's methot
float PeninsulaTerrain::getRadiusFromContent(float content, float lenToCenter, int sigdig)
{
    float y = 2 * content / (lenToCenter * lenToCenter);
    float s2 = 1.3; //something between 0 and PI/2
    float s = -s2;

    float eps = getEpsilon(s2, sigdig);

    while (fabs((s - s2)) > eps && s2 != s) {
        s = s2;
        s2 = s - 0.5 * (1.0 / tan(s)) + (cos(s) * cos(s) * \
	(y * (1.0 / tan(s)) - 1.0)) / (2.0 * (M_PI - s));
    }

    float alpha = M_PI - s2;

    return lenToCenter / cos(M_PI - alpha);
}

// TODO not working for num <= 1 and >= 15?
int PeninsulaTerrain::generate()
{
    float maxPeninsulaAngle = 2.0 * M_PI / mPeninsulaCount;
    float actualAngle;

    module::TranslatePoint islands[mPeninsulaCount];
    module::Max maxims[(mPeninsulaCount == 1) ? 1 : (mPeninsulaCount - 1)];
    Vect2f vect(1.0, -1.0);
    vect.norm();

    module::Circle circle[(mPeninsulaCount)];

    for (unsigned int i = 0; i < mPeninsulaCount; i++) {
        actualAngle = vect.getAngle();
        if (actualAngle < 0.0) actualAngle += M_PI;
        if (actualAngle > M_PI * 0.25 && actualAngle < M_PI * 0.75)
            vect *= MAP_SIZE_2 / fabs(vect.y);
        else
            vect *= MAP_SIZE_2 / fabs(vect.x);
        islands[i].SetSourceModule(0, circle[i]);
        islands[i].SetZTranslation(vect.x);
        islands[i].SetXTranslation(vect.y);
        vect.rotate(maxPeninsulaAngle);
        if (i != 0) {
            if (i == 1) {
	maxims[i - 1].SetSourceModule(1, islands[i]);
            }
            else {
	maxims[i - 1].SetSourceModule(0, maxims[i - 2]);
	maxims[i - 1].SetSourceModule(1, islands[i]);
            }
        }
        else {
            maxims[0].SetSourceModule(0, islands[0]);
            maxims[0].SetSourceModule(1, islands[0]);
        }
    }

    float maxRadius =
        sqrt(pow(islands[0].GetZTranslation() -
        islands[1].GetZTranslation(), 2.0) +
        pow(islands[0].GetXTranslation() -
        islands[1].GetXTranslation(), 2.0)) / 2.0;
    float maxContent = M_PI * maxRadius * maxRadius / 4.0;

    for (unsigned int i = 0; i < mPeninsulaCount; i++) {
        float lenToCenter = (fabs(islands[i].GetZTranslation()) >=
	MAP_SIZE_2 * 0.999) ? // >= map size (*0.999 because of float's inaccuracy)
            fabs(islands[i].GetXTranslation()) :
            fabs(islands[i].GetZTranslation());

        lenToCenter = MAP_SIZE_2 - lenToCenter;

        if (lenToCenter <= 0.001) // == 0 (+/- 0.001)
            circle[i].SetRadius(maxRadius * RELATIVE_PENINSULA_SIZE);
        else if (lenToCenter >= maxRadius / M_SQRT2)
            circle[i].SetRadius(maxRadius * RELATIVE_PENINSULA_SIZE / M_SQRT2);
        else
            circle[i].SetRadius(getRadiusFromContent(maxContent,
	    lenToCenter, 6) * RELATIVE_PENINSULA_SIZE);
    }
    module::Turbulence terrainType;
    terrainType.SetSourceModule(0, maxims[(mPeninsulaCount == 1) ? 0 : (mPeninsulaCount - 2)]);
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

