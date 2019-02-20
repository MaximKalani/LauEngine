#ifndef VECTOR2D_HPP_INCLUDED
#define VECTOR2D_HPP_INCLUDED
#include <iostream>

class Vector2D
{
public:
    float x;
    float y;
    
    Vector2D();
    Vector2D(float x, float y);
    
    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);
    
    Vector2D operator+(const Vector2D& vec);
    Vector2D operator-(const Vector2D& vec);
    Vector2D operator*(const Vector2D& vec);
    Vector2D operator/(const Vector2D& vec);
    
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);
    
    Vector2D& operator*(const int& i);
    
    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
    
};


#endif // VECTOR2D_HPP_INCLUDED