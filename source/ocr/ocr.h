//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_OCR_H
#define LIBOCR_OCR_H

#include <opencv2/core/mat.hpp>
#include <string>

namespace libocr
{
    namespace onnx
    {
        class text_detector;
        class text_recognizer;
    } // namespace onnx
    using detector_ptr = std::shared_ptr<onnx::text_detector>;
    using recognizer_ptr = std::shared_ptr<onnx::text_recognizer>;

    std::string recognize(recognizer_ptr recognizer, const cv::Mat& image);
    std::string detect_and_recognize(detector_ptr detector, recognizer_ptr recognizer, const cv::Mat& image);
} // namespace libocr

#endif //LIBOCR_OCR_H
