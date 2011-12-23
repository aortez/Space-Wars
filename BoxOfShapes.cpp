#include <QList>
#include <QTimer>
#include "BoxOfShapes.h"

BoxOfShapes::BoxOfShapes( QWidget* parent, float width, float height ) :
    QGLWidget( parent ),
    mHeight( height ),
    mWidth( width )
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( update() ) );
    timer->start( 20 );
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
    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, width(), 0, height());
    glClear( GL_COLOR_BUFFER_BIT );
    //    glScalef( mWidth / mHeight, 1, 1 );
    //    glLoadIdentity();
    //    glRotatef( -90, 0, 0, 1 );
    //    glTranslatef( 0, 0, -1 );
    Render();
}

void BoxOfShapes::Render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //    glTranslatef(0,0,-3);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, -1, 0);
    glEnd();

    for( auto i = mShapes.begin(); i != mShapes.end(); ++i )
    {
        (*i)->Draw();
    }

    //     glBegin(GL_TRIANGLES);
    //       glVertex3f( 0.0f, 1.0f, 0.0f);
    //       glVertex3f(-1.0f,-1.0f, 0.0f);
    //       glVertex3f( 1.0f,-1.0f, 0.0f);
    //     glEnd();

    //     glTranslatef(3.0f,0.0f,0.0f);
}

void BoxOfShapes::resizeGL( int width, int height )
{
    if ( height == 0 ) height = 1;
    if ( width == 0 ) width = 1;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 8.0f );
    glMatrixMode( GL_MODELVIEW );
}
