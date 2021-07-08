//
// Created by pspr1 on 7/7/2021.
//

#ifndef CAMSTAR_VULKANCONTEXT_H
#define CAMSTAR_VULKANCONTEXT_H

#include <android_native_app_glue.h>
#include "vulkan_wrapper.h"
#define CALL_VK(func)                                                 \
  if (VK_SUCCESS != (func)) {                                         \
    __android_log_print(ANDROID_LOG_ERROR, "Tutorial ",               \
                        "Vulkan error. File[%s], line[%d]", __FILE__, \
                        __LINE__);                                    \
    assert(false);                                                    \
  }
class VulkanContext {
private:
    bool createInstance();
    bool createSurface();
    bool getGpuAndCheckCapabilities();
    bool findGFXFamilyQueueAndCreateLogicalDevice();

public:
    VkInstance vkInstance;
    VkPhysicalDevice vkGpu;
    VkDevice vkDevice = VK_NULL_HANDLE;
    VkSurfaceKHR vkSurface;

    bool bInit = false;


    bool initialize(android_app *app);
    void destroy();

};


#endif //CAMSTAR_VULKANCONTEXT_H
