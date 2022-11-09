//
// Created by GengG on 2022/11/9.
//

#include "ocr_manager.h"
//#include "../onnx/text_recognizer/text_recognizer.h"

libocr::ocr_manager::ocr_manager() {

}

libocr::ocr_manager &libocr::ocr_manager::get_instance() {
    static ocr_manager instance;
    return instance;
}

std::string libocr::ocr_manager::recognize(cv::Mat &image) {
    text_rec.run(image);
    return text_rec.get_output();
}

int libocr::ocr_manager::recognize(int image_width, int image_height, const char *image_data, int image_data_size,
                                              char *result, int result_size) {
    cv::Mat image = cv::Mat(image_height, image_width, CV_8UC3, (void *) image_data);
    std::string text = recognize(image);
    if (text.size() > result_size) {
        return -1;
    }
    memcpy(result, text.c_str(), text.size());
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_data, int image_data_size, char *result, int result_size) {
    cv::Mat image = cv::imdecode(cv::Mat(1, image_data_size, CV_8UC3, (void *) image_data), cv::IMREAD_COLOR);
    std::string text = recognize(image);
    if (text.size() > result_size) {
        return -1;
    }
    memcpy(result, text.c_str(), text.size());
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_file, char *result, int result_size) {
    cv::Mat image = cv::imread(image_file, cv::IMREAD_COLOR);
    std::string text = recognize(image);
    if (text.size() > result_size) {
        return -1;
    }
    memcpy(result, text.c_str(), text.size());
    return 0;
}
