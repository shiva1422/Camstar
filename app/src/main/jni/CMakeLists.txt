cmake_minimum_required(VERSION 3.18.1)
add_library(glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(glue PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue)
set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
find_library(log-lib log)

##Oboe




add_library(main SHARED main.cpp AndroidEvents.cpp AppContext.cpp JavaCall.cpp Commons.cpp FileManager/FileManager.cpp)
target_include_directories(main PUBLIC ${FFMPEG_DIR}/include ${OBOE}/include ${VULKAN_DIR}/src/include/vulkan ${VULKAN_DIR}/src/common)

#graphics UI
#vulkan
set(VULKAN_DIR ${ANDROID_NDK}/sources/third_party/vulkan)
add_definitions(-DVULKAN_HPP_TYPESAFE_CONVERSION)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -std=c++11 \
                     -DVK_USE_PLATFORM_ANDROID_KHR")

add_library(graphics STATIC Graphics/GLContext.cpp ${VULKAN_DIR}/src/common/vulkan_wrapper.cpp Graphics/VulkanContext.cpp Graphics/Shader.cpp)
target_include_directories(graphics PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue ${VULKAN_DIR}/src/include/vulkan ${VULKAN_DIR}/src/common)


add_library(ui STATIC UI/View.cpp UI/ClickListener.cpp UI/ViewGroup.cpp)
target_include_directories(ui PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue )





target_link_libraries(main graphics ui  android  glue jnigraphics GLESv3 EGL ${log-lib})
