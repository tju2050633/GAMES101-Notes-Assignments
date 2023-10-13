#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

// 点一下画一个控制点（最多4）
void mouse_handler(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) {
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 + 3 * std::pow(t, 2) * (1 - t) * p_2 +
                     std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) {
    // 如果控制点数量为 1，直接返回该点
    if (control_points.size() == 1) {
        return control_points[0];
    }

    // 递归计算中间点
    std::vector<cv::Point2f> mid_points;
    for (int i = 0; i < control_points.size() - 1; ++i) {
        mid_points.push_back((1 - t) * control_points[i] + t * control_points[i + 1]);
    }

    // 递归计算贝塞尔曲线上的点
    return recursive_bezier(mid_points, t);
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) {
    // 遍历所有 t 值，计算贝塞尔曲线上的点
    for (float t = 0; t <= 1; t += 0.001) {
        auto point = recursive_bezier(control_points, t);

        // 将点坐标转换为整数
        int x = static_cast<int>(point.x);
        int y = static_cast<int>(point.y);

        // 绘制点
        window.at<cv::Vec3b>(y, x)[1] = 255;
    }
}

int main() {
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) {
        // 画出控制点
        for (auto &point : control_points) {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        // 有4个点后，画出bezier曲线
        if (control_points.size() == 4) {
            naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

    return 0;
}
