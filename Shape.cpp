#include "Shape.h"

Shape::Shape( Vec2f center, float radius )
    : mCenter( center ),
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
