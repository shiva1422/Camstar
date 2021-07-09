//
// Created by pspr1 on 5/27/2021.
//

#ifndef DHWANI_AUDIOSTUDIO_CONTEXT_H
#define DHWANI_AUDIOSTUDIO_CONTEXT_H

#include <EGL/egl.h>
#include <android_native_app_glue.h>
#include "Commons.h"
#include "Graphics/GLContext.h"
#include "Graphics/VulkanContext.h"

#if __ANDROID_API__ >= 24
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif

class DisplayMetrics;
class View;
class AppContext {
protected:
    static android_app *app;

public:
    AppContext(android_app *papp);
    DisplayMetrics displayMetrics;
    GLContext glContext;
    VulkanContext vulkanContext;
    GLuint uiProgram;
    bool bWindowInit=false,bGraphicsInit=false,bAppFirstOpen=true;
    int screenOrientation  = ACONFIGURATION_ORIENTATION;


    View *contentView = nullptr;

    AppContext();

    //Activity call backs;Protected?????

    //onCreate is the main method;
    virtual void onStart();
    virtual void onResume();
    virtual void onPause();
    virtual void onStop();
    virtual void onDestroy();
    void onWindowInit();
    void onWindowResized();
    void onWindowRedrawNeeded();
    void onWindowTermination();

    void onContentRectChanged();
    virtual void onLowMemory();
    virtual void onFocusLost();
    virtual void onFocusGained();
    virtual void onConfigChanged();
    virtual void onSaveState();
    virtual void onInputChange();


    void setContentView(View *view);
    void onScreenRotation();
    static android_app* getApp()
    {
        return app;
    }
};


#endif //DHWANI_AUDIOSTUDIO_CONTEXT_H
