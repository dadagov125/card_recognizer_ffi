cmake_minimum_required(VERSION 3.5)



add_library(caffe STATIC
        ${CAFFE_VENDOR_DIR}/blob.cpp
        ${CAFFE_VENDOR_DIR}/common.cpp
        ${CAFFE_VENDOR_DIR}/layer_factory.cpp
        ${CAFFE_VENDOR_DIR}/layers/base_conv_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/base_data_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/bnll_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/concat_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/conv_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/eltwise_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/flatten_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/im2col_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/inner_product_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/loss_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/lrn_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/memory_data_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/neuron_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/pooling_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/power_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/relu_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/sigmoid_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/softmax_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/softmax_loss_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/split_layer.cpp
        ${CAFFE_VENDOR_DIR}/layers/tanh_layer.cpp
        ${CAFFE_VENDOR_DIR}/net.cpp
        ${CAFFE_VENDOR_DIR}/proto/caffe.pb.cc
        ${CAFFE_VENDOR_DIR}/syncedmem.cpp
        ${CAFFE_VENDOR_DIR}/util/im2col.cpp
        ${CAFFE_VENDOR_DIR}/util/insert_splits.cpp
        ${CAFFE_VENDOR_DIR}/util/io.cpp
        ${CAFFE_VENDOR_DIR}/util/math_functions.cpp
        ${CAFFE_VENDOR_DIR}/util/upgrade_proto.cpp)

target_include_directories(caffe
        PRIVATE ${CAFFE_INCLUDE_DIR}
        PUBLIC include)

target_compile_definitions(caffe PUBLIC CPU_ONLY USE_EIGEN)
target_compile_options(caffe PRIVATE
        -marm -Wno-unused-command-line-argument
        -frtti -fexceptions
        -O3)
set_target_properties(caffe PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set_property(TARGET caffe APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon")
endif()

#target_link_libraries(caffe
 #       PUBLIC protobuf
 #       PRIVATE eigen)
