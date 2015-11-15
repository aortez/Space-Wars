#include <QDebug>
#include <QList>
#include <QTime>
#include <QTimer>
#include <cassert>
#include "BoxOfShapes.h"
#include "Circle.h"
#include "rand.h"
#include "Vec3f.h"
using namespace std;

const float FPS = 60;

const float TIME_SCALE = 0.05;

BoxOfShapes::BoxOfShapes( QWidget* parent, float width, float height ) :
    QGLWidget( parent ),
    mDims( height, width ),
    mFpsTimer( new QTime )
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( doPhysics() ) );
    timer->start( 1.0 / FPS * 1000 );
    this->setFixedWidth( mDims.X );
    this->setFixedHeight( mDims.Y );
    this->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    mFpsTimer->start();
}

BoxOfShapes::~BoxOfShapes( void )
{
}

void BoxOfShapes::addShape( std::shared_ptr< Shape > shape )
{
    mShapes.push_back( shape );
}

list< shared_ptr< Shape > > BoxOfShapes::collide( list< shared_ptr< Shape > > toCollide )
{
    list< shared_ptr< Shape > > deadShapes;

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
                if ( !a->IsAlive() )
                {
                    deadShapes.push_back( a );
                }
                if ( !b->IsAlive() )
                {
                    deadShapes.push_back( b );
                }
            }
        }

        // after colliding 'a' with every other shape, take it out of our 'toCollide' list
        toCollide.pop_front();
    }

    return deadShapes;
}

void BoxOfShapes::doPhysics( void )
{
    static QTime timer;
    const float deltaT = 0.001 * timer.elapsed() * TIME_SCALE;
    timer.start();

    {
        const int msElapsed = mFpsTimer->restart();
        const int fps = 1000 / msElapsed;
        emit fpsChanged( fps );
    }

    // collide shapes
    auto toExplode = collide( mShapes );

    // move shapes
    move( mShapes, deltaT );
    move( mParticles, deltaT );

    // reduce health of very weak shapes
    for( auto i = mShapes.begin(); i != mShapes.end(); ++i )
    {
        float& hp = (*i)->mHP;
        if ( hp < 0.05 )
            hp -= 0.000001;

        if ( hp <= 0 )
        {
            toExplode.push_back( *i );
        }
    }

    // remove old particles
    list< shared_ptr< Shape > > toRemove;
    for( auto i = mParticles.begin(); i != mParticles.end(); ++i )
    {
        float& hp = (*i)->mHP;
        hp -= 0.000001;

        if ( hp <= 0 )
        {
            toRemove.push_back( *i );
        }
    }

    // explode exploders
    auto newShapes = explode( toExplode );

    // remove exploders from world
    for( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        mShapes.remove( *i );
    }

    // add shapes
    for ( auto shape = newShapes.begin(); shape != newShapes.end(); ++shape )
    {
        if ( mShapes.size() < 600 )
        {
            mShapes.push_back( *shape );
        }
    }
    update();
    emit( numShapesChanged( mShapes.size() ) );
}

list< shared_ptr < Shape > > BoxOfShapes::explode( list< shared_ptr< Shape > > toExplode )
{
    list< shared_ptr< Shape > > newShapes;
    list< shared_ptr< Shape > > newParticles;
    for ( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        Shape& s = **i;
        const float step = s.mBoundsRadius * 0.5;
        for ( float y = s.mCenter.Y - s.mBoundsRadius; y < s.mCenter.Y + s.mBoundsRadius; y += step )
        {
            for ( float x = s.mCenter.X - s.mBoundsRadius; x < s.mCenter.X + s.mBoundsRadius; x += step )
            {
                const Vec2f newCenter( x, y );
                if ( newCenter.distanceTo(s.mCenter) > s.mBoundsRadius ) continue;

                Vec3f color;
                color.rand();
                shared_ptr< Circle > c( new Circle( newCenter, step * 0.20, color ) );

                Vec2f d = c->mCenter - s.mCenter;
                d *= 10;
                c->mVelocity = d + s.mVelocity * 0.1;
                if ( c->mBoundsRadius > 0.001 )
                {
                    newShapes.push_back( c );
                }
                else
                {
                    newParticles.push_back( c );
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

void BoxOfShapes::move( std::list< shared_ptr< Shape > >& toMove, const float deltaT )
{
    for( auto i = toMove.begin(); i != toMove.end(); ++i )
    {
        Shape& s = **i;
        float& x = s.mCenter.X;
        float& y = s.mCenter.Y;

        float& xv = s.mVelocity.X;
        float& yv = s.mVelocity.Y;
        assert( !isinf(xv) );
        assert( !isinf(yv) );

        float& r = s.mBoundsRadius;

        const float g = 0.986;
        yv -= deltaT * g;

        x += xv * deltaT;
        y += yv * deltaT;

        // bounce off of walls
        const float damping = 0.8;
        if ( y + r > 1 )
        {
            y = 1 - r;
            yv *= -1 * damping;
        }
        else if ( y - r < -1 )
        {
            y = -1 + r;
            yv *= -1 * damping;
        }
        if ( x + r > 1 )
        {
            x = 1 - r;
            xv *= -1 * damping;
        }
        else if ( x - r < -1 )
        {
            x = -1 + r;
            xv *= -1 * damping;
        }
    }
}

void BoxOfShapes::paintGL( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
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

void BoxOfShapes::resetWorld( void )
{
    mParticles.clear();
    mShapes.clear();
}

void BoxOfShapes::resizeGL( int width, int height )
{
    if ( height == 0 ) height = 1;
    if ( width == 0 ) width = 1;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glMatrixMode( GL_MODELVIEW );
}
