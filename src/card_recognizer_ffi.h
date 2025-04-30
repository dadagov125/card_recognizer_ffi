//card_recognizer_ffi.h
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#if _WIN32
#define FFI_PLUGIN_EXPORT __declspec(dllexport)
#else
#define FFI_PLUGIN_EXPORT
#endif



FFI_PLUGIN_EXPORT int sum(int a, int b);

FFI_PLUGIN_EXPORT int sum_long_running(int a, int b);

#ifdef __cplusplus
extern "C" {
#endif

FFI_PLUGIN_EXPORT unsigned long long nativeInit();

#ifdef __cplusplus
}
#endif