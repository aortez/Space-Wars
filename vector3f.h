#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <math.h>
#include "enum.h"

class Vector3f {
	
private:
	
public:
	Vector3f(float x, float y, float z);
	~Vector3f();
	inline float getSum() {
		return x + y + z;
	}
	float x, y, z;
	float getMagnitude() const;
	void multiplyByScalar(float scalar);
	void divideByScalar(float scalar);
	void normalize();
	Vector3f operator/(const Vector3f& vector);
	Vector3f operator/=(const Vector3f& vector);
	Vector3f operator*=(const Vector3f& vector);
	Vector3f operator*(const Vector3f& vector);
	Vector3f operator+(const Vector3f& vector);
	Vector3f operator+=(const Vector3f& vector);
	Vector3f operator-(const Vector3f& vector);
	Vector3f operator-=(const Vector3f& vector);
};

float compdist3f(const Vector3f& vec_a, const Vector3f& vec_b);

float vectprod3f(const Vector3f& vecta,const Vector3f& vectb);

float dotprod3f(const Vector3f& vecta, const Vector3f& vectb);

AngleType getAngleType(const Vector3f& a, const Vector3f& b);

float getAngle(const Vector3f& a, const Vector3f& b);

float projvectf(const Vector3f& v, const Vector3f& n);
#endif //VECTOR3F_H
