#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <math.h>
#include "enum.h"

class Vector3f {

public:
        float X, Y, Z;
        Vector3f(const float x, const float y, const float z);
	~Vector3f();

        inline float getSum() const{
                return X + Y + Z;
	}

        float getMagnitude() const;
        void normalize() const;
        //Float Operations
        Vector3f operator/= (const float a);
        Vector3f operator*= (const float a);
        Vector3f operator+= (const float a);
        Vector3f operator-= (const float a);

        //Vector Operations
        Vector3f operator/= (const Vector3f& vector);
        Vector3f operator*= (const Vector3f& vector);
        Vector3f operator+= (const Vector3f& vector);
        Vector3f operator-= (const Vector3f& vector);
};

//-------Float-------

Vector3f operator+ (Vector3f a, const float b);
Vector3f operator- (Vector3f a, const float b);
Vector3f operator/ (Vector3f a, const float b);
Vector3f operator* (Vector3f a, const float b);
//------Vector--------
Vector3f operator+ (Vector3f a, const Vector3f& b);
Vector3f operator- (Vector3f a, const Vector3f& b);
Vector3f operator/ (Vector3f a, const Vector3f& b);
Vector3f operator* (Vector3f a, const Vector3f& b);

float compdist3f(const Vector3f& vec_a, const Vector3f& vec_b);

float vectprod3f(const Vector3f& vecta,const Vector3f& vectb);

float dotprod3f(const Vector3f& vecta, const Vector3f& vectb);

AngleType getAngleType(const Vector3f& a, const Vector3f& b);

float getAngle(const Vector3f& a, const Vector3f& b);

float projvectf(const Vector3f& v, const Vector3f& n);
#endif //VECTOR3F_H
