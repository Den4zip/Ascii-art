#include "imageconverter.h"
#include <opencv2/opencv.hpp>
#include <cmath>

std::string ImageConverter::convertToAscii(const cv::Mat &image, int width)
{
    if(image.empty()) return "Error: Empty image";

    const std::string gradient = " .:!/r(l1Z?*@W8#";
    float aspect = 11.0f / 24.0f;
    int height = static_cast<int>(width * aspect * image.rows / image.cols);

    cv::Mat resized, gray;
    cv::resize(image, resized, cv::Size(width, height), 0, 0, cv::INTER_CUBIC); // Улучшенное масштабирование
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    std::string asciiArt;
    for(int y = 0; y < gray.rows; ++y) {
        for(int x = 0; x < gray.cols; ++x) {
            uchar pixel = gray.at<uchar>(y, x);
            // Более точное преобразование яркости
            asciiArt += gradient[static_cast<int>(pixel / 255.0 * (gradient.size() - 1))];
        }
        asciiArt += '\n';
    }
    return asciiArt;
}
