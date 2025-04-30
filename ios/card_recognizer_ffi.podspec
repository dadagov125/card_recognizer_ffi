#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint card_recognizer_ffi.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'card_recognizer_ffi'
  s.version          = '0.0.1'
  s.summary          = 'A new Flutter project.'
  s.description      = <<-DESC
                            A new Flutter project.
                          DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.swift_version = '5.0'
  s.dependency 'Flutter'
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*.{c,cpp,cc,h,hpp}'
  s.project_header_files = 'Classes/**/*.{h,hpp}'
  s.vendored_libraries = 'Libraries/libopencv_core.a',
                          'Libraries/libopencv_hal.a',
                          'Libraries/libopencv_imgproc.a',
                          'Libraries/libopencv_objdetect.a'
  s.platform = :ios, '12.0'
  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = {
      'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386',
      'HEADER_SEARCH_PATHS' => '"${PROJECT_DIR}/.."/.symlinks/plugins/card_recognizer_ffi/ios/include/Eigen/ "${PROJECT_DIR}/.."/.symlinks/plugins/card_recognizer_ffi/ios/include/opencv2/ "${PROJECT_DIR}/.."/.symlinks/plugins/card_recognizer_ffi/ios/include/',
      'GCC_PREPROCESSOR_DEFINITIONS' => 'CPU_ONLY USE_EIGEN COMPACT HAVE_PTHREAD',
      'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
      'CLANG_CXX_LIBRARY' => 'libc++'
  }

  s.prepare_command = <<-CMD
                            mkdir -p Classes/CrossPlatform
                            cp -r ../src/CrossPlatform/* Classes/CrossPlatform/
                         CMD

end
