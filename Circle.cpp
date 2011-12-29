#include <cmath>
#include <QGLWidget>
#include "Circle.h"
#include "Vec2f.h"

Circle::Circle( void )
    : Shape(),
      mColor()
{
}

Circle::Circle( const Vec2f center, const float radius, const Vec3f color )
    : Shape( center, radius ),
      mColor( color )
{
}

void Circle::Draw( void ) const
{
    const double numPoints = 10;
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( mColor.X, mColor.Y, mColor.Z );
    glVertex3f( mCenter.X, mCenter.Y, 0.0f );

    for ( int i = 0; i <= numPoints; i++ )
    {
        const float x = mCenter.X + std::cos( i / numPoints * 2 * PI ) * mRadius;
        const float y = mCenter.Y + std::sin( i / numPoints * 2 * PI ) * mRadius;
        glVertex3f( x, y, 0.0f);
    }
    glEnd();
}

void Circle::Collide( Shape& s )
{
    if ( this != &s && this->Intersects( s ) )
    {
        s.Collide( *this );
    }
}

void Circle::Collide( Circle& b )
{
    Circle& a = *this;
    const float m1 = a.mRadius;
    const float m2 = b.mRadius;

    Vec2f& v1 = a.mVelocity;
    Vec2f& v2 = b.mVelocity;

    // elastic collision
    Vec2f v1prime;
    v1prime.X = ( v1.X * ( m1 - m2 ) + 2 * ( m2 * v2.X ) ) / ( m1 + m2 );
    v1prime.Y = ( v1.Y * ( m1 - m2 ) + 2 * ( m2 * v2.Y ) ) / ( m1 + m2 );

    Vec2f v2prime;
    v2prime.X = ( v2.X * ( m2 - m1 ) + 2 * ( m1 * v1.X ) ) / ( m1 + m2 );
    v2prime.Y = ( v2.Y * ( m2 - m1 ) + 2 * ( m1 * v1.Y ) ) / ( m1 + m2 );

    a.mVelocity = v1prime;
    b.mVelocity = v2prime;

    // if a.X > b.X then shift a left and b right
    // so that they no longer overlap
}

bool Circle::Intersects( const Shape& s ) const
{
    return s.Intersects( *this );
}

bool Circle::Intersects( const Circle& c ) const
{
    return mCenter.distanceTo( c.mCenter ) <= ( mRadius + c.mRadius );
}
