#include <cmath>
#include "Vec2f.h"

Vec2f::Vec2f( const float x, const float y )
    : X( x ),
    Y( y ),
    mData( &X )
{
}

float Vec2f::distanceTo( const Vec2f& v ) const
{
    return std::sqrt( ( v.X - X ) * ( v.X - X ) + ( v.Y - Y ) * (v.Y - Y ) );
}

float& Vec2f::operator[]( int i )
{
    return mData[ i ];
}
