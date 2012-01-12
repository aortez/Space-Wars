#pragma once
#include "Shape.h"
#include "Vec2f.h"
#include "Vec3f.h"

class Circle
        : public Shape
{
public:
    Circle( void );

    Circle( Vec2f center, float radius, const Vec3f color );

    virtual void Collide( Shape& s );

    virtual void Collide( Circle& c );

    virtual bool Intersects( const Shape& s ) const;

    virtual bool Intersects( const Circle& c ) const;

    virtual float Mass( void ) const;

protected:
    virtual void Draw( void ) const;

private:
    Vec3f mColor;
};
