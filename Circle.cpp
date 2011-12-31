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
    const int numPoints = mRadius * 1000;
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( mColor.X, mColor.Y, mColor.Z );
    glVertex3f( mCenter.X, mCenter.Y, 0.0f );

    for ( double i = 0; i <= numPoints; i++ )
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
    // compute distance between centers
    Vec2f Dn;
    float delta = 0;
    while ( delta == 0 )
    {
        b.mCenter.X += static_cast< double >( qrand() ) / RAND_MAX * 0.01;
        b.mCenter.Y += static_cast< double >( qrand() ) / RAND_MAX * 0.01;
        Dn = mCenter - b.mCenter;
        delta = Dn.magnitude();
    }

    // normalize vector between centers
    Dn.normalize();

    // minimum translation distance to separate circles
    const Vec2f mT = Dn * ( ( mRadius + b.mRadius - delta ) );

    //the masses of the two balls
    const float m1 = mRadius / 10;
    const float m2 = b.mRadius / 10;
    const float M = m1 + m2;

    // push the circles apart proportional to their mass
    mCenter += ( mT * m2 / M );
    b.mCenter -= ( mT * m1 / M  );

    // the velocity vectors of the balls before the collision
    const Vec2f v1 = mVelocity;
    const Vec2f v2 = b.mVelocity;

    // The tangential vector of the collision plane
    const Vec2f Dt( Dn.Y, -Dn.X );

    // split the velocity vector of the first ball into a normal and a tangential component in respect of the collision plane
    const Vec2f v1n = Dn * dot( v1, Dn );
    const Vec2f v1t = Dt * dot( v1, Dt );

    // split the velocity vector of the second ball into a normal and a tangential component in respect of the collision plane
    const Vec2f v2n = Dn * dot( v2, Dn );
    const Vec2f v2t = Dt * dot( v2, Dt );

    // calculate new velocity vectors of the balls, the tangential component stays the same, the normal component changes analog to the 1-Dimensional case
    mVelocity = v1t + Dn * ( ( m1 - m2 ) / M * v1n.magnitude() + 2 * m2 / M * v2n.magnitude() );
    b.mVelocity = v2t - Dn * ( (m2 - m1) / M * v2n.magnitude() + 2 * m1 / M * v1n.magnitude() );
}

bool Circle::Intersects( const Shape& s ) const
{
    return s.Intersects( *this );
}

bool Circle::Intersects( const Circle& c ) const
{
    return mCenter.distanceTo( c.mCenter ) <= ( mRadius + c.mRadius );
}
