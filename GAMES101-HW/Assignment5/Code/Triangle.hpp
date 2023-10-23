#pragma once

#include "Object.hpp"

#include <cstring>

bool rayTriangleIntersect(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& orig,
                          const Vector3f& dir, float& tnear, float& u, float& v)
{
    // TODO: Implement this function that tests whether the triangle
    // that's specified bt v0, v1 and v2 intersects with the ray (whose
    // origin is *orig* and direction is *dir*)
    // Also don't forget to update tnear, u and v.

    // Moller Trumbore算法

    // 计算辅助向量
    Vector3f e1 = v1 - v0;
    Vector3f e2 = v2 - v0;
    Vector3f s = orig - v0;
    Vector3f s1 = crossProduct(dir, e2);
    Vector3f s2 = crossProduct(s, e1);

    // 右边的系数
    float divisor = dotProduct(s1, e1);
    if (divisor == 0)
        return false;
    float invDivisor = 1 / divisor;

    // 计算左边向量每个分量的值
    // tnear即t
    // u即b_1
    // v即b_2
    tnear = dotProduct(s2, e2) * invDivisor;
    if (tnear < 0)
        return false;

    u = dotProduct(s1, s) * invDivisor;
    if (u < 0 || u > 1)
        return false;

    v = dotProduct(s2, dir) * invDivisor;
    if (v < 0 || u + v > 1)
        return false;

    return true;
}

/**
 * @brief 表示一个由三角形组成的网格物体。
 * 
 * 该类继承自Object类，包含了网格物体的顶点、三角形索引、纹理坐标等属性。
 * 它还实现了Object类中的纯虚函数，用于计算物体和光线的交点、获取物体表面的属性等。
 */
class MeshTriangle : public Object
{
public:
    /**
     * @brief 构造函数，创建一个由三角形组成的网格物体。
     * 
     * @param verts 顶点数组。
     * @param vertsIndex 顶点索引数组。
     * @param numTris 三角形数量。
     * @param st 纹理坐标数组。
     */
    MeshTriangle(const Vector3f* verts, const uint32_t* vertsIndex, const uint32_t& numTris, const Vector2f* st)
    {
        // 计算顶点数组的大小
        uint32_t maxIndex = 0;
        for (uint32_t i = 0; i < numTris * 3; ++i)
            if (vertsIndex[i] > maxIndex)
                maxIndex = vertsIndex[i];
        maxIndex += 1;

        // 复制顶点数组、三角形索引数组和纹理坐标数组
        vertices = std::unique_ptr<Vector3f[]>(new Vector3f[maxIndex]);
        memcpy(vertices.get(), verts, sizeof(Vector3f) * maxIndex);
        vertexIndex = std::unique_ptr<uint32_t[]>(new uint32_t[numTris * 3]);
        memcpy(vertexIndex.get(), vertsIndex, sizeof(uint32_t) * numTris * 3);
        numTriangles = numTris;
        stCoordinates = std::unique_ptr<Vector2f[]>(new Vector2f[maxIndex]);
        memcpy(stCoordinates.get(), st, sizeof(Vector2f) * maxIndex);
    }

    /**
     * @brief 计算物体和光线的交点。
     * 
     * @param orig 光线的起点。
     * @param dir 光线的方向。
     * @param tnear 光线和物体的交点距离。
     * @param index 相交三角形的ID。
     * @param uv 物体表面的纹理坐标。
     * @return true 如果光线和物体相交。
     * @return false 如果光线和物体不相交。
     */
    bool intersect(const Vector3f& orig, const Vector3f& dir, float& tnear, uint32_t& index,
                   Vector2f& uv) const override
    {
        bool intersect = false;
        for (uint32_t k = 0; k < numTriangles; ++k)
        {
            const Vector3f& v0 = vertices[vertexIndex[k * 3]];
            const Vector3f& v1 = vertices[vertexIndex[k * 3 + 1]];
            const Vector3f& v2 = vertices[vertexIndex[k * 3 + 2]];
            float t, u, v;  // 这3个变量要在rayTriangleIntersect函数中更新
            if (rayTriangleIntersect(v0, v1, v2, orig, dir, t, u, v) && t < tnear)
            {
                tnear = t;
                uv.x = u;
                uv.y = v;
                index = k;
                intersect |= true;
            }
        }

        return intersect;
    }

    void getSurfaceProperties(const Vector3f&, const Vector3f&, const uint32_t& index, const Vector2f& uv, Vector3f& N,
                              Vector2f& st) const override
    {
        const Vector3f& v0 = vertices[vertexIndex[index * 3]];
        const Vector3f& v1 = vertices[vertexIndex[index * 3 + 1]];
        const Vector3f& v2 = vertices[vertexIndex[index * 3 + 2]];
        Vector3f e0 = normalize(v1 - v0);
        Vector3f e1 = normalize(v2 - v1);
        N = normalize(crossProduct(e0, e1));
        const Vector2f& st0 = stCoordinates[vertexIndex[index * 3]];
        const Vector2f& st1 = stCoordinates[vertexIndex[index * 3 + 1]];
        const Vector2f& st2 = stCoordinates[vertexIndex[index * 3 + 2]];
        st = st0 * (1 - uv.x - uv.y) + st1 * uv.x + st2 * uv.y;
    }

    /**
     * @brief 计算物体的漫反射颜色。
     * 
     * @param st 物体表面的纹理坐标。
     * @return Vector3f 漫反射颜色。
     */
    Vector3f evalDiffuseColor(const Vector2f& st) const override
    {
        float scale = 5;
        float pattern = (fmodf(st.x * scale, 1) > 0.5) ^ (fmodf(st.y * scale, 1) > 0.5);
        return lerp(Vector3f(0.815, 0.235, 0.031), Vector3f(0.937, 0.937, 0.231), pattern);
    }

    // 顶点数组、顶点索引数组和纹理坐标数组
    std::unique_ptr<Vector3f[]> vertices;
    uint32_t numTriangles;
    std::unique_ptr<uint32_t[]> vertexIndex;
    std::unique_ptr<Vector2f[]> stCoordinates;
};