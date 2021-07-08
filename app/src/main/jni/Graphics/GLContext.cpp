//
// Created by pspr1 on 7/6/2021.
//

#include "GLContext.h"
#include "../AppContext.h"
#include "initializer_list"
#define GraphicsLog(...)((void)__android_log_print(ANDROID_LOG_ERROR,"GRAPHICS LOG:",__VA_ARGS__))
bool GLContext::init()
{

    GraphicsLog("initializing opengl");
    const EGLint attribs[]={ EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,EGL_BLUE_SIZE, 8,EGL_GREEN_SIZE, 8,EGL_RED_SIZE, 8, EGL_SURFACE_TYPE, EGL_WINDOW_BIT,EGL_NONE};
    const EGLint context_attribs[]={EGL_CONTEXT_CLIENT_VERSION,3,EGL_NONE};
    const EGLint surfaceAttribs[]={EGL_WIDTH,ANativeWindow_getWidth(AppContext::getApp()->window),EGL_HEIGHT,ANativeWindow_getHeight(AppContext::getApp()->window),EGL_NONE};
    EGLint format;
    EGLint numConfigs;
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(eglDisplay==EGL_NO_DISPLAY) {
        GraphicsLog("no display");
        return false;
    }

    if( !eglInitialize(eglDisplay, nullptr, nullptr))//can pass variable to get the result opengl versions
    {        GraphicsLog("egl initialize failed");

        return false;
    }
    if(!eglChooseConfig(eglDisplay, attribs, &config,1, &numConfigs)||numConfigs<=0)
    {//////chose the first config
        GraphicsLog("eglChooseConfig failed ");
        return false;

    }
    //   std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    //  assert(supportedConfigs);
    // eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
    //  assert(numConfigs);
    // auto i = 0;
    GraphicsLog("numConfigs %d",numConfigs);
    /*  for (; i < numConfigs; i++) {
           auto& cfg = supportedConfigs[i];
           EGLint r, g, b, d,a;
           if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r)   &&
               eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
               eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b)  &&
               eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
               r == 8 && g == 8 && b == 8) {//&&d=0 removed
               config = supportedConfigs[i];
               break;
           }
       }*/
    //  if (i == numConfigs) {
    //   GraphicsLog("no configuration match");
    //   config = supportedConfigs[0];
    // }


    if (config == nullptr) {
        GraphicsLog("Unable to initialize EGLConfig");
        return false;
    }
    if(! eglGetConfigAttrib(eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format))
    {
        GraphicsLog("egl getConfig attrib failed");
        return false;
    }
    eglContext = eglCreateContext(eglDisplay, config, nullptr, context_attribs);//context attribs mandatory for creating required context
    if(eglContext==EGL_NO_CONTEXT){
        GraphicsLog("context creation failed");
        return false;
    }

    // create surfaace and make current
    ANativeWindow_setBuffersGeometry(AppContext::getApp()->window,0,0,format);
    eglSurface = eglCreateWindowSurface(eglDisplay, config, AppContext::getApp()->window, nullptr);////this is for visual surface
    //surface=eglCreatePbufferSurface(appContext->eglDisplay,config,surfaceAttribs);/////this is for off screen rendering
    if(eglSurface == EGL_NO_SURFACE)
    {
        GraphicsLog("window surface creation failed");
        return false;
    }
    if (eglMakeCurrent(eglDisplay,eglSurface,eglSurface,eglContext ) == EGL_FALSE) {
        GraphicsLog("Unable to eglMakeCurrent");
        return false;
    }
    eglQuerySurface(eglDisplay,eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &height);
    auto opengl_info ={GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
    for (auto name : opengl_info) {
        auto info = glGetString(name);
        GraphicsLog("OpenGL Info: %s", info);
    }
    //  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    // glEnable(GL_CULL_FACE);
    //  glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    GraphicsLog("Opengl initialized successfully");
    return true;

}
bool GLContext::onAppReopen()
{
    EGLint format;
    const EGLint surfaceAttribs[]={EGL_WIDTH,ANativeWindow_getWidth(AppContext::getApp()->window),EGL_HEIGHT,ANativeWindow_getHeight(AppContext::getApp()->window),EGL_NONE};
    if(! eglGetConfigAttrib(eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format)){
        GraphicsLog("egl getConfig attrib failed");
        return false;
    }
    // create surfaace and make current
    ANativeWindow_setBuffersGeometry(AppContext::getApp()->window,0,0,format);
    eglSurface = eglCreateWindowSurface(eglDisplay, config,AppContext::getApp()->window, nullptr);////this is for visual surface
    //surface=eglCreatePbufferSurface(appContext->eglDisplay,config,surfaceAttribs);/////this is for off screen rendering
    if( eglSurface == EGL_NO_SURFACE)
    {
        GraphicsLog("window surface creation failed");
        return false;
    }
    if (eglMakeCurrent(eglDisplay,eglSurface,eglSurface,eglContext ) == EGL_FALSE) {
        GraphicsLog("Unable to eglMakeCurrent");
        return false;
    }
    GraphicsLog("successfully initialization on app reopeng");
    return true;
}