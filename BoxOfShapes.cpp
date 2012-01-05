#include <QDebug>
#include <QList>
#include <QTimer>
#include "BoxOfShapes.h"
#include "Circle.h"
#include "rand.h"
#include "Vec3f.h"
using namespace std;

const float deltaT = 1.0 / 60;

BoxOfShapes::BoxOfShapes( QWidget* parent, float width, float height ) :
    QGLWidget( parent ),
    mHeight( height ),
    mWidth( width )
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( doPhysics() ) );
    timer->start( deltaT * 1000 );
    this->setFixedWidth( mWidth );
    this->setFixedHeight( mHeight );
    this->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

BoxOfShapes::~BoxOfShapes( void )
{
}

void BoxOfShapes::AddShape( std::shared_ptr< Shape > shape )
{
    mShapes.push_back( shape );
}

list< shared_ptr< Shape > > BoxOfShapes::collide( list< shared_ptr< Shape > > toCollide )
{
    list< shared_ptr< Shape > > collided;

    while( !toCollide.empty() )
    {
        // every shape 'a' must be collided with every other shape 'b'
        shared_ptr< Shape > a = *toCollide.begin();
        for( auto i = toCollide.begin(); i != toCollide.end(); ++i )
        {
            shared_ptr< Shape > b = *i;
            if ( a.get() != b.get() && a->Intersects( *b ) )
            {
                a->Collide( *b );
                collided.push_back( a );
                collided.push_back( b );
            }
        }

        // after colliding 'a' with every other shape, take it out of our 'toCollide' list
        toCollide.pop_front();
    }

    return collided;
}

void BoxOfShapes::doPhysics( void )
{
    // collide shapes
    auto toExplode = collide( mShapes );

    // move shapes
    move( mShapes );

    // explode exploders
    auto newShapes = explode( toExplode );

    // remove exploders from world
    for( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        mShapes.remove( *i );
    }

    mShapes.splice( mShapes.end(), newShapes );

    update();
}

list< shared_ptr < Shape > > BoxOfShapes::explode( list< shared_ptr< Shape > > toExplode )
{
    list< shared_ptr< Shape > > newShapes;
    for ( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        Shape& s = **i;
        for ( int y = s.mCenter.Y - s.mRadius; y < s.mCenter.Y + s.mRadius; y++ )
        {
            for ( int x = s.mCenter.X - s.mRadius; x < s.mCenter.X + s.mRadius; x++ )
            {
                if ( rng() > 0.05 )
                {
                    Vec3f color;
                    color.rand();
                    shared_ptr< Circle > c( new Circle( Vec2f( x, y ), s.mRadius / 2, color ) );
                    newShapes.push_back( c );
                }
            }
        }
    }
    return newShapes;
}

void BoxOfShapes::initializeGL( void )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );

    glEnable( GL_BLEND );
    glEnable( GL_MULTISAMPLE );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_LINE_SMOOTH );
    glShadeModel( GL_SMOOTH );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void BoxOfShapes::move( std::list< shared_ptr< Shape > >& toMove )
{
    for( auto i = toMove.begin(); i != toMove.end(); ++i )
    {
        float& x = (*i)->mCenter.X;
        float& y = (*i)->mCenter.Y;

        float& xv = (*i)->mVelocity.X;
        float& yv = (*i)->mVelocity.Y;

        float& r = (*i)->mRadius;

        const float g = .0986;
        yv -= deltaT * g;

        x += xv;
        y += yv;

        // bounce off of walls
        const float damping = 0.8;
        if ( y + r >= 1 )
        {
            y = 1 - r;
            yv = -yv * damping;
        }
        else if ( y - r <= -1 )
        {
            y = -1 + r;
            yv = -yv * damping;
        }
        if ( x + r >= 1 )
        {
            x = 1 - r;
            xv = -xv * damping;
        }
        else if ( x - r <= -1 )
        {
            x = -1 + r;
            xv = -xv * damping;
        }
    }
}

void BoxOfShapes::paintGL( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, width(), 0, height() );
    glClear( GL_COLOR_BUFFER_BIT );

    Render();
}

void BoxOfShapes::Render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  

    for( auto i = mShapes.begin(); i != mShapes.end(); ++i )
    {
        (*i)->Draw();
    }
}

void BoxOfShapes::resizeGL( int width, int height )
{
    if ( height == 0 ) height = 1;
    if ( width == 0 ) width = 1;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 8.0f );
    glMatrixMode( GL_MODELVIEW );
}
