#pragma once

#include "Vector.hpp"

/**
 * @brief 表示场景中的光源。
 * 
 * 该类包含了光源的位置和强度，用于计算场景中物体的光照效果。
 */
class Light
{
public:
    /**
     * @brief 构造函数，用给定的位置和强度创建一个新的光源。
     * 
     * @param p 光源的位置。
     * @param i 光源的强度。
     */
    Light(const Vector3f& p, const Vector3f& i)
        : position(p)
        , intensity(i)
    {}

    /**
     * @brief 虚析构函数，确保对象在通过基类指针删除时正确释放。
     */
    virtual ~Light() = default;

    /**
     * @brief 光源的位置。
     */
    Vector3f position;

    /**
     * @brief 光源的强度。
     * 
     * 这表示光源的颜色和亮度。每个分量的值分别表示红、绿、蓝三个通道的强度。
     */
    Vector3f intensity;
};