//
// Created by goksu on 4/6/19.
//

#pragma once

#include <eigen3/Eigen/Eigen>
#include <algorithm>
#include "global.hpp"
#include "Triangle.hpp"
using namespace Eigen;

namespace rst
{
    enum class Buffers
    {
        Color = 1, // 颜色缓存
        Depth = 2 // 深度缓存
    };

    // 两个缓存类型的组合
    inline Buffers operator|(Buffers a, Buffers b)
    {
        return Buffers((int)a | (int)b);
    }

    // 两个缓存类型的交集
    inline Buffers operator&(Buffers a, Buffers b)
    {
        return Buffers((int)a & (int)b);
    }

    enum class Primitive
    {
        Line, // 线段
        Triangle // 三角形
    };

    /*
     * For the curious : The draw function takes two buffer id's as its arguments. These two structs
     * make sure that if you mix up with their orders, the compiler won't compile it.
     * Aka : Type safety
     * */
    struct pos_buf_id
    {
        int pos_id = 0; // 顶点位置信息的缓存 ID
    };

    struct ind_buf_id
    {
        int ind_id = 0; // 三角形索引信息的缓存 ID
    };

    struct col_buf_id
    {
        int col_id = 0; // 顶点颜色信息的缓存 ID
    };

    class rasterizer
    {
    public:
        // 构造函数，初始化宽度和高度
        rasterizer(int w, int h);

        // 加载顶点位置信息，返回顶点位置信息的缓存 ID
        pos_buf_id load_positions(const std::vector<Eigen::Vector3f>& positions);

        // 加载三角形索引信息，返回三角形索引信息的缓存 ID
        ind_buf_id load_indices(const std::vector<Eigen::Vector3i>& indices);

        // 加载顶点颜色信息，返回顶点颜色信息的缓存 ID
        col_buf_id load_colors(const std::vector<Eigen::Vector3f>& colors);

        // 设置MVP矩阵
        void set_model(const Eigen::Matrix4f& m);
        void set_view(const Eigen::Matrix4f& v);
        void set_projection(const Eigen::Matrix4f& p);

        // 设置像素颜色
        void set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color);

        // 清空缓存
        void clear(Buffers buff);

        // 绘制三角形
        void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type);

        // 获取帧缓存
        std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }

    private:
        // 绘制线段
        void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);

        // 光栅化三角形
        void rasterize_triangle(const Triangle& t);

        // VERTEX SHADER -> MVP -> Clipping -> /.W -> VIEWPORT -> DRAWLINE/DRAWTRI -> FRAGSHADER

    private:
        Eigen::Matrix4f model; // 模型矩阵
        Eigen::Matrix4f view; // 视图矩阵
        Eigen::Matrix4f projection; // 投影矩阵

        std::map<int, std::vector<Eigen::Vector3f>> pos_buf; // 顶点位置信息缓存
        std::map<int, std::vector<Eigen::Vector3i>> ind_buf; // 三角形索引信息缓存
        std::map<int, std::vector<Eigen::Vector3f>> col_buf;

        std::vector<Eigen::Vector3f> frame_buf; // 帧缓存
        std::vector<float> depth_buf; // 深度缓存
        int get_index(int x, int y); // 获取像素在帧缓存中的索引

        int width, height; // 宽度和高度

        int next_id = 0; // 下一个缓存 ID
        int get_next_id() { return next_id++; } // 缓存 ID自增
    };
}
