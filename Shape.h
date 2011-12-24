#pragma once
#include "Vec2f.h"
const float PI = 3.14159265358979323846;
class Circle;

class Shape
{
public:
    Shape( Vec2f center = Vec2f(), float mRadius = 0 );

    virtual ~Shape( void );

    virtual bool Intersects( const Shape& s ) const = 0;

    virtual bool Intersects( const Circle& c ) const = 0;

    virtual void Draw( void ) const = 0;

    Vec2f mCenter;

    float mRadius;

    Vec2f mVelocity;
};