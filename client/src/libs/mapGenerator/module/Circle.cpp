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

#include <libnoise/misc.h>
#include <cmath>

#include "Circle.h"

using namespace noise::module;

Circle::Circle ()
: Module (GetSourceModuleCount ()), m_radius (DEFAULT_CIRCLE_RADIUS)
{
}

double Circle::GetValue (double x, double y, double z) const
{
    double len = 1.0 / m_radius;
    x *= len;
    y *= len;
    z *= len;
    
    double distFromCenter = sqrt (x * x + y * y + z * z);

    if (distFromCenter > 2.0)
        return -1.0;

    return -(1 - 2.0 * cos(distFromCenter));
}

