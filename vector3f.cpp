#include "vector3f.h"

Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::~Vector3f() {
	
	
}

float Vector3f::getMagnitude() const{
	return sqrt(
		(this->x * this->x)
	+	(this->y * this->y)
	+ 	(this->z * this->z)
	);
		
}

void Vector3f::multiplyByScalar(float scalar) {
	if (scalar != 0.0f) {
		this->x = x * scalar;
		this->y = y * scalar;
		this->z = z * scalar;
	}
}

void Vector3f::divideByScalar(float scalar) {
	if (scalar != 0.0f && (this->x != 0.0f && this->y != 0.0f && this->z != 0.0f)) 
	{	this->x = x / scalar;
		this->y = y / scalar;
		this->z = z / scalar;
	}	
}

void Vector3f::normalize() {
	float magnitude = getMagnitude();
	
	bool noZero =
	(magnitude != 0.0f && (this->x != 0.0f && this->y != 0.0f && this->z != 0.0f));

	if (noZero) {
		this->x = x / getMagnitude();
		this->y = y / getMagnitude();
		this->z = z / getMagnitude();
	} else {
		std::cout << "Cannot normalize Vector3f: the x, y, or z coordinate or the magnitude has resulted in zeor." << std::endl;
	}
	
}

Vector3f Vector3f::operator/(const Vector3f& vec) {

	bool vecNoZero = (vec.x != 0.0f && vec.y != 0.0f && vec.z != 0.0f);
	bool thisNoZero = (this->x != 0.0f && this->y != 0.0f && this->z != 0.0f);

	if (vecNoZero && thisNoZero) {
		this->x = x / vec.x;
		this->y = y / vec.y;
		this->z = z / vec.z;
	}

	return *this;
}

Vector3f Vector3f::operator/=(const Vector3f& vec) {
	
	*this = *this / vec;

	return *this;
}

Vector3f Vector3f::operator*(const Vector3f& vec) {
	this->x = x * vec.x;
	this->y = y * vec.y;
	this->z = z * vec.z;

	return *this;
}

Vector3f Vector3f::operator*=(const Vector3f& vec) {
	*this = *this * vec;

	return *this;
}

Vector3f Vector3f::operator+ (const Vector3f& vec) {
	this->x = x + vec.x;
	this->y = y + vec.y;
	this->z = z + vec.z;

	return *this; 
}

Vector3f Vector3f::operator+=(const Vector3f& vec) {
	*this = *this + vec;

	return *this;
}

Vector3f Vector3f::operator-(const Vector3f& vec) {
	this->x = x - vec.x;
	this->y = y - vec.y;
	this->z = z - vec.z;

	return *this;
}

Vector3f Vector3f::operator-=(const Vector3f& vec) {
	*this = *this - vec;

	return *this;
}



float compdist3f(const Vector3f& vec_a,const Vector3f& vec_b) {
	float x = vec_a.x - vec_b.x;
	float y = vec_a.y - vec_b.y;
	float z = vec_a.z - vec_b.z;

	return sqrt((x * x) + (y * y) + (z * z));
}

float vectprod3f(const Vector3f& vec_a, const Vector3f& vec_b) {
	return (vec_a.x * vec_b.x) 
		 + (vec_a.y * vec_b.y) 
		 + (vec_a.z * vec_b.z);
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
	
	float vectprod = dotprod3f(angle, a, b);

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
		return acosf(dotprod / magprod);	
	} else {
		return -1.0f;	
	}	
	
}

float projvectf(float angle, const Vector3f& v, const Vector3f& n) {
	
	float nmagnitude = n.getMagnitude(), 
		  vmagnitude = v.getMagnitude(), 
		  IImag, T, II;
		 
	if (nmagnitude != 0.0f && vmagnitude != 0.0f){ 	 
		if (vmagnitude > nmagnitude) {	
			II = dotprod3f(angle, v, n) / (nmagnitude * nmagnitude);
			n.multiplyByScalar(II);
			II = n.getMagnitude();
			T = vmagnitude - II;
		} else {
			II = dotprod3f(angle, v, n) / (vmagnitude * vmagnitude);
			v.multiplyByScalar(II);
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


