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
       bGraphicsInit=vulkanContext.initialize(app);
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
