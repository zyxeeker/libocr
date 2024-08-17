//
// Created by GengG on 2022/11/9.
//
#include "libocr/libocr.h"
#include "image/image.h"
#include "ocr/ocr.h"
#include "ocr_manager/ocr_manager.h"

inline int ocr(auto&& image_exp, char* result, int result_size)
{
    if (!image_exp)
        return -1;
    auto text = libocr::detect_and_recognize(libocr::ocr_manager::get_instance().get_detector(), libocr::ocr_manager::get_instance().get_recognizer(), image_exp.value());
    if (text.empty())
        return -2;
    if (text.size() > result_size)
        return -3;
    strcpy(result, text.c_str());
    return 0;
}

int _stdcall ocr(const char* image_data, int image_data_size, char* result, int result_size)
{
    return ocr_file_data(image_data, image_data_size, result, result_size);
}

int _stdcall ocr_image_data(int image_width, int image_height, const char* image_data, int image_data_size, char* result, int result_size)
{
    auto image_exp = libocr::image(image_width, image_height, image_data, image_data_size);
    return ocr(image_exp, result, result_size);
}

int _stdcall ocr_image_data_rgba(int image_width, int image_height, const char* image_data, unsigned int row_pitch, char* result, int result_size)
{
    auto image_exp = libocr::image(image_width, image_height, image_data, row_pitch);
    return ocr(image_exp, result, result_size);
}

int _stdcall ocr_file_data(const char* image_data, int image_data_size, char* result, int result_size)
{
    auto image_exp = libocr::image(image_data, image_data_size);
    return ocr(image_exp, result, result_size);
}

int _stdcall ocr_file_path(const char* image_file, char* result, int result_size)
{
    auto image_exp = libocr::image(image_file);
    return ocr(image_exp, result, result_size);
}

// allocate memory
const char* _stdcall ocr_file(const char* file_path, int file_size)
{
    auto image_exp = libocr::image(file_path, file_size);
    if (!image_exp) return nullptr;
    auto text = libocr::detect_and_recognize(libocr::ocr_manager::get_instance().get_detector(), libocr::ocr_manager::get_instance().get_recognizer(), image_exp.value());
    if (text.empty()) return nullptr;
    char* buffer = new char[text.size() + 1];
    strcpy(buffer, text.c_str());
    return buffer;
}

const char* _stdcall ocr_image(int image_width, int image_height, const char* image_data, int image_data_size)
{
    auto image_exp = libocr::image(image_width, image_height, image_data, image_data_size);
    if (!image_exp) return nullptr;
    auto text = libocr::detect_and_recognize(libocr::ocr_manager::get_instance().get_detector(), libocr::ocr_manager::get_instance().get_recognizer(), image_exp.value());
    if (text.empty()) return nullptr;
    char* buffer = new char[text.size() + 1];
    strcpy(buffer, text.c_str());
    return buffer;
}

// free memory
void _stdcall free_char(char* p)
{
    // free(p);
    delete p;
}
