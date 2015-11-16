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

 // scalar for velocity of new particles based on distance from center
const float EXPLODE_V_FACTOR = 10;

const float FPS = 60;

const int MAX_SHAPES = 800;

const float TIME_SCALE = 0.1;

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

void BoxOfShapes::scenario0( void )
{
    shared_ptr< Shape > circle( new Circle( Vec2f(), 0.1, Vec3f( 1, 0, 0 ) ) );
    addShape( circle );
}

void BoxOfShapes::scenario1( void )
{
    shared_ptr< Shape > a( new Circle( Vec2f( -0.1, 0 ), 0.1, Vec3f( 0, 1, 0 ) ) );
    a->mVelocity.X = 2;

    shared_ptr< Shape > b( new Circle( Vec2f( 0.5, 0 ), 0.1, Vec3f( 1, 0, 0 ) ) );
    addShape( a );
    addShape( b );
}

list< shared_ptr< Shape > > BoxOfShapes::collide( list< shared_ptr< Shape > > toCollide )
{
    list< shared_ptr< Shape > > deadShapes;

    while( !toCollide.empty() )
    {
        // every shape 'a' must be collided with every other shape 'b'
        shared_ptr< Shape > a = *toCollide.begin();

        // after colliding 'a' with every other shape, take it out of our 'toCollide' list
        toCollide.pop_front();

        // if shape is already dead then don't collide it
        if ( !a->IsAlive() ) continue;

        for( auto i = toCollide.begin(); i != toCollide.end(); ++i )
        {
            shared_ptr< Shape > b = *i;
            if ( !b->IsAlive() ) continue;
            if ( a.get() != b.get() && a->Intersects( *b ) )
            {
                a->Collide( *b );
                if ( !b->IsAlive() )
                {
                    deadShapes.push_back( b );
                }
                if ( !a->IsAlive() )
                {
                    deadShapes.push_back( a );
                    continue;
                }
            }
        }
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

    // move shapes
    move( mShapes, deltaT );
    move( mParticles, deltaT );

    // collide shapes
    auto toExplode = collide( mShapes );

    // explode exploders
    list< shared_ptr< Shape > > newShapes;
    list< shared_ptr< Shape > > newParticles;
    explode( toExplode, newShapes, newParticles );

    // remove exploders from world
    for( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        mShapes.remove( *i );
    }

    // remove old particles
    for ( auto i = mParticles.begin(); i != mParticles.end();)
    {
        Shape& p = (**i);
        p.mHP -= 15;
        if ( p.mHP <= 0 )
        {
            i = mParticles.erase(i);
            qDebug() << "**********  removed a particle *************" << endl;
        }
        else
        {
            ++i;
        }
    }

    // add new particles
    mParticles.insert( mParticles.end(), newParticles.begin(), newParticles.end() );

    // add shapes
    for ( auto shape = newShapes.begin(); shape != newShapes.end(); ++shape )
    {
        if ( mShapes.size() < MAX_SHAPES )
        {
            mShapes.push_back( *shape );
        }
    }
    update();
    emit( numShapesChanged( mShapes.size() ) );
}

float ctc(float value) {
    const float a = 0.1f;
    value *= rngrange(1 - a, 1 + a);
    value = min(value, 1.0f);
    value = max(value, 0.0f);
    return value;
}

void BoxOfShapes::explode(
        list< shared_ptr< Shape > >& toExplode,
        list< shared_ptr< Shape > >& newShapes,
        list< shared_ptr< Shape > >& newParticles )
{
    for ( auto i = toExplode.begin(); i != toExplode.end(); ++i )
    {
        Shape& parent = **i;
        const float n = 5;
        for (float dy = parent.mCenter.Y - parent.mRadius; dy < parent.mCenter.Y + parent.mRadius; dy += parent.mRadius / n)
        {
            for (float dx = parent.mCenter.X - parent.mRadius; dx < parent.mCenter.X + parent.mRadius; dx += parent.mRadius / n)
            {
                const Vec2f newCenter( dx, dy );
                if ( newCenter.distanceTo(parent.mCenter) > parent.mRadius ) continue;

                // determine particle color
                Vec3f color;
                color.rand();
                color.X = ctc(parent.mColor.X);
                color.Y = ctc(parent.mColor.Y);
                color.Z = ctc(parent.mColor.Z);

                // radius
                const float r = rngrange(0, parent.mRadius / n * 0.5f);

                // create particle
                shared_ptr< Circle > c( new Circle( newCenter, r, color ) );

                // modify velocity...
                // scale based upon distance from center
                Vec2f d = c->mCenter - parent.mCenter;
                d *= EXPLODE_V_FACTOR;

                // base upon parent's velocity
                c->mVelocity = d + parent.mVelocity * 0.2;

                // add jitter
                const float a = 0.2;
                c->mVelocity.X *= rngrange( -a, a);
                c->mVelocity.Y *= rngrange( -a, a);

                // create as either a new shape or a particle
                if ( c->mRadius > 0.005 )
                {
                    newShapes.push_back( c );
                }
                else if ( c->mRadius > 0.001 )
                {
                    newParticles.push_back( c );
                }
            }
        }
    }
}

void BoxOfShapes::initializeGL( void )
{
    glClearColor( 0.01f, 0.01f, 0.3f, 0.0f );
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

        float& r = s.mRadius;

        const float g = 9.86;
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

    for( auto i = mParticles.begin(); i != mParticles.end(); ++i )
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
