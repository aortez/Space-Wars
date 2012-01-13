#include <cmath>
#include "Vec2f.h"

Vec2f::Vec2f( const float x, const float y )
    : X( x ),
    Y( y ),
    mData( &X )
{
}

Vec2f::Vec2f( const Vec2f& v )
    : X( v.X ),
      Y( v.Y ),
      mData( &X )
{
}

float Vec2f::distanceTo( const Vec2f& v ) const
{
    return std::sqrt( ( v.X - X ) * ( v.X - X ) + ( v.Y - Y ) * (v.Y - Y ) );
}

float Vec2f::magnitude( void ) const
{
    return std::sqrt( X * X + Y * Y );
}

void Vec2f::normalize( void )
{
    *this /= magnitude();
}

float& Vec2f::operator[]( int i )
{
    return mData[ i ];
}

Vec2f& Vec2f::operator+=( const Vec2f& v )
{
    X += v.X;
    Y += v.Y;
    return *this;
}

Vec2f& Vec2f::operator+=( const float s )
{
    X += s;
    Y += s;
    return *this;
}

Vec2f& Vec2f::operator-=( const Vec2f& v )
{
    X -= v.X;
    Y -= v.Y;
    return *this;
}

Vec2f& Vec2f::operator-=( const float s )
{
    X -= s;
    Y -= s;
    return *this;
}

Vec2f& Vec2f::operator*=( const Vec2f& v )
{
    X *= v.X;
    Y *= v.Y;
    return *this;
}

Vec2f& Vec2f::operator*=( const float s )
{
    X *= s;
    Y *= s;
    return *this;
}

Vec2f& Vec2f::operator/=( const Vec2f& v )
{
    X /= v.X;
    Y /= v.Y;
    return *this;
}

Vec2f& Vec2f::operator/=( const float s )
{
    X /= s;
    Y /= s;
    return *this;
}

float dot( const Vec2f& a, const Vec2f& b )
{
    const float scalarProduct = a.X * b.X + a.Y * b.Y;
    return scalarProduct;
}

Vec2f operator+( Vec2f a, const Vec2f& b )
{
    a += b;
    return a;
}

Vec2f operator+( Vec2f a, float s )
{
    a += s;
    return a;
}


Vec2f operator-( Vec2f a, const Vec2f& b )
{
    a -= b;
    return a;
}

Vec2f operator-( Vec2f a, float s )
{
    a -= s;
    return a;
}

Vec2f operator-( Vec2f a )
{
    a = 0 - a;
    return a;
}

Vec2f operator*( Vec2f a, const Vec2f& b )
{
    a *= b;
    return a;
}

Vec2f operator*( Vec2f a, float s )
{
    a *= s;
    return a;
}

Vec2f operator/( Vec2f a, const Vec2f& b )
{
    a /= b;
    return a;
}

Vec2f operator/( Vec2f a, float s )
{
    a /= s;
    return a;
}
