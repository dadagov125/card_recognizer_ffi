cmake_minimum_required(VERSION 3.5)

set(CROSS_PLATFORM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../src/CrossPlatform")

add_library(crossplatform STATIC
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeDatum.cpp
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeDatumList.cpp
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeNeuralNetwork.cpp
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeObjectFactory.cpp
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeResult.cpp
        ${CROSS_PLATFORM_DIR}/CaffePredictor/CaffeResultList.cpp
        ${CROSS_PLATFORM_DIR}/CV/canny.cpp
        ${CROSS_PLATFORM_DIR}/CV/hough.cpp
        ${CROSS_PLATFORM_DIR}/CV/warp.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/DateRecognizer.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/EdgesDetector.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/FrameStorage.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/NameRecognizer.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/NumberRecognizer.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/RecognitionCore.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/RecognitionResult.cpp
        ${CROSS_PLATFORM_DIR}/Recognizer/Utils.cpp
        ${CROSS_PLATFORM_DIR}/ServiceContainer.cpp
        ${CROSS_PLATFORM_DIR}/Torch/TorchManager.cpp
        )

find_package(OpenCV REQUIRED
        COMPONENTS opencv_objdetect opencv_imgcodecs opencv_imgproc opencv_ml opencv_core)

set_target_properties(crossplatform PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_STANDARD 11
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
target_compile_options(crossplatform PRIVATE
        -marm -Wno-unused-command-line-argument
        -frtti -fexceptions
        -O3)

target_include_directories(crossplatform
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CROSS_PLATFORM_DIR}
        ${CROSS_PLATFORM_DIR}/CaffePredictor
        ${CROSS_PLATFORM_DIR}/CV
        ${CROSS_PLATFORM_DIR}/Include
        ${CROSS_PLATFORM_DIR}/Include/NeuralNetwork
        ${CROSS_PLATFORM_DIR}/Include/Public
        ${CROSS_PLATFORM_DIR}/Include/Recognizer
        ${CROSS_PLATFORM_DIR}/Include/Torch
        ${CROSS_PLATFORM_DIR}/Recognizer
        ${CROSS_PLATFORM_DIR}/Torch
        ${CROSS_PLATFORM_DIR}/model/include)

if (ANDROID_ABI STREQUAL "armeabi-v7a")
    set_property(TARGET crossplatform APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon")
elseif(ANDROID_ABI MATCHES "x86(_64)?")
    target_compile_options(crossplatform PRIVATE
            $<$<STREQUAL:${ANDROID_ABI},x86>:-msse3>
            -Wno-unknown-attributes
            -Wno-deprecated-declarations)
    target_compile_definitions(crossplatform PRIVATE HAVE_NEON_X86=1)
    target_link_libraries(crossplatform PRIVATE NEON_2_SSE)
endif()

target_link_libraries(crossplatform
        PRIVATE
        eigen
        caffe
        libyuv
        PUBLIC
        ${OpenCV_LIBS}
)
