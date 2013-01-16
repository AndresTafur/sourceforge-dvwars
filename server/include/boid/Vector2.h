#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <string>

/**
 * Auxiliar vector class, to represent world geometries.
 */
class Vector2
{
public:

        Vector2();


        Vector2(float coordX,float coordY);


        static Vector2 parseVector(std::string var, const char token);


        float length();

        /**
         * Assings a value to both components.
         * @param val Value to be assigned.
         */
        void operator = (float val);

        void operator += (Vector2 val);

        void operator -= (Vector2 val);

        Vector2 operator + (Vector2 val);

        Vector2 operator - (Vector2 val);


        Vector2 operator * (float val);

        Vector2 operator / (float val);


        virtual ~Vector2();

public:
float mXcoord;
float mYcoord;
};

#endif // _VECTOR2_H_
