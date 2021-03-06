#include <cassert>
#include <cmath>
#include <QDebug>
#include <QGLWidget>
#include <QString>
#include "Circle.h"
#include "rand.h"
#include "Vec2f.h"

Circle::Circle(
        const Vec2f center,
        const float radius,
        const Vec3f color )
    : Shape( center, radius, color )
{
    mHP = Mass() * 200;
}

void Circle::Draw( void ) const
{
    const int numPoints = mRadius * 1000;
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( mColor.X, mColor.Y, mColor.Z );

    for ( double i = 0; i <= numPoints; i++ )
    {
        const float x = mCenter.X + std::cos( i / numPoints * 2 * PI ) * mRadius;
        const float y = mCenter.Y + std::sin( i / numPoints * 2 * PI ) * mRadius;
        glVertex3f( x, y, 0.0f );
    }
    glEnd();

    if ( mRadius < 0.005 ) return;

    glBegin( GL_LINE_STRIP );
    glColor3f( 0, 0, 0 );

    for ( double i = 0; i <= numPoints; i++ )
    {
        const float x = mCenter.X + std::cos( i / numPoints * 2 * PI ) * mRadius;
        const float y = mCenter.Y + std::sin( i / numPoints * 2 * PI ) * mRadius;
        glVertex3f( x, y, 0.0f );
    }
    glEnd();

}

void Circle::Collide( Circle& b )
{
    // compute distance between centers
    Vec2f Dn = mCenter - b.mCenter;

    float delta = Dn.magnitude();
    while ( delta == 0 ) // if circles are on top of each other, jitter em around
    {
        b.mCenter.X += rngb() * 0.01;
        b.mCenter.Y += rngb() * 0.01;
        Dn = mCenter - b.mCenter;
        delta = Dn.magnitude();
    }

    // normalize vector between centers
    Dn.normalize();

    // minimum translation distance to separate circles
    const Vec2f mT = Dn * ( ( mRadius + b.mRadius - delta ) );

    //the masses of the two balls
    const float m1 = Mass();
    const float m2 = b.Mass();
    const float M = m1 + m2;

    // push the circles apart proportional to their mass
    mCenter += mT * ( m2 / M );
    b.mCenter -= mT * ( m1 / M  );

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

    // calculate new velocity vectors of the balls, the tangential component stays the same, the normal component changes
    mVelocity = v1t + Dn * ( ( m1 - m2 ) / (M * v1n.magnitude() ) + 2 * m2 / M * v2n.magnitude() );
    b.mVelocity = v2t - Dn * ( (m2 - m1) / ( M * v2n.magnitude() ) + 2 * m1 / M * v1n.magnitude() );
    mVelocity.clamp();
    b.mVelocity.clamp();

    // damage the circles based upon their change in direction X mass
    const float p1Damage = m1 * v1.distanceTo(mVelocity);
    const float p2Damage = m2 * v2.distanceTo(b.mVelocity);
    mHP -= p1Damage;
    b.mHP -= p2Damage;
}

void Circle::Collide( Shape& s )
{
    s.Collide( *this );
}

bool Circle::Intersects( const Circle& c ) const
{
    return mCenter.distanceTo( c.mCenter ) < ( mRadius + c.mRadius );
}

bool Circle::Intersects( const Shape& s ) const
{
    return s.Intersects( *this );
}

float Circle::Mass( void ) const
{
    const float mass = pow( mRadius * 1000, 2 );
    return mass;
}
