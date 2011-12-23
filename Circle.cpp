#include <cmath>
#include <QGLWidget>
#include "Circle.h"
#include "Point2f.h"

Circle::Circle( void )
    : Shape(),
      mColor(),
      mRadius( 0 )
{
}

Circle::Circle( const Point2f center, const float radius, const Vec3f color )
    : Shape(),
      mCenter( center ),
      mColor( color ),
      mRadius( radius )
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
