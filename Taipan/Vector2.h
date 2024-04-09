#pragma once

class Vector2 {
public:
    int x;
    int y;

    Vector2(int x = 0, int y = 0);
    static float dot(const Vector2& a, const Vector2& b);

    friend Vector2 operator+(const Vector2& a, const Vector2& b);
    friend Vector2 operator-(const Vector2& a, const Vector2& b);
    friend Vector2 operator*(const Vector2& vector, int scalar);
};