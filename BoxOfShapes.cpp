#include <QDebug>
#include <QList>
#include <QTimer>
#include "BoxOfShapes.h"

BoxOfShapes::BoxOfShapes( QWidget* parent, float width, float height ) :
    QGLWidget( parent ),
    mHeight( height ),
    mWidth( width )
{
    const float deltaT = 0.020;
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

void BoxOfShapes::doPhysics( void )
{
    const float deltaT = 0.020;
    const float g = .0986;

    // move shapes
    for( auto i = mShapes.begin(); i != mShapes.end(); ++i )
    {
        float& x = (*i)->mCenter.X;
        float& y = (*i)->mCenter.Y;

        float& xv = (*i)->mVelocity.X;
        float& yv = (*i)->mVelocity.Y;

        float& r = (*i)->mRadius;

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

    // collide shapes
    auto toCollide = mShapes;
    while( !toCollide.empty() )
    {
        // every shape 'a' must be collided with every other shape 'b'
        Shape& a = **toCollide.begin();
        for( auto i = toCollide.begin(); i != toCollide.end(); ++i )
        {
            Shape& b = *(*i);
            a.Collide( b );
        }

        // after colliding 'a' with every other shape, take it out of our 'toCollide' list
        toCollide.pop_front();
    }
    update();
}

void BoxOfShapes::initializeGL( void )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );

    glEnable( GL_BLEND );
    glEnable( GL_MULTISAMPLE );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glShadeModel( GL_SMOOTH );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
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
