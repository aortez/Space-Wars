#include "vector3f.h"

Vector3f::Vector3f(const float x, const float y, const float z) {
        this->X = x;
        this->Y = y;
        this->Z = z;
}

Vector3f::~Vector3f() {
	
	
}

float Vector3f::getMagnitude() const{
    return sqrt(
        (this->X * this->X)
    +   (this->Y * this->Y)
    +   (this->Z * this->Z)
    );
		
}

void Vector3f::normalize() const {
    const float magnitude = getMagnitude();

    const bool notZero =
    (magnitude != 0.0f && (this->X != 0.0f && this->Y != 0.0f && this->Z != 0.0f));

    if (notZero) {
            this->X /= getMagnitude();
            this->Y /= getMagnitude();
            this->Z /= getMagnitude();
    } else {
            std::cout << "Cannot normalize Vector3f: the x, y, or z coordinate or the magnitude has resulted in zero." << std::endl;
    }
	
}

Vector3f Vector3f::operator/=(const Vector3f& vec) {

    bool vecNoZero = (vec.X != 0.0f && vec.Y != 0.0f && vec.Z != 0.0f);
    bool thisNoZero = (this->X != 0.0f && this->Y != 0.0f && this->Z != 0.0f);

    if (vecNoZero && thisNoZero) {
            this->X /= vec.X;
            this->Y /= vec.Y;
            this->Z /= vec.Z;
    }

    return *this;
}


Vector3f Vector3f::operator*=(const Vector3f& vec) {
    this->X *= vec.X;
    this->Y *= vec.Y;
    this->Z *= vec.Z;

    return *this;
}

Vector3f Vector3f::operator+=(const Vector3f& vec) {
    this->X += vec.X;
    this->Y += vec.Y;
    this->Z += vec.Z;

    return *this;
}

Vector3f Vector3f::operator-=(const Vector3f& vec) {
    this->X -= vec.X;
    this->Y -= vec.Y;
    this->Z -= vec.Z;

    return *this;
}

//Float Operations

Vector3f Vector3f::operator*= (const float a) {

    this->X *= a;
    this->Y *= a;
    this->Z *= a;

    return *this;
}

Vector3f Vector3f::operator/= (const float a) {
    this->X /= a;
    this->Y /= a;
    this->Z /= a;

    return *this;
}

Vector3f Vector3f::operator+= (const float a) {
    this->X += a;
    this->Y += a;
    this->Z += a;

    return *this;
}

Vector3f Vector3f::operator-= (const float a) {
    this->X -= a;
    this->Y -= a;
    this->Z -= a;

    return *this;
}

//-------Float-------

Vector3f operator+ (Vector3f a, const float b) {
    a += b;

    return a;
}
Vector3f operator- (Vector3f a, const float b) {
    a -= b;

    return a;
}
Vector3f operator/ (Vector3f a, const float b) {
    if (b != 0.0f) //check for divide by zero
        a /= b;

    return a;
}
Vector3f operator* (Vector3f a, const float b) {
    a *= b;

    return a;
}

//------Vector--------

Vector3f operator+ (Vector3f a, const Vector3f& b) {
    a += b;

    return a;
}
Vector3f operator- (Vector3f a, const Vector3f& b) {
    a -= b;

    return a;
}
Vector3f operator/ (Vector3f a, const Vector3f& b) {
    const bool notZero =
        (b.X != 0.0f && b.Y != 0.0f && b.Z != 0.0f);

    if (notZero)
        a /= b;

    return a;
}
Vector3f operator* (Vector3f a, const Vector3f& b) {
    a *= b;

    return a;
}

/*compute the distance between two 3D vectors*/

float compdist3f(const Vector3f& vec_a,const Vector3f& vec_b) {
    float x = vec_a.X - vec_b.X;
    float y = vec_a.Y - vec_b.Y;
    float z = vec_a.Z - vec_b.Z;

    return sqrt((x * x) + (y * y) + (z * z));
}

float vectprod3f(const Vector3f& vec_a, const Vector3f& vec_b) {
    return (vec_a.X * vec_b.X)
         + (vec_a.Y * vec_b.Y)
         + (vec_a.Z * vec_b.Z);
}

float dotprod3f(float angle, const Vector3f& vecta, const Vector3f& vectb) {
	float amag, bmag;

	amag = vecta.getMagnitude();
	bmag = vectb.getMagnitude();
	bool notZero = (amag != 0.0f && bmag != 0.0f);

	if (notZero) {
		return (amag * bmag) * cosf(angle);
	} else {
		return -1.0f;	
	}
	
}

AngleType getAngleType(float angle, const Vector3f& a, const Vector3f& b) {
	
        float dotprod = dotprod3f(angle, a, b);

        if (dotprod > 0) {
		return AT_ACUTE;	
        } else if (dotprod < 0) {
		return AT_OBTUSE;
	} else {
		return AT_RIGHT;	
	}
}

float getAngle(const Vector3f& a, const Vector3f& b) {
	
	float vectprod, amag, bmag, magprod;

	amag = a.getMagnitude();
	bmag = b.getMagnitude();

	vectprod = vectprod3f(a, b);
	magprod = amag * bmag;

	if (vectprod != 0.0f && magprod != 0.0f) {
                return acosf(vectprod / magprod);
	} else {
		return -1.0f;	
	}	
	
}

/* project vector onto another vector */

float projvectf(float angle, Vector3f& v, Vector3f& n) {
	
	float nmagnitude = n.getMagnitude(), 
		  vmagnitude = v.getMagnitude(), 
                   T = NULL, II = NULL;
		 
	if (nmagnitude != 0.0f && vmagnitude != 0.0f){ 	 
		if (vmagnitude > nmagnitude) {	
			II = dotprod3f(angle, v, n) / (nmagnitude * nmagnitude);
                        n *= II;
			II = n.getMagnitude();
			T = vmagnitude - II;
		} else {
			II = dotprod3f(angle, v, n) / (vmagnitude * vmagnitude);
                        v *= II;
			II = v.getMagnitude();
			T = nmagnitude - II;
		}
	} else {
		std::cout << "Vector3f v of magnitude " << vmagnitude << " ";
		std::cout << "and Vector3f n of magnitude " << nmagnitude << " could not be projected: divide by zero" << std:: endl;

		return -1.0f;
	}

	return II + T;
}


