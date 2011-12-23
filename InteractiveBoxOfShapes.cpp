#include <QMouseEvent>
#include "Circle.h"
#include "InteractiveBoxOfShapes.h"
#include "Vec3f.h"

InteractiveBoxOfShapes::InteractiveBoxOfShapes( QWidget* parent, float width, float height )
    : BoxOfShapes( parent, width, height )
{
    printf( "box o shapes!\n" );
}

InteractiveBoxOfShapes::~InteractiveBoxOfShapes( void )
{
}

void InteractiveBoxOfShapes::mousePressEvent ( QMouseEvent* event )
{
    // map from [0,1] -> [-1,1]
    const float x = 2 * ( event->pos().x() / static_cast<float>( width() ) - 0.5 );
    const float y = 2 * ( 0.5 - event->pos().y() / static_cast<float>( height() ) );
    Point2f center( x, y );

    // choose a random color
    Vec3f color;
    for ( int i = 0; i < 3; i++ )
    {
        color[ i ] = static_cast< double >( qrand() ) / RAND_MAX;
    }
    const float radius = 0.1;

    shared_ptr< Shape > shape(
                new Circle(
                    center,
                    radius,
                    color ) );

    AddShape( shape );
}
