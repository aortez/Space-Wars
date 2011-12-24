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


bool Circle::Intersects( const Shape& s ) const
{
    return s.Intersects( *this );
}

bool Circle::Intersects( const Circle& c ) const
{
    return mCenter.distanceTo( c.mCenter ) <= ( mRadius + c.mRadius );
}
