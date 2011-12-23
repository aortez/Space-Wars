#pragma once
#include <list>
#include <QGLWidget>
#include "SharedPtr.h"
#include "Shape.h"

class BoxOfShapes
        : public QGLWidget
{
    Q_OBJECT
public:
    explicit BoxOfShapes( QWidget* parent, float width, float height );

    virtual ~BoxOfShapes( void );

    void AddShape( std::shared_ptr< Shape > shape );

protected:
    int heightForWidth( int w ) { return w; }

    void initializeGL( void );

    void paintGL( void );

    void Render( void );

    void resizeGL( int width, int height );

    std::list< shared_ptr< Shape > > mShapes;

    float mHeight;

    float mWidth;
};
