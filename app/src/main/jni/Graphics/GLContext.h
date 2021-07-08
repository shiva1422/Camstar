//
// Created by pspr1 on 7/6/2021.
//

#ifndef CAMSTAR_GLCONTEXT_H
#define CAMSTAR_GLCONTEXT_H

#include "EGL/egl.h"
#include "../Commons.h"

#if __ANDROID_API__ >= 24
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif

class GLContext{
public:
    int32 width = 0,height = 0;//surface dims
    EGLConfig config ;
    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLSurface eglSurface = EGL_NO_SURFACE;
    EGLContext eglContext = EGL_NO_CONTEXT;
    bool init();//initDisplay
    bool onAppReopen();
    void destroyGL();
    GLenum printGlError(const char *tag);

};


#endif //CAMSTAR_GLCONTEXT_H
