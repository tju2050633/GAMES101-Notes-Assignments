#pragma once

#include "Object.hpp"
#include "Vector.hpp"

/**
 * @brief 表示一个球体。
 * 
 * 该类继承自Object类，包含了球体的中心坐标和半径。
 * 它实现了Object类中的两个纯虚函数，用于计算球体和光线的交点、获取球体表面的属性等。
 */
class Sphere : public Object
{
public:
    /**
     * @brief 构造函数，创建一个具有给定中心坐标和半径的球体。
     * 
     * @param c 球体的中心坐标。
     * @param r 球体的半径。
     */
    Sphere(const Vector3f& c, const float& r)
        : center(c)
        , radius(r)
        , radius2(r * r)
    {}

    /**
     * @brief 计算球体和光线的交点。
     * 
     * @param orig 光线的起点。
     * @param dir 光线的方向。
     * @param tnear 光线和球体的交点距离。
     * @param objectId 球体的ID。
     * @param uv 球体表面的纹理坐标。
     * @return true 如果光线和球体相交。
     * @return false 如果光线和球体不相交。
     */
    bool intersect(const Vector3f& orig, const Vector3f& dir, float& tnear, uint32_t&, Vector2f&) const override
    {
        // 解析解
        Vector3f L = orig - center;
        float a = dotProduct(dir, dir);
        float b = 2 * dotProduct(dir, L);
        float c = dotProduct(L, L) - radius2;
        float t0, t1;
        // 无解，光线和球体不相交
        if (!solveQuadratic(a, b, c, t0, t1))
            return false;
        // 可能物体在光源后面、或者光线起点在球体内部
        if (t0 < 0)
            t0 = t1;
        // 物体在光源后面
        if (t0 < 0)
            return false;
        tnear = t0;

        return true;
    }

    /**
     * @brief 获取球体表面的属性。
     * 
     * @param P 球体和光线的交点。
     * @param viewDirection 观察方向。
     * @param objectId 球体的ID。
     * @param uv 球体表面的纹理坐标。
     * @param N 球体表面的法向量。
     * @param tangent 球体表面的切向量。
     */
    void getSurfaceProperties(const Vector3f& P, const Vector3f&, const uint32_t&, const Vector2f&,
                              Vector3f& N, Vector2f&) const override
    {
        N = normalize(P - center);
    }

    /**
     * @brief 球体的中心坐标。
     */
    Vector3f center;

    /**
     * @brief 球体的半径。
     */
    float radius;

    /**
     * @brief 球体的半径的平方。
     */
    float radius2;
};