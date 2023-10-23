#pragma once

#include <vector>
#include <memory>
#include "Vector.hpp"
#include "Object.hpp"
#include "Light.hpp"

/**
 * @brief 表示一个场景。
 * 
 * 该类包含了场景的宽度、高度、视角、背景颜色、最大递归深度和epsilon值等属性，
 * 以及场景中的物体和光源等元素。
 */
class Scene
{
public:
    // setting up options
    int width = 1280;
    int height = 960;
    double fov = 90;
    Vector3f backgroundColor = Vector3f(0.235294, 0.67451, 0.843137);
    int maxDepth = 5;
    float epsilon = 0.00001;

    /**
     * @brief 构造函数，创建一个具有给定宽度和高度的场景。
     * 
     * @param w 场景的宽度。
     * @param h 场景的高度。
     */
    Scene(int w, int h) : width(w), height(h)
    {}

    /**
     * @brief 向场景中添加一个物体。
     * 
     * @param object 要添加的物体。
     */
    void Add(std::unique_ptr<Object> object) { objects.push_back(std::move(object)); }

    /**
     * @brief 向场景中添加一个光源。
     * 
     * @param light 要添加的光源。
     */
    void Add(std::unique_ptr<Light> light) { lights.push_back(std::move(light)); }

    /**
     * @brief 获取场景中的物体列表。
     * 
     * @return const std::vector<std::unique_ptr<Object>>& 物体列表。
     */
    [[nodiscard]] const std::vector<std::unique_ptr<Object> >& get_objects() const { return objects; }

    /**
     * @brief 获取场景中的光源列表。
     * 
     * @return const std::vector<std::unique_ptr<Light>>& 光源列表。
     */
    [[nodiscard]] const std::vector<std::unique_ptr<Light> >&  get_lights() const { return lights; }

private:
    // creating the scene (adding objects and lights)
    /**
     * @brief 场景中的物体列表。
     */
    std::vector<std::unique_ptr<Object> > objects;

    /**
     * @brief 场景中的光源列表。
     */
    std::vector<std::unique_ptr<Light> > lights;
};