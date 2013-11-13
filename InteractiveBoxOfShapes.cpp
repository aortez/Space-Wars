#include <QDebug>
#include <QMouseEvent>
#include "Circle.h"
#include "InteractiveBoxOfShapes.h"
#include "Rectangle.h"
#include "Vec3f.h"

InteractiveBoxOfShapes::InteractiveBoxOfShapes( QWidget* parent, float width, float height )
    : BoxOfShapes( parent, width, height ),
      mIsButtonDown( false )
{
}

InteractiveBoxOfShapes::~InteractiveBoxOfShapes( void )
{
}

void InteractiveBoxOfShapes::mouseMoveEvent ( QMouseEvent* event )
{
    mButtonCurrent = event->pos();
}

void InteractiveBoxOfShapes::mousePressEvent ( QMouseEvent* event )
{   
    mButtonDown = event->pos();
    mIsButtonDown = true;
}

Vec2f InteractiveBoxOfShapes::widgetPointToVec( const QPointF& p ) const
{
    const float x = 2 * ( p.x() / static_cast<float>( width() ) - 0.5 );
    const float y = 2 * ( 0.5 - p.y() / static_cast<float>( height() ) );
    const Vec2f v( x, y );
    return v;
}

void InteractiveBoxOfShapes::mouseReleaseEvent ( QMouseEvent* event )
{
    mButtonCurrent = event->pos();
    mIsButtonDown = false;

    // map from [0,1] -> [-1,1]
    Vec2f center = widgetPointToVec( event->localPos() );

    // choose a random color
    Vec3f color;
    for ( int i = 0; i < 3; i++ )
    {
        color[ i ] = static_cast< double >( qrand() ) / RAND_MAX;
    }
    const float radius = ( static_cast< double >( qrand() ) / RAND_MAX ) / 2;

    shared_ptr< Shape > shape;
    if ( event->button() == Qt::LeftButton )
    {
        shape.reset( new Circle( center, radius, color ) );
    }
    else
    {
        shape.reset( new Rectangle( center, Vec2f( radius, radius ), color ) );
    }
    Vec2f v;
    v.X = ( ( mButtonCurrent.x() - mButtonDown.x() ) / float( width() ) );
    v.Y = -( ( mButtonCurrent.y() - mButtonDown.y() ) / float( height() ) );
    v *= 2;

    shape->mVelocity = v;

    addShape( shape );
}

void InteractiveBoxOfShapes::Render( void )
{
    BoxOfShapes::Render();
    if ( mIsButtonDown )
    {
        glBegin( GL_LINES );
        glColor3f( 1, 1, 1 );
        const Vec2f v = widgetPointToVec( mButtonDown );
        glVertex3f( v.X, v.Y, 0 );
        const Vec2f v1 = widgetPointToVec( mButtonCurrent );
        glVertex3f( v1.X, v1.Y, 0 );
        glEnd();
    }
}
