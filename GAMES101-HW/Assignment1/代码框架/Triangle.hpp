//
// Created by LEI XU on 4/11/19.
//

#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include <eigen3/Eigen/Eigen>
using namespace Eigen;

class Triangle
{
public:
    Vector3f v[3]; /*三角形的原始坐标，v0、v1、v2按逆时针顺序排列*/

    /*每个顶点的值*/
    Vector3f color[3];      // 每个顶点的颜色
    Vector2f tex_coords[3]; // 每个顶点的纹理坐标
    Vector3f normal[3];     // 每个顶点的法向量

    // Texture *tex;
    Triangle(); // 构造函数

    Eigen::Vector3f a() const { return v[0]; } // 返回第一个顶点的坐标
    Eigen::Vector3f b() const { return v[1]; } // 返回第二个顶点的坐标
    Eigen::Vector3f c() const { return v[2]; } // 返回第三个顶点的坐标

    void setVertex(int ind, Vector3f ver); /*设置第i个顶点的坐标*/
    void setNormal(int ind, Vector3f n);   /*设置第i个顶点的法向量*/
    void setColor(int ind, float r, float g, float b); /*设置第i个顶点的颜色*/
    void setTexCoord(int ind, float s, float t); /*设置第i个顶点的纹理坐标*/
    std::array<Vector4f, 3> toVector4() const; // 将三角形转换为四维向量数组
};

#endif // RASTERIZER_TRIANGLE_H
