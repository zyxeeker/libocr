add_library(${BUILD_TARGET_NAME} SHARED)
add_library(${BUILD_TARGET_NAME}::ocr ALIAS ${BUILD_TARGET_NAME})

target_compile_options(${BUILD_TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
set_target_properties(${BUILD_TARGET_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_options(${BUILD_TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/MP>)

# rc文件
set(version_rc_file "${CMAKE_BINARY_DIR}/resource_version.rc")
configure_file("${CMAKE_SOURCE_DIR}/resource/resource_version.rc.in" "${version_rc_file}")
set(model_rc_file "${CMAKE_SOURCE_DIR}/resource/resource_model.rc")
list(APPEND resource_files "${version_rc_file}" "${model_rc_file}")

# cpp文件
file(GLOB_RECURSE source_files "*.cpp" "*.h" "*.hpp" "*.c" "*.cc" "*.cxx" "*.hxx")

source_group("include" FILES ${include_dir}/libocr/libocr.h)
source_group("resource" FILES ${resource_files})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${source_files})

list(APPEND source_files ${resource_files})

target_include_directories(${BUILD_TARGET_NAME} PUBLIC ${include_dir})
target_compile_definitions(${BUILD_TARGET_NAME} PRIVATE LIBOCR_EXPORTS)
target_compile_definitions(${BUILD_TARGET_NAME} PRIVATE LIBOCR_NAME="${BUILD_TARGET_NAME}.dll")

target_sources(${BUILD_TARGET_NAME} PUBLIC ${include_dir}/libocr/libocr.h PRIVATE ${source_files})

target_link_libraries(${BUILD_TARGET_NAME} PRIVATE opencv_core opencv_imgcodecs opencv_imgproc)
target_include_directories(${BUILD_TARGET_NAME} PRIVATE ${onnxruntime_INCLUDE_DIR})
target_link_libraries(${BUILD_TARGET_NAME} PRIVATE ${onnxruntime_LIBRARYS})

# 编译完成后，install到install目录
install(TARGETS ${BUILD_TARGET_NAME})
install(FILES ${include_dir}/libocr/libocr.h DESTINATION include/libocr)
