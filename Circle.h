#pragma once
#include "Shape.h"
#include "Vec2f.h"
#include "Vec3f.h"

class Circle
        : public Shape
{
public:
    Circle( Vec2f center = Vec2f(),
            float radius = 0,
            Vec3f color = Vec3f() );

    virtual void Collide( Circle& c );

    virtual void Collide( Shape& s );    

    virtual bool Intersects( const Circle& c ) const;

    virtual bool Intersects( const Shape& s ) const;

    virtual float Mass( void ) const;

protected:
    virtual void Draw( void ) const;

private:
    Vec3f mColor;
    float mRadius;
};
