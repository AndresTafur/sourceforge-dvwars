#ifndef _VECT_2_F_H_
#define _VECT_2_F_H_

/**
 * 2D vector of float type.
 * Simple class for base work with vectors as rotation, skalar product etc.
 */
class Vect2f
{
    public:
	/// Value of x axis.
        float x;

	/// Value of y axis.
        float y;
    public:

	/**
	 * Constructor.
	 * <i>X</i> and <i>Y</i> attributes will be set to zero values.
	 */
       	Vect2f();

	/**
	 * Constructor.
	 * <i>X</i> and <i>Y</i> attributes will be set by parameters.
	 *
	 * @param xx X attribute will by set by this parameter.
	 * @param yy Y attribute will by set by this parameter.
	 */
       	Vect2f(float xx, float yy);

	/**
	 * Constructor.
	 * New vector will by set by 2 vectors as parameters.
	 * Value of new vector is given by the difference of <i>second</i>
	 * vector and <i>first</i> vector.
	 *
	 * @param first First vector by which is set this instance.
	 * @param second Second vector by which is set this instance.
	 */
       	Vect2f(const Vect2f first, const Vect2f second);

	/**
	 * Will rotate the vector for angle degrees.
	 *
	 * @param angle The angle by which will be vector rotated.
	 */
       	void rotate(const float angle);

	/**
	 * Will adjust vector to the unit length.
	 */
       	void unit(void);

	/**
	 * Inverts the direction of the vector.
	 */
       	void invert(void);

	/**
	 * Calculate and returns lenght of vector.
	 *
	 * @return Length of the vector.
	 */
       	float getLength(void) const;

	/**
	 * Returns angle of the vector (in radians).
	 *
	 * @return Angle of the vector (in radians).
	 */
       	float getAngle(void) const;

	/**
	 * Returns result of addition of two vectors.
	 * Will return result of addition between <i>this</i> object
	 * and object <i>next</i> specified as parameter.
	 *
	 * @param next Vector which will be added to object <i>this</i>.
	 * @return Result of addition of two vectors.
	 */
       	Vect2f operator+(const Vect2f &next) const;

	/**
	 * Returns result of subtract of two vectors.
	 * Will return result of subtract between <i>this</i> object
	 * and object <i>next</i> specified as parameter.
	 *
	 * @param next Vector which will be subtracted to object <i>this</i>.
	 * @return Result of subtract of two vectors.
	 */
       	Vect2f operator-(const Vect2f &next) const;

	/**
	 * Returns result of multiplication of vector and scalar.
	 * Will return result of multiplication between <i>this</i> vector
	 * and scalar <i>scalar</i> specified as parameter.
	 *
	 * @param scalar Scalar which will be multiplied to object <i>this</i>.
	 * @return Result of multiplication of vector and scalar.
	 */
       	Vect2f operator*(const float scalar) const;

	/**
	 * Returns new instance with result of multiplication
	 * of vector and scalar.
	 * Will return new instance of Vector with result of multiplication
	 * between <i>this</i> vector and scalar <i>scalar</i> specified
	 * as parameter.
	 *
	 * @param scalar Scalar which will be multiplied to object <i>this</i>.
	 * @return New instance with result of multiplication
	 */
       	Vect2f &operator *= (const float scalar);

	/**
	 * Returns result of division of vector and scalar.
	 * Will return result of division between <i>this</i> vector
	 * and scalar <i>scalar</i> specified as parameter.
	 *
	 * @param scalar Scalar which will be divided to object <i>this</i>.
	 * @return Result of division of vector and scalar.
	 */
       	Vect2f operator/(const float scalar) const;

	/**
	 * Returns new instance with result of division
	 * of vector and scalar.
	 * Will return new instance of Vector with result of division
	 * between <i>this</i> vector and scalar <i>scalar</i> specified
	 * as parameter.
	 *
	 * @param scalar Scalar which will be divided to object <i>this</i>.
	 * @return New instance with result of division
	 */
       	Vect2f &operator /= (const float scalar);

	/**
	 * Returns boolean result of comparsion of two vectors.
	 * Will return boolean result of comparsion between <i>this</i> object
	 * and object <i>next</i> specified as parameter.
	 *
	 * @param next Vector which will be compared with object <i>this</i>.
	 * @return True if vectors are equal.
	 * @return False if vectors are <b>not</b> equal.
	 */
       	bool operator==(const Vect2f &next) const;

	/**
	 * Returns <b>negated</b> boolean result of comparsion of two vectors.
	 * Will return <b>negated</b> boolean result of comparsion between
	 * <i>this</i> object and object <i>next</i> specified as parameter.
	 *
	 * @param next Vector which will be compared with object <i>this</i>.
	 * @return True if vectors are <b>not</b> equal.
	 * @return False if vectors are equal.
	 */
       	bool operator!=(const Vect2f &next) const;
};

#endif // _VECT_2_F_H_
