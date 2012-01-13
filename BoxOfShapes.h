#pragma once
#include <list>
#include <QGLWidget>
#include <GL/glext.h>
#include "SharedPtr.h"
#include "Shape.h"

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

protected:
    std::list< shared_ptr< Shape > > collide( std::list< shared_ptr< Shape > > toCollide );

    std::list< shared_ptr< Shape > > explode( std::list< shared_ptr< Shape > > toExplode );

    int heightForWidth( int w ) { return w; }

    void initializeGL( void );

    void move( std::list< shared_ptr< Shape > >& toMove );

    void paintGL( void );

    virtual void Render( void );

    void resizeGL( int width, int height );

    std::list< shared_ptr< Shape > > mShapes;

    std::list< shared_ptr< Shape > > mParticles;

    float mHeight;

    float mWidth;
};
