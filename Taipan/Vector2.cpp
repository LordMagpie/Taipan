#include "Vector2.h"

Vector2::Vector2(int x, int y) : x(x), y(y) {}

Vector2 operator+(const Vector2& a, const Vector2& b) {
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(const Vector2& a, const Vector2& b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator*(const Vector2& vector, int scalar) {
    return Vector2(vector.x * scalar, vector.y * scalar);
}

float Vector2::dot(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}