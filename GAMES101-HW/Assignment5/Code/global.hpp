#pragma once

#include <cmath>
#include <iostream>
#include <random>

#define M_PI 3.14159265358979323846

constexpr float kInfinity = std::numeric_limits<float>::max();

/**
 * @brief 将一个值限制在给定的范围内。
 * 
 * @param lo 下限。
 * @param hi 上限。
 * @param v 要限制的值。
 * @return float 限制后的值。
 */
inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}

/**
 * @brief 求解二次方程ax^2 + bx + c = 0的解。
 * 
 * @param a 二次项系数。
 * @param b 一次项系数。
 * @param c 常数项系数。
 * @param x0 第一个解。
 * @param x1 第二个解。
 * @return true 如果有解。
 * @return false 如果无解。
 */
inline bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0)
        return false;
    else if (discr == 0)
        x0 = x1 = -0.5 * b / a;
    else
    {
        float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1)
        std::swap(x0, x1);
    return true;
}

/**
 * @brief 材质类型枚举。
 */
enum MaterialType
{
    DIFFUSE_AND_GLOSSY, // 漫反射和高光
    REFLECTION_AND_REFRACTION,  // 反射和折射
    REFLECTION  // 反射
};

/**
 * @brief 生成一个0到1之间的随机浮点数。
 * 
 * @return float 随机浮点数。
 */
inline float get_random_float()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.f, 1.f); // distribution in range [1, 6]

    return dist(rng);
}

/**
 * @brief 更新进度条。
 * 
 * @param progress 进度，取值范围为[0, 1]。
 */
inline void UpdateProgress(float progress)
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}