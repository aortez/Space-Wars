#pragma once
#include "Vec2f.h"

const float PI = 3.14159265358979323846;

class Circle;
class Rectangle;

class Shape
{
public:

    Shape( Vec2f center = Vec2f(), float boundsRadius = 0 );

    virtual ~Shape( void );

    virtual void Collide( Shape& s ) = 0;

    virtual void Collide( Circle& c ) = 0;

    virtual void Collide( Rectangle& s ) = 0;

    virtual void Draw( void ) const = 0;

    virtual bool Intersects( const Circle& c ) const = 0;

    virtual bool Intersects( const Rectangle& r ) const = 0;

    virtual bool Intersects( const Shape& s ) const = 0;

    virtual bool IsAlive( void ) const;

    virtual float Mass( void ) const = 0;

    Vec2f mCenter;

    float mHP;

    bool mIsSolid;

    float mBoundsRadius;

    Vec2f mVelocity;
};
