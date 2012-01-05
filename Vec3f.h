#pragma once

struct Vec3f
{
    Vec3f( float x = 0, float y = 0, float z = 0 );

    float distanceTo( const Vec3f& v ) const;

    float& operator[]( int i );

    void rand( void );

    float X;
    float Y;
    float Z;

private:
    float* mData;

};
