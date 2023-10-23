#pragma once

#include "Vector.hpp"
#include "global.hpp"

/**
 * @brief 表示场景中的物体。
 * 
 * 该类包含了物体的材质属性，如漫反射系数、镜面反射系数、折射率等。
 * 它还定义了一些纯虚函数，用于计算物体和光线的交点、获取物体表面的属性等。
 */
class Object
{
public:
    /**
     * @brief 默认构造函数，创建一个具有默认材质属性的物体。
     */
    Object()
        : materialType(DIFFUSE_AND_GLOSSY)
        , ior(1.3)
        , Kd(0.8)
        , Ks(0.2)
        , diffuseColor(0.2)
        , specularExponent(25)
    {}

    /**
     * @brief 虚析构函数，确保对象在通过基类指针删除时正确释放。
     */
    virtual ~Object() = default;

    /**
     * @brief 计算物体和光线的交点。
     * 
     * @param orig 光线的起点。
     * @param dir 光线的方向。
     * @param t 光线和物体的交点距离。
     * @param objectId 物体的ID。
     * @param uv 物体表面的纹理坐标。
     * @return true 如果光线和物体相交。
     * @return false 如果光线和物体不相交。
     */
    virtual bool intersect(const Vector3f& orig, const Vector3f& dir, float& t, uint32_t& objectId, Vector2f& uv) const = 0;

    /**
     * @brief 获取物体表面的属性。
     * 
     * @param hitPoint 物体和光线的交点。
     * @param viewDirection 观察方向。
     * @param objectId 物体的ID。
     * @param uv 物体表面的纹理坐标。
     * @param hitNormal 物体表面的法向量。
     * @param tangent 物体表面的切向量。
     */
    virtual void getSurfaceProperties(const Vector3f& hitPoint, const Vector3f& viewDirection, const uint32_t& objectId,
                                      const Vector2f& uv, Vector3f& hitNormal, Vector2f& tangent) const = 0;

    /**
     * @brief 计算物体的漫反射颜色。
     * 
     * @param uv 物体表面的纹理坐标。
     * @return Vector3f 漫反射颜色。
     */
    virtual Vector3f evalDiffuseColor(const Vector2f& uv) const
    {
        return diffuseColor;
    }

    // 材质属性
    MaterialType materialType;
    float ior;
    float Kd, Ks;
    Vector3f diffuseColor;
    float specularExponent;
};