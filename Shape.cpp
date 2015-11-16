#include "Shape.h"

Shape::Shape( Vec2f center, float radius, Vec3f color )
    : mCenter( center ),
    mColor( color ),
    mHP( 0 ),
    mIsSolid( true ),
    mRadius( radius )
{
}

Shape::~Shape( void )
{
}

bool Shape::IsAlive( void ) const
{
    return mHP > 0;
}
