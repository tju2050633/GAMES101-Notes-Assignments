#pragma once
#include "Scene.hpp"

// 交点信息
struct hit_payload
{
    float tNear;    // 交点距离
    uint32_t index; // 交点索引
    Vector2f uv;    // 交点uv坐标
    Object* hit_obj;    // 交点物体
};

class Renderer
{
public:
    void Render(const Scene& scene);

private:
};