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

    virtual bool Intersects( const Shape& s ) const;

    virtual bool Intersects( const Circle& c ) const;

protected:
    virtual void Draw( void ) const;

private:
    Vec3f mColor;
};
