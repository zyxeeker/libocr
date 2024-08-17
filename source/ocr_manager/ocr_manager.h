//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_OCR_MANAGER_H
#define LIBOCR_OCR_MANAGER_H

#include <memory>

namespace libocr
{
    namespace onnx
    {
        class text_detector;
        class text_recognizer;
    } // namespace onnx
    using detector_ptr = std::shared_ptr<onnx::text_detector>;
    using recognizer_ptr = std::shared_ptr<onnx::text_recognizer>;

    class ocr_manager
    {
    private:
        detector_ptr detector;
        recognizer_ptr recognizer;
        bool initialized = false;

        ocr_manager() = default;
    public:
        static ocr_manager& get_instance()
        {
            static ocr_manager instance;
            return instance;
        }
        ~ocr_manager() = default;

    public:
        void init();
    public:
        detector_ptr get_detector() 
        {
            if (!initialized) init();
            return detector;
        }
        recognizer_ptr get_recognizer() 
        {
            if (!initialized) init();
            return recognizer;
        }
    };
} // namespace libocr

#endif // LIBOCR_OCR_MANAGER_H
