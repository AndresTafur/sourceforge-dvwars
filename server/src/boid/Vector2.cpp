#include "Vector2.h"

#include <math.h>
#include <stdlib.h>

Vector2::Vector2()
{
    mXcoord = 0;
    mYcoord = 0;
}


Vector2::Vector2(float coordX,float coordY)
{
    mXcoord = coordX;
    mYcoord = coordY;
}


    Vector2 Vector2::parseVector(std::string var, const char token)
    {
      float posX, posY;

                  posX    = atof(var.substr(0,var.find(token)).c_str());
                  posY    = atof(var.substr(var.find(token)+1).c_str());

            return Vector2(posX,posY);
    }

    float Vector2::length()
    {
        return sqrt( mXcoord*mXcoord + mYcoord*mYcoord );
    }


    void Vector2::operator = (float val)
    {
        mXcoord = val;
        mYcoord = val;
    }


    void Vector2::operator += (Vector2 val)
    {
        mXcoord += val.mXcoord;
        mYcoord += val.mYcoord;
    }

    void Vector2::operator -= (Vector2 val)
    {
        mXcoord -= val.mXcoord;
        mYcoord -= val.mYcoord;
    }


    Vector2 Vector2::operator + (Vector2 val)
    {
      Vector2 obj;

            obj.mXcoord = val.mXcoord + mXcoord;
            obj.mYcoord = val.mYcoord + mYcoord;
            return obj;

    }

    Vector2 Vector2::operator - (Vector2 val)
    {
      Vector2 obj;

            obj.mXcoord = mXcoord - val.mXcoord;
            obj.mYcoord = mYcoord - val.mYcoord;
            return obj;
   }


   Vector2 Vector2::operator * (float val)
   {
      Vector2 obj;

            obj.mXcoord = mXcoord * val;
            obj.mYcoord = mYcoord * val;
            return obj;
   }

   Vector2 Vector2::operator / (float val)
   {
      Vector2 obj;

            obj.mXcoord = mXcoord / val;
            obj.mYcoord = mYcoord / val;
            return obj;
   }


Vector2::~Vector2()
{
    //dtor
}
