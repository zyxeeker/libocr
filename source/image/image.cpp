//
// Created by GengG on 2024/8/18.
//
#include "image.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

std::expected<cv::Mat,std::string> libocr::image(int image_width, int image_height, const char* image_data, int image_data_size)
{
    if (image_data_size != image_width * image_height * 3)
        return std::unexpected("Invalid image data size");
    cv::Mat image = cv::Mat(image_height, image_width, CV_8UC3, (void*)image_data);
    if (image.empty())
        return std::unexpected("Failed to create image");
    return image;
}
std::expected<cv::Mat,std::string> libocr::image(int image_width, int image_height, const char* image_data, unsigned int row_pitch)
{
    if (row_pitch % image_width != 0)
        return std::unexpected("Invalid row pitch");
    auto channels = row_pitch / image_width;
    if (channels != 3 && channels != 4 && channels != 1)
        return std::unexpected("Invalid image channels");
    cv::Mat image = cv::Mat(image_height, image_width, CV_MAKE_TYPE(CV_8U, channels), (void*)image_data, row_pitch);
    if (image.empty())
        return std::unexpected("Failed to create image");
    if (channels == 4)
        cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
    return image;
}
std::expected<cv::Mat,std::string> libocr::image(int image_width, int image_height, const char* image_data, int image_data_size, int image_channels)
{
    if (image_data_size != image_width * image_height * image_channels)
        return std::unexpected("Invalid image data size");
    cv::Mat image = cv::Mat(image_height, image_width, CV_MAKE_TYPE(CV_8U, image_channels), (void*)image_data);
    if (image.empty())
        return std::unexpected("Failed to create image");
    if (image_channels == 4)
        cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
    return image;
}
std::expected<cv::Mat,std::string> libocr::image(const char* image_raw, int image_raw_size)
{
    cv::Mat image = cv::imdecode(cv::Mat(1, image_raw_size, CV_8UC1, (void*)image_raw), cv::IMREAD_COLOR);
    if (image.empty())
        return std::unexpected("Failed to decode image data");
    return image;
}
std::expected<cv::Mat,std::string> libocr::image(const char* image_file)
{
    cv::Mat image = cv::imread(image_file, cv::IMREAD_COLOR);
    if (image.empty())
        return std::unexpected("Failed to read image file");
    return image;
}