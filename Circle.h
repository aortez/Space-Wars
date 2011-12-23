#pragma once
#include "Point2f.h"
#include "Shape.h"
#include "Vec3f.h"

class Circle
        : public Shape
{
public:
    Circle( void );

    Circle( Point2f center, float radius, const Vec3f color );

protected:
    virtual void Draw( void ) const;

private:
    Point2f mCenter;
    Vec3f mColor;
    float mRadius;
};
