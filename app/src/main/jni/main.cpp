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
        eglSwapBuffers(appContext.glContext.eglDisplay, appContext.glContext.eglSurface);
        frameTime.end();

    }while(app->destroyRequested==0);
}
void initialSetup(android_app *app)//move to context::init;
{




    View::disMet=&((AppContext *)(app->userData))->displayMetrics;
    View::initializeUI();
}

