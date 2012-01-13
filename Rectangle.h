#pragma once
#include "Shape.h"
#include "Vec2f.h"
#include "Vec3f.h"

class Rectangle
        : public Shape
{
public:
    Rectangle( void );

    Rectangle( Vec2f center, Vec2f dims, Vec3f color );

    virtual void Collide( Shape& s );

    virtual void Collide( Circle& c );

    virtual void Collide( Rectangle& c );

    virtual bool Intersects( const Shape& s ) const;

    virtual bool Intersects( const Circle& c ) const;

    virtual bool Intersects( const Rectangle& c ) const;

    virtual float Mass( void ) const;

protected:
    Vec2f BottomLeft( void ) const;

    Vec2f BottomRight( void ) const;

    virtual void Draw( void ) const;

    Vec2f TopLeft( void ) const;

    Vec2f TopRight( void ) const;

private:
    Vec3f mColor;
    Vec2f mRadius;
};
