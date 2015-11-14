//#include <QGLWidget>
//#include "Rectangle.h"

//Rectangle::Rectangle(
//        const Vec2f center,
//        const Vec2f dims,
//        const Vec3f color )
//    : Shape(
//          center,
//          ( dims * 0.5 ).magnitude() // bounding circle's radius is distance from center to corner
//          ),
//      mColor( color ),
//      mRadius( dims * 0.5 )
//{
//    mHP = Mass() * 50;
//}

//void Rectangle::Draw( void ) const
//{
//    glBegin( GL_LINE_STRIP );
//    glColor3f( mColor.X, mColor.Y, mColor.Z );

//    BottomLeft().vertex3f();
//    BottomRight().vertex3f();
//    TopRight().vertex3f();
//    TopLeft().vertex3f();
//    BottomLeft().vertex3f();

//    glEnd();
//}

//Vec2f Rectangle::BottomLeft( void ) const
//{
//    return mCenter - mRadius;
//}

//Vec2f Rectangle::BottomRight( void ) const
//{
//    return Vec2f( mCenter.X + mRadius.X,
//                  mCenter.Y - mRadius.Y );
//}

//void Rectangle::Collide( Circle& c )
//{
//    // TODO
//}

//void Rectangle::Collide( Rectangle& r )
//{
//    // TODO
//}

//void Rectangle::Collide( Shape& s )
//{
//    s.Collide( *this );
//}

//bool Rectangle::Intersects( const Circle& c ) const
//{
//    return false; // TODO
//}

//bool Rectangle::Intersects( const Rectangle& r ) const
//{
//    const bool withinBoundsRadius = mCenter.distanceTo( r.mCenter ) < ( mBoundsRadius + r.mBoundsRadius );
//    if ( !withinBoundsRadius )
//    {
//        return false;
//    }
//    else
//    {
//        // TODO: iterate over corners and see if one lies within the other rectangle
//        return true;
//    }
//}

//bool Rectangle::Intersects( const Shape& s ) const
//{
//    return s.Intersects( *this );
//}

//float Rectangle::Mass( void ) const
//{
//    // a = w * h
//    return ( mRadius.X * mRadius.Y ) * 2;
//}

//Vec2f Rectangle::TopLeft( void ) const
//{
//    return Vec2f( mCenter.X - mRadius.X,
//                  mCenter.Y + mRadius.Y );
//}

//Vec2f Rectangle::TopRight( void ) const
//{
//    return mCenter + mRadius;
//}
