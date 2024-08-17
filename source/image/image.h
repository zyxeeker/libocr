//
// Created by GengG on 2024/8/18.
//

#ifndef LIBOCR_IMAGE_H
#define LIBOCR_IMAGE_H

#include <expected>
#include <string>
#include <opencv2/core/mat.hpp>

namespace libocr
{
    std::expected<cv::Mat, std::string> image(int image_width, int image_height, const char* image_data, int image_data_size);
    std::expected<cv::Mat, std::string> image(int image_width, int image_height, const char* image_data, unsigned int row_pitch);
    std::expected<cv::Mat, std::string> image(int image_width, int image_height, const char* image_data, int image_data_size, int image_channels);
    std::expected<cv::Mat, std::string> image(const char* image_raw, int image_raw_size);
    std::expected<cv::Mat, std::string> image(const char* image_file);
} // namespace libocr

#endif // LIBOCR_IMAGE_H
