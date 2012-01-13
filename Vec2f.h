#pragma once

class Vec2f
{
public:
    Vec2f( float x = 0, float y = 0 );

    Vec2f( const Vec2f& v );

    float distanceTo( const Vec2f& v ) const;

    float magnitude( void ) const;

    void normalize( void );

    float& operator[]( int i );

    Vec2f& operator+=( const Vec2f& v );
    Vec2f& operator+=( const float s );

    Vec2f& operator-=( const Vec2f& v );
    Vec2f& operator-=( const float s );

    Vec2f& operator*=( const Vec2f& v );
    Vec2f& operator*=( const float s );

    Vec2f& operator/=( const Vec2f& v );
    Vec2f& operator/=( const float s );

    void vertex2f( void ) const;

    void vertex3f( void ) const;

    float X;
    float Y;

private:
    float* mData;
};

float dot( const Vec2f& a, const Vec2f& b );

Vec2f operator+( Vec2f a, const Vec2f& b );
Vec2f operator+( Vec2f a, float s );

Vec2f operator-( Vec2f a, const Vec2f& b );
Vec2f operator-( Vec2f a, float s );
Vec2f operator-( Vec2f a );

Vec2f operator*( Vec2f a, const Vec2f& b );
Vec2f operator*( Vec2f a, float s );

Vec2f operator/( Vec2f a, const Vec2f& b );
Vec2f operator/( Vec2f a, float s );
