#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <math.h>
#include "enum.h"

class Vect3f {

public:
        float X, Y, Z;
        Vect3f(const float x, const float y, const float z);
        ~Vect3f();

        inline float getSum() const{
                return X + Y + Z;
	}

        float getMagnitude() const;
        void normalize();
        //Float Operations
        Vect3f& operator/= (const float a);
        Vect3f& operator*= (const float a);
        Vect3f& operator+= (const float a);
        Vect3f& operator-= (const float a);

        //Vector Operations
        Vect3f& operator/= (const Vect3f& vector);
        Vect3f& operator*= (const Vect3f& vector);
        Vect3f& operator+= (const Vect3f& vector);
        Vect3f& operator-= (const Vect3f& vector);
};

//-------Float-------

Vect3f& operator+ (Vect3f& a, const float b);
Vect3f& operator- (Vect3f& a, const float b);
Vect3f& operator/ (Vect3f& a, const float b);
Vect3f& operator* (Vect3f& a, const float b);
//------Vector--------
Vect3f& operator+ (Vect3f& a, const Vect3f& b);
Vect3f& operator- (Vect3f& a, const Vect3f& b);
Vect3f& operator/ (Vect3f& a, const Vect3f& b);
Vect3f& operator* (Vect3f& a, const Vect3f& b);

float compdist3f(const Vect3f& vec_a, const Vect3f& vec_b);

float vectprod3f(const Vect3f& vecta,const Vect3f& vectb);

float dotprod3f(const Vect3f& vecta, const Vect3f& vectb);

AngleType getAngleType(const Vect3f& a, const Vect3f& b);

float getAngle(const Vect3f& a, const Vect3f& b);

float projvectf(const Vect3f& v, const Vect3f& n);
#endif //VECTOR3F_H
