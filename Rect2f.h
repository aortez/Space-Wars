#ifndef RECT2F_H
#define RECT2F_H

#include <QGLWidget>
#include <GL/glext.h>
#include <cmath>
#include <QDebug>
#include "Shape.h"
#include "Vec3f.h"
#include "rand.h"

typedef enum {
    RC_TOPLEFT,
    RC_TOPRIGHT,
    RC_BOTTOMRIGHT,
    RC_BOTTOMLEFT
} RectangleCorner;

class Rect2f : public Shape
{
public:

    Rect2f(
        Vec2f center = Vec2f(),
        float width = 4,
        float height = 4,
        float radius = 0,
        Vec3f color = Vec3f()
    );

    ~Rect2f();

    inline const float GetWidth( void ) const {
        return mWidth;
    }

    inline const float GetHeight( void ) const {
        return mHeight;
    }

    inline const Vec2f* GetCorner( RectangleCorner rc ) const {
        switch( rc ) {
        case RC_TOPLEFT:
            return mTopLeftCrnr;
            break;

        case RC_TOPRIGHT:
            return mTopRightCrnr;
            break;

        case RC_BOTTOMLEFT:
            return mBottomLeftCrnr;
            break;

        case RC_BOTTOMRIGHT:
            return mBottomRightCrnr;
            break;
        }
    }

    void UpdateCorners();

    virtual void Collide( Shape &s );

    virtual void Collide( Rect2f &r );

    virtual void Collide ( Circle &c );

    virtual bool Intersects( const Shape& s ) const;

    virtual bool Intersects( const Rect2f& s ) const;

    virtual bool IsAlive( void ) const;

    virtual float Mass( void ) const;

protected:

   virtual void Draw( void ) const;
   float mWidth, mHeight;
   Vec3f mColor;

private:
   Vec2f* mTopLeftCrnr;
   Vec2f* mTopRightCrnr;
   Vec2f* mBottomLeftCrnr;
   Vec2f* mBottomRightCrnr;

};


#endif //RECT2F_H
