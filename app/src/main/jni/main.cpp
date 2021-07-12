//
// Created by pspr1 on 6/3/2020.
//
#include <assert.h>
#include "android/log.h"
#include "Commons.h"
#include "AndroidEvents.h"
#include "JavaCall.h"
#include "AppContext.h"
#include "UI/View.h"
#include "ImageViewGL.h"
#include "Time.h"

void initialSetup(android_app *app);
void android_main(struct android_app* app)
{

    AppContext appContext(app);
    //continue with appContext main;
    initialSetup(app);
    int32_t eventId,events,fdesc;
    android_poll_source* source;
    TimeDiff frameTime;
    View temp(appContext.displayMetrics.screenWidth*10/100,0,100,100);
    temp.setBackgroundColor(1.0,1.0,0.0,1.0);
    appContext.setContentView(&temp);
    ImageViewGL image("icons/photo.jpg",10,0,appContext.displayMetrics.screenWidth,appContext.displayMetrics.screenHeight);
    image.fitToBoundsWithCentre(appContext.displayMetrics.screenWidth/2.0,appContext.displayMetrics.screenHeight/2.0,100,100);
   do
    {
        while((eventId=ALooper_pollAll(0,&fdesc,&events,(void **) &source))>=0)
        {
            if (source != NULL)
            {
                source->process(app, source);

            }
            break;

        }

        frameTime.start();
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        temp.draw();
        image.draw();
        eglSwapBuffers(appContext.glContext.eglDisplay, appContext.glContext.eglSurface);
        frameTime.end();

    }while(app->destroyRequested==0);
   //dont exit until destroyed requested as only this thread exits not the Activity(apps main thread).  if want to exit call ANativeActivity_finish(or APP_CMD_DESTROY)
}
void initialSetup(android_app *app)//move to context::init;
{




    View::disMet=&((AppContext *)(app->userData))->displayMetrics;
    View::initializeUI();
}

