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

#include <cmath>

#include "Vect2f.h"

Vect2f::Vect2f()
:x(0.0), y(0.0)
{
}

Vect2f::Vect2f(float xx, float yy)
:x(xx), y(yy)
{
}

Vect2f::Vect2f(const Vect2f first, const Vect2f second)
:x(second.x - first.x), y(second.y - first.y)
{
}

void Vect2f::rotate(float angle)
{
    float temp = x;
    float cosinus = cos(angle), sinus = sin(angle);

    x = x * cosinus + y * sinus;
    y = y * cosinus - temp * sinus;
}
    

void Vect2f::norm(void)
{
    float length = getLength();
    x = x / length;
    y = y / length;
}

void Vect2f::invert(void)
{
    x = -x;
    y = -y;
}	

float Vect2f::getLength(void) const
{
    return sqrt(x * x + y * y);
}

float Vect2f::getAngle(void) const
{
    return atan(y / x);
}

Vect2f Vect2f::operator+(const Vect2f &next) const
{
    return Vect2f(x + next.x, y + next.y);
}

Vect2f Vect2f::operator-(const Vect2f &next) const
{
    return Vect2f(x - next.x, y - next.y);
}

Vect2f Vect2f::operator*(const float scalar) const
{
    return Vect2f(x * scalar, y * scalar);
}

Vect2f & Vect2f::operator *= (const float scalar)
{
    x *= scalar, y *= scalar;
    return *this;
}

Vect2f Vect2f::operator/(const float scalar) const
{
    return Vect2f(x / scalar, y / scalar);
}

Vect2f & Vect2f::operator /= (const float scalar)
{
    x /= scalar, y /= scalar;
    return *this;
}

bool Vect2f::operator==(const Vect2f &next) const
{
    return x == next.x && y == next.y;
}

bool Vect2f::operator!=(const Vect2f &next) const
{
    return !(*this == next);
}

