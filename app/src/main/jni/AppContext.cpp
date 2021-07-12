//
// Created by pspr1 on 5/27/2021.
//

#include <assert.h>
#include "AppContext.h"
#include "android_native_app_glue.h"
#include "AndroidEvents.h"
#include "JavaCall.h"
#include "Graphics/Shader.h"
#include "UI/View.h"
#define AppLogE(...)((void)__android_log_print(ANDROID_LOG_ERROR,"APPCONTEXT:",__VA_ARGS__))
#define AppLogI(...)((void)__android_log_print(ANDROID_LOG_INFO,"APPCONTEXT:",__VA_ARGS__))
android_app* AppContext::app= nullptr;

AppContext::AppContext(android_app *papp)
{

    app = papp;
    app->onAppCmd=AndroidEvents::onAppCmd;
    app->onInputEvent=AndroidEvents::onInputEvent;
    app->userData = this;

    assert(JavaCall::getDisplayMetrics(&displayMetrics) == STATUS_OK);
    displayMetrics.print();
    //
    int32_t eventId,events,fdesc;
    android_poll_source* source;
    do//just to init GL so that glfuncts dont fail after this;
    {
        while((eventId=ALooper_pollAll(0,&fdesc,&events,(void **) &source))>=0)
        {
            if(source!=NULL)
            {
                source->process(app,source);
            }
        }

    }while(!bWindowInit);

}

void AppContext::setContentView(View *view)
{
    contentView = view;
}
void AppContext::onScreenRotation()
{
    displayMetrics.onScreenRotation();
    if(contentView)
    {
        contentView->onScreenRotation();
    }
}


//CallBacks
void AppContext::onWindowInit()
{
    bWindowInit=true;
    if (bAppFirstOpen)
    {
        /* assert(Graphics::init_display(this) == STATUS_OK);
         bAppFirstOpen = false;
         bWindowInit = true;
         bGraphicsInit = true;
         return;*/
        // bGraphicsInit=vulkanContext.initialize(app);
        if(!bGraphicsInit)
        {
            bGraphicsInit = glContext.init();
            GLuint shaderId = Shader::createShaderProgram("shaders/ui/vertexShader.glsl","shaders/ui/fragmentShader.glsl");
            glUseProgram(shaderId);
        }

        bAppFirstOpen = false;
    }
    else
    {
        glContext.onAppReopen();
    }
    JavaCall::hideSystemUI();
}
void AppContext::onWindowResized()
{
    AppLogI("WindowResized");
}
void AppContext::onWindowRedrawNeeded()
{
    AppLogI("Redraw Needed");
}
void AppContext::onWindowTermination()
{
    AppLogI("WIndow Terminating");
}
void AppContext::onContentRectChanged()
{
    AppLogI("Content Rect Changed");
}
void AppContext::onStart()
{
    AppLogI("STart");
}
void AppContext::onResume()
{
    AppLogI("Resume");
}
void AppContext::onPause()
{
    AppLogI("Pause");
}
void AppContext::onStop()
{
    AppLogI("Stop");
}
void AppContext::onDestroy()
{
    AppLogI("Destroy");
}
void AppContext::onFocusGained()
{
    AppLogI("Focus Gained");
}
void AppContext::onFocusLost()
{
    AppLogI("Focus Lost");
}
void AppContext::onConfigChanged()
{
    AppLogI("Config changed");
    if(AConfiguration_getOrientation(app->config) == ACONFIGURATION_ORIENTATION_PORT)
        AppLogI("Portrait");
    else
        AppLogI("Landscape");
    AppLogI("%d and orientation %d",AConfiguration_getScreenHeightDp(app->config),AConfiguration_getOrientation(app->config));
   // glViewport(0,0,displayMetrics.screenHeight,displayMetrics.screenWidth);
}
void AppContext::onSaveState()
{
    AppLogI("Save State");
}
void AppContext::onLowMemory()
{
    AppLogI("Low memory");
}
void AppContext::onInputChange()
{
    AppLogI("Input Change");
}


