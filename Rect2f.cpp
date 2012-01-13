#include "Rect2f.h"

/**********/
/* PUBLIC */
/**********/

Rect2f::Rect2f( Vec2f center, float width, float height, float radius, Vec3f color)
    : Shape( center, radius ),
      mColor( color ),
      mWidth( width ),
      mHeight( height )
{
    //mTopRightCrnr = new Vec2f( mCenter.X - width * 0.5f, mCenter.Y - height * 0.5f );
   // mTopLeftCrnr = new Vec2f( mCenter.X + width * 0.5f, mCenter.Y + height * 0.5f );
   // mBottomLeftCrnr = new Vec2f( mCenter.X - width * 0.5f, mCenter.Y + height * 0.5f );
    //mBottomRightCrnr = new Vec2f( mCenter.X + width * 0.5f, mCenter.Y - height * 0.5f );
}

Rect2f::~Rect2f() {
    delete mTopRightCrnr;
    delete mTopLeftCrnr;
    delete mBottomLeftCrnr;
    delete mBottomRightCrnr;
}

void Rect2f::Collide( Shape &s ) {
    s.Collide( *this );
}

void Rect2f::UpdateCorners() {

}

void Rect2f::Collide( Rect2f &r ) {

    Vec2f Dn;

    float delta = 0;

    bool collides = false;

    while ( delta == 0 ) {

        r.mCenter.X += randcollider();
        r.mCenter.Y += randcollider();

        r.UpdateCorners();

        Dn = mCenter - r.mCenter;

        delta = Dn.magnitude();
    }


}

void Rect2f::Collide( Circle& c ) {

}

bool Rect2f::Intersects( const Shape &s ) const {
    return false;
}

bool Rect2f::Intersects( const Rect2f &s ) const {
    return false;
}

bool Rect2f::IsAlive( void ) const {
    return false;
}

float Rect2f::Mass( void ) const {
    return -1.0f; //const float x = ( mWidthHeight->X *  )
}

void Rect2f::Draw( void ) const {

    /*
    mRadius =
        ( ( mWidthHeight->X * mWidthHeight ) + ( mWidthHeight->Y * mWidthHeight->Y ) ) / 2;*/

    const int numPoints = mRadius * 1000;
    glBegin( GL_POLYGON_SMOOTH );
    glColor3f( mColor.X, mColor.Y, mColor.Z );

    for ( double i = 0; i < mRadius; i++ )
    {
        const float x = mCenter.X + std::cos( i / numPoints * 2 * PI ) * mRadius;
        const float y = mCenter.Y + std::sin( i / numPoints * 2 * PI ) * mRadius;
        glVertex3f( x, y, 0.0f );
    }

    glEnd();
}

/***********/
/* PRIVATE */
/***********/


