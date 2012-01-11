#include <cmath>
#include "rand.h"
#include "Vec3f.h"

Vec3f::Vec3f( float x, float y, float z )
    : X( x ),
      Y( y ),
      Z( z ),
      mData( &X )
{
}

float Vec3f::distanceTo( const Vec3f& v ) const
{
    return std::sqrt( ( v.X - X ) * ( v.X - X ) + ( v.Y - Y ) * (v.Y - Y ) + (v.Z - Z ) * (v.Z - Z ) );
}

float& Vec3f::operator[]( int i )
{
    return mData[ i ];
}

void Vec3f::rand( void )
{
    X = rng();
    Y = rng();
    Z = rng();
}
