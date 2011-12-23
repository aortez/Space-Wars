#pragma once

struct Vec3f
{
    Vec3f(
        float x = 0,
        float y = 0,
        float z = 0 )
        : X( x ),
          Y( y ),
          Z( z ),
          mData( &X )
    {
    }

    float& operator[]( size_t i )
    {
        return mData[ i ];
    }


    float X;
    float Y;
    float Z;

private:
    float* mData;

};
