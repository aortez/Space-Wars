#pragma once
#include "BoxOfShapes.h"

class InteractiveBoxOfShapes
        : public BoxOfShapes
{
public:
    InteractiveBoxOfShapes( QWidget* parent, float width, float height );

    virtual ~InteractiveBoxOfShapes( void );

protected:
    void mousePressEvent( QMouseEvent* event );

    void mouseReleaseEvent( QMouseEvent* event );

    void mouseMoveEvent( QMouseEvent* event );

    Vec2f widgetPointToVec( const QPointF& p ) const;

    virtual void Render( void );

    QPoint mButtonCurrent;

    QPoint mButtonDown;

    bool mIsButtonDown;
};

