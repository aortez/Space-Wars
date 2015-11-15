#pragma once
#include <list>
#include <QGLWidget>
#include <GL/glext.h>
#include "SharedPtr.h"
#include "Shape.h"
#include "Vec2f.h"
class QTime;

class BoxOfShapes
        : public QGLWidget
{
    Q_OBJECT
public:
    explicit BoxOfShapes( QWidget* parent, float width, float height );

    virtual ~BoxOfShapes( void );

    void addShape( std::shared_ptr< Shape > shape );

public slots:
    void doPhysics( void );

    void resetWorld( void );

signals:
    void numShapesChanged( int numShapes );

    void fpsChanged( int fps );

protected:
    std::list< shared_ptr< Shape > > collide( std::list< shared_ptr< Shape > > toCollide );

    std::list< shared_ptr< Shape > > explode( std::list< shared_ptr< Shape > > toExplode );

    int heightForWidth( int w ) { return w; }

    void initializeGL( void );

    void move( std::list< shared_ptr< Shape > >& toMove, float deltaT );

    void paintGL( void );

    virtual void Render( void );

    void resizeGL( int width, int height );

    Vec2f mDims;

    shared_ptr< QTime > mFpsTimer;

    std::list< shared_ptr< Shape > > mShapes;

    std::list< shared_ptr< Shape > > mParticles;
};
