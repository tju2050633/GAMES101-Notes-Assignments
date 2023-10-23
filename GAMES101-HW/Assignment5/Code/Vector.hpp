#pragma once

#include <cmath>
#include <iostream>

// 三维向量：标量乘法、标量除法、加法、减法、取反、点乘、叉乘
class Vector3f
{
public:
    Vector3f()
        : x(0)
        , y(0)
        , z(0)
    {}
    Vector3f(float xx)
        : x(xx)
        , y(xx)
        , z(xx)
    {}
    Vector3f(float xx, float yy, float zz)
        : x(xx)
        , y(yy)
        , z(zz)
    {}
    Vector3f operator*(const float& r) const
    {
        return Vector3f(x * r, y * r, z * r);
    }
    Vector3f operator/(const float& r) const
    {
        return Vector3f(x / r, y / r, z / r);
    }

    Vector3f operator*(const Vector3f& v) const
    {
        return Vector3f(x * v.x, y * v.y, z * v.z);
    }
    Vector3f operator-(const Vector3f& v) const
    {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }
    Vector3f operator+(const Vector3f& v) const
    {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }
    Vector3f operator-() const
    {
        return Vector3f(-x, -y, -z);
    }
    Vector3f& operator+=(const Vector3f& v)
    {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    friend Vector3f operator*(const float& r, const Vector3f& v)
    {
        return Vector3f(v.x * r, v.y * r, v.z * r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v)
    {
        return os << v.x << ", " << v.y << ", " << v.z;
    }
    float x, y, z;
};

// 二维向量：标量乘法、加法
class Vector2f
{
public:
    Vector2f()
        : x(0)
        , y(0)
    {}
    Vector2f(float xx)
        : x(xx)
        , y(xx)
    {}
    Vector2f(float xx, float yy)
        : x(xx)
        , y(yy)
    {}
    Vector2f operator*(const float& r) const
    {
        return Vector2f(x * r, y * r);
    }
    Vector2f operator+(const Vector2f& v) const
    {
        return Vector2f(x + v.x, y + v.y);
    }
    float x, y;
};

// 线性插值
inline Vector3f lerp(const Vector3f& a, const Vector3f& b, const float& t)
{
    return a * (1 - t) + b * t;
}

// 归一化
inline Vector3f normalize(const Vector3f& v)
{
    float mag2 = v.x * v.x + v.y * v.y + v.z * v.z;
    if (mag2 > 0)
    {
        float invMag = 1 / sqrtf(mag2);
        return Vector3f(v.x * invMag, v.y * invMag, v.z * invMag);
    }

    return v;
}

// 点乘
inline float dotProduct(const Vector3f& a, const Vector3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 叉乘
inline Vector3f crossProduct(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}