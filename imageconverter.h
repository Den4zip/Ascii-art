#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <opencv2/opencv.hpp>
#include <string>

class ImageConverter
{
public:
    static std::string convertToAscii(const cv::Mat &image, int width = 80);
};

#endif // IMAGECONVERTER_H
