#pragma once
const float PI = 3.14159265358979323846;

class Shape
{
public:
    Shape( void );

    virtual ~Shape( void );

    virtual void Draw( void ) const = 0;
};
