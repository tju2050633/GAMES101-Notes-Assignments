#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

/**
 * 获取视图矩阵
 * @param eye_pos 相机位置
 * @return 视图矩阵
 */
Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    // 构造平移矩阵，将相机位置变换到原点
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 
                 0, 1, 0, -eye_pos[1], 
                 0, 0, 1, -eye_pos[2], 
                 0, 0, 0, 1;

    // 将平移矩阵与单位矩阵相乘得到视图矩阵
    view = translate * view;

    return view;
}

/**
 * 获取模型矩阵
 * @param rotation_angle 旋转角度
 * @return 模型矩阵
 */
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.

    // 构造旋转矩阵，将三角形绕 Z 轴旋转指定角度
    Eigen::Matrix4f rotate;

    double rad = rotation_angle * MY_PI / 180;
    rotate << cos(rad), -sin(rad), 0, 0,
            sin(rad), cos(rad), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    // 将旋转矩阵与单位矩阵相乘得到模型矩阵
    model = rotate * model;

    return model;
}

/**
 * 获取投影矩阵
 * @param eye_fov 视野角度
 * @param aspect_ratio 屏幕宽高比
 * @param zNear 近平面距离
 * @param zFar 远平面距离
 * @return 投影矩阵
 */
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    // 计算 cot 视野角度的一半
    float cot_fov = 1.0f / tanf(eye_fov / 2.0f);

    // 构造投影矩阵
    projection(0, 0) = cot_fov / aspect_ratio;
    projection(1, 1) = cot_fov;
    projection(2, 2) = (zFar + zNear) / (zNear - zFar);
    projection(2, 3) = 2.0f * zFar * zNear / (zNear - zFar);
    projection(3, 2) = -1.0f;
    projection(3, 3) = 0.0f;

    return projection;
}

int main(int argc, const char** argv)
{
    // 初始化变量
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    // 处理命令行参数
    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    // 创建光栅化器对象
    rst::rasterizer r(700, 700);

    // 设置相机位置
    Eigen::Vector3f eye_pos = {0, 0, 5};

    // 定义三角形的顶点坐标和索引
    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};
    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    // 加载顶点坐标和索引到光栅化器中
    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    // 初始化变量
    int key = 0;
    int frame_count = 0;

    // 如果是命令行模式，则直接渲染图像并保存到文件
    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    // 如果是交互模式，则循环渲染图像并等待用户输入
    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        // 绘制三角形
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        // 将帧缓冲区中的像素数据转换为 OpenCV 的图像格式，并显示在窗口中
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);

        // 等待用户输入
        key = cv::waitKey(10);

        // 输出帧数
        std::cout << "frame count: " << frame_count++ << '\n';

        // 根据用户输入调整旋转角度
        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}