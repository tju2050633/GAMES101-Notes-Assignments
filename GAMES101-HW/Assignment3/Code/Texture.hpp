//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

// 纹理类，包含纹理图像和宽度、高度
class Texture{
private:
    cv::Mat image_data;   // 纹理图像

public:
    Texture(const std::string& name)
    {
        // 读取纹理图像并转换为BGR格式
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);

        // 计算纹理宽度和高度
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;   // 纹理宽度和高度

    // 获取纹理颜色
    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }
};

#endif //RASTERIZER_TEXTURE_H
