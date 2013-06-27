#ifndef _VECT_2_F_H_
#define _VECT_2_F_H_

class Vect2f
{
    public:
        float x;
        float y;
    public:
       	Vect2f();
       	Vect2f(float xx, float yy);
       	Vect2f(const Vect2f first, const Vect2f second);
       	void rotate(const float angle);
       	void norm(void);
       	void invert(void);
       	float getLength(void) const;
       	float getAngle(void) const;
       	Vect2f operator+(const Vect2f &next) const;
       	Vect2f operator-(const Vect2f &next) const;
       	Vect2f operator*(const float scalar) const;
       	Vect2f &operator *= (const float scalar);
       	Vect2f operator/(const float scalar) const;
       	Vect2f &operator /= (const float scalar);
       	bool operator==(const Vect2f &next) const;
       	bool operator!=(const Vect2f &next) const;
};

#endif // _VECT_2_F_H_
