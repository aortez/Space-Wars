#pragma once

class Vec2f
{
public:
    Vec2f( float x = 0, float y = 0 );

    float distanceTo( const Vec2f& v ) const;

    float& operator[]( int i );

    float X;
    float Y;

private:
    float* mData;
};
