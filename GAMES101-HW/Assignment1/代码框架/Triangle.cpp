//
// Created by LEI XU on 4/11/19.
//

#include "Triangle.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

/**
 * @brief 构造函数，初始化三角形的顶点坐标、颜色和纹理坐标。
 */
Triangle::Triangle()
{
    v[0] << 0, 0, 0;
    v[1] << 0, 0, 0;
    v[2] << 0, 0, 0;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;

    tex_coords[0] << 0.0, 0.0;
    tex_coords[1] << 0.0, 0.0;
    tex_coords[2] << 0.0, 0.0;
}

/**
 * @brief 设置第i个顶点的坐标。
 * @param ind 要设置的顶点的索引。
 * @param ver 新的顶点坐标。
 */
void Triangle::setVertex(int ind, Eigen::Vector3f ver)
{
    v[ind] = ver;
}

/**
 * @brief 设置第i个顶点的法向量。
 * @param ind 要设置的顶点的索引。
 * @param n 新的法向量。
 */
void Triangle::setNormal(int ind, Vector3f n)
{
    normal[ind] = n;
}

/**
 * @brief 设置第i个顶点的颜色。
 * @param ind 要设置的顶点的索引。
 * @param r 颜色的红色分量。
 * @param g 颜色的绿色分量。
 * @param b 颜色的蓝色分量。
 * @throw std::runtime_error 如果颜色分量不在0到255之间，则抛出异常。
 */
void Triangle::setColor(int ind, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    color[ind] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    return;
}

/**
 * @brief 设置第i个顶点的纹理坐标。
 * @param ind 要设置的顶点的索引。
 * @param s 纹理坐标的u分量。
 * @param t 纹理坐标的v分量。
 */
void Triangle::setTexCoord(int ind, float s, float t)
{
    tex_coords[ind] = Vector2f(s, t);
}

/**
 * @brief 将三角形转换为四维向量数组。
 * @return 一个包含三个四维向量的数组，每个向量表示一个顶点。
 */
std::array<Vector4f, 3> Triangle::toVector4() const
{
    std::array<Vector4f, 3> res;
    std::transform(std::begin(v), std::end(v), res.begin(), [](auto& vec) {
        return Vector4f(vec.x(), vec.y(), vec.z(), 1.f);
    });
    return res;
}
