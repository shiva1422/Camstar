//
// Created by pspr1 on 5/27/2021.
//

#ifndef DHWANI_AUDIOSTUDIO_COMMONS_H
#define DHWANI_AUDIOSTUDIO_COMMONS_H
#include "android/log.h"
#define Loge(...)((void)__android_log_print(ANDROID_LOG_ERROR,__VA_ARGS__))
#define Logi(...)((void)__android_log_print(ANDROID_LOG_INFO,__VA_ARGS__))
#define kforceinline inline __attribute__((always_inline))

enum status{STATUS_OK,STATUS_KO,STATUS_EXTRA,STATUS_KO_FATAL};
typedef int32_t int32;
typedef uint8_t uint8;


class DisplayMetrics{
public:
    int32 screenWidth=0,screenHeight=0,densityDpi=0,deviceStableDensity=0;
    float density=0.0f,scaledDensity=0.0f,xdpi=0.0f,ydpi=0.0f;
    void print();
    void onScreenRotation();
};


#endif //DHWANI_AUDIOSTUDIO_COMMONS_H
