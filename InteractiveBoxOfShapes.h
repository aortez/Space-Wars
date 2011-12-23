#pragma once
#include "BoxOfShapes.h"

class InteractiveBoxOfShapes
        : public BoxOfShapes
{
public:
    InteractiveBoxOfShapes( QWidget* parent, float width, float height );

    virtual ~InteractiveBoxOfShapes( void );

protected:
    void mousePressEvent ( QMouseEvent* event );

    //void QWidget::mouseReleaseEvent ( QMouseEvent * event );

//    void QWidget::moveEvent ( QMoveEvent * event );
};

