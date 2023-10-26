//
// Created by goksu on 4/6/19.
//

#pragma once

#include <eigen3/Eigen/Eigen>
#include <optional>
#include <algorithm>
#include "global.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"

using namespace Eigen;

namespace rst
{
    // 缓存类型枚举，包括颜色和深度缓存
    enum class Buffers
    {
        Color = 1,
        Depth = 2
    };

    // 按位或运算符重载，用于将两个缓存类型进行组合
    inline Buffers operator|(Buffers a, Buffers b)
    {
        return Buffers((int)a | (int)b);
    }

    // 按位与运算符重载，用于检查一个缓存类型是否包含另一个缓存类型
    inline Buffers operator&(Buffers a, Buffers b)
    {
        return Buffers((int)a & (int)b);
    }

    // 图元类型枚举，包括线段和三角形
    enum class Primitive
    {
        Line,
        Triangle
    };

    // 顶点位置缓存结构体，包含缓存 ID
    struct pos_buf_id
    {
        int pos_id = 0;
    };

    // 顶点索引缓存结构体，包含缓存 ID
    struct ind_buf_id
    {
        int ind_id = 0;
    };

    // 顶点颜色缓存结构体，包含缓存 ID
    struct col_buf_id
    {
        int col_id = 0;
    };

    // 光栅化器类，用于将三维图形渲染到二维屏幕上
    class rasterizer
    {
    public:
        rasterizer(int w, int h);   // 构造函数，接受屏幕宽度和高度
        pos_buf_id load_positions(const std::vector<Eigen::Vector3f>& positions);   // 加载顶点位置缓存
        ind_buf_id load_indices(const std::vector<Eigen::Vector3i>& indices);       // 加载顶点索引缓存
        col_buf_id load_colors(const std::vector<Eigen::Vector3f>& colors);         // 加载顶点颜色缓存
        col_buf_id load_normals(const std::vector<Eigen::Vector3f>& normals);       // 加载顶点法向量缓存

        void set_model(const Eigen::Matrix4f& m);       // 设置模型矩阵
        void set_view(const Eigen::Matrix4f& v);        // 设置视图矩阵
        void set_projection(const Eigen::Matrix4f& p);  // 设置投影矩阵

        void set_texture(Texture tex) { texture = tex; }    // 设置纹理

        void set_vertex_shader(std::function<Eigen::Vector3f(vertex_shader_payload)> vert_shader);    // 设置顶点着色器
        void set_fragment_shader(std::function<Eigen::Vector3f(fragment_shader_payload)> frag_shader);  // 设置片段着色器

        void set_pixel(const Vector2i &point, const Eigen::Vector3f &color);   // 设置像素颜色

        void clear(Buffers buff);   // 清空缓存

        void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type);   // 绘制图元
        void draw(std::vector<Triangle *> &TriangleList);   // 绘制三角形列表

        std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }   // 获取帧缓存

    private:
        void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);   // 绘制线段

        void rasterize_triangle(const Triangle& t, const std::array<Eigen::Vector3f, 3>& world_pos);   // 光栅化三角形

    private:
        Eigen::Matrix4f model;      // 模型矩阵
        Eigen::Matrix4f view;       // 视图矩阵
        Eigen::Matrix4f projection; // 投影矩阵

        int normal_id = -1;

        std::map<int, std::vector<Eigen::Vector3f>> pos_buf;    // 顶点位置缓存
        std::map<int, std::vector<Eigen::Vector3i>> ind_buf;    // 顶点索引缓存
        std::map<int, std::vector<Eigen::Vector3f>> col_buf;    // 顶点颜色缓存
        std::map<int, std::vector<Eigen::Vector3f>> nor_buf;    // 顶点法向量缓存

        std::optional<Texture> texture;    // 纹理

        std::function<Eigen::Vector3f(fragment_shader_payload)> fragment_shader;    // 片段着色器
        std::function<Eigen::Vector3f(vertex_shader_payload)> vertex_shader;        // 顶点着色器

        std::vector<Eigen::Vector3f> frame_buf;   // 帧缓存
        std::vector<float> depth_buf;             // 深度缓存
        int get_index(int x, int y);              // 获取像素索引

        int width, height;    // 屏幕宽度和高度

        int next_id = 0;
        int get_next_id() { return next_id++; }   // 获取下一个缓存 ID
    };
}
