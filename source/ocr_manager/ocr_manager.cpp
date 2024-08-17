//
// Created by GengG on 2022/11/9.
//

#include "ocr_manager.h"
#include "../onnx/text_detector/text_detector.h"
#include "../onnx/text_recognizer/text_recognizer.h"

void libocr::ocr_manager::init()
{
    if (!initialized)
    {
        detector = std::make_shared<onnx::text_detector>();
        recognizer = std::make_shared<onnx::text_recognizer>();
        initialized = true;
    }
}
