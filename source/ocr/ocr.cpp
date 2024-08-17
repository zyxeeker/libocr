//
// Created by GengG on 2022/11/9.
//

#include "ocr.h"
#include "../onnx/text_detector/text_detector.h"
#include "../onnx/text_recognizer/text_recognizer.h"

std::string libocr::recognize(recognizer_ptr recognizer, const cv::Mat& image)
{
    return recognizer->run(image);
}

std::string libocr::detect_and_recognize(detector_ptr detector, recognizer_ptr recognizer, const cv::Mat& image)
{
    std::string texts;
    for (auto& area : detector->run(image))
        texts += recognize(recognizer, image(area.rect));
    return texts;
}
