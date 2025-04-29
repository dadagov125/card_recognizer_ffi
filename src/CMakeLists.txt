# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)
project(card_recognizer_ffi_library VERSION 0.0.1 LANGUAGES C CXX)

set(ANDROID_CPP_DIR "${CMAKE_SOURCE_DIR}/../android/src/main/cpp")
set(OpenCV_DIR "${ANDROID_CPP_DIR}/opencv2/sdk/native/jni")


add_subdirectory(${ANDROID_CPP_DIR}/armneon2x86sse armneon2x86sse)
add_subdirectory(${ANDROID_CPP_DIR}/eigen eigen)
add_subdirectory(${ANDROID_CPP_DIR}/protobuf protobuf)
add_subdirectory(${ANDROID_CPP_DIR}/caffe caffe)
add_subdirectory(${ANDROID_CPP_DIR}/libyuv libyuv)
add_subdirectory(${ANDROID_CPP_DIR}/crossplatform crossplatform)


add_library(card_recognizer_ffi SHARED
  "card_recognizer_ffi.c"
)

set_target_properties(card_recognizer_ffi PROPERTIES
  PUBLIC_HEADER card_recognizer_ffi.h
  OUTPUT_NAME "card_recognizer_ffi"
)

target_compile_definitions(card_recognizer_ffi PUBLIC DART_SHARED_LIB)

if (ANDROID)
  # Support Android 15 16k page size
  target_link_options(card_recognizer_ffi PRIVATE "-Wl,-z,max-page-size=16384")
endif()

target_link_libraries(card_recognizer_ffi PRIVATE
    libyuv
    log
    z
    -lc++_shared
)