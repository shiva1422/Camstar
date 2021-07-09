//
// Created by pspr1 on 5/27/2021.
//


#include <stdint.h>
#include <android_native_app_glue.h>
#include <assert.h>
#include "Commons.h"
#include "AndroidEvents.h"
#include "AppContext.h"
#include "JavaCall.h"
#include "UI/View.h"
int32 pointerIndex,pointerId,pointerCount;
float touchX ,touchY;
int32_t AndroidEvents::onInputEvent(android_app* papp, AInputEvent* event)
{
    View *contentView = ((AppContext *)papp->userData)->contentView;
    Loge("INPUT EVENT", "got");
    if(!contentView)
        return 0;
    if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)//check eventSource accordinglt
    {
        pointerIndex =(AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        pointerId=AMotionEvent_getPointerId(event,pointerIndex);
        // TouchLog("the pointer index for all is %d and the pointer id is %d",pointerIndex,pointerId);
        touchX = AMotionEvent_getX(event, pointerIndex);
        touchY = AMotionEvent_getY(event, pointerIndex);
        Logi("touch coordinate","%f and %f",touchX,touchY);
      //  Logi("OnInputEvent :","touch coordinates are x - %f and y -%f",touchX , touchY);
        switch (AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK)
        {
            case AMOTION_EVENT_ACTION_DOWN:
            {
                return contentView->onDispatchTouch(touchX,touchY,pointerId,ACTION_DOWN);
            }
            break;

        }





    }

    return 1;//change based on dispatching
}
 void AndroidEvents::onAppCmd(android_app* app, int32_t cmd)
{
    AppContext *context = static_cast<AppContext *>(app->userData);//NULL?never?
    switch(cmd)
    {
        /*java Lauch(onCreate(ANativeActivity_OnCreate->android_main) ->Created(Onstart)->Started follows below in the same ordered
         * better only render(incluing audio) only after all resumed,focus gained and windowCreated.
         * */
        case APP_CMD_START:
            context->onStart();
            break;
        case APP_CMD_RESUME:
            //app in foreground
            context->onResume();
            break;
        case APP_CMD_PAUSE:
            context->onPause();
            break;
        case APP_CMD_STOP:
            context->onStop();
            break;
        case APP_CMD_DESTROY:
            context->onDestroy();
            //destroy opengl;
            break;
        case APP_CMD_LOW_MEMORY:
            context->onLowMemory();
            break;
        case APP_CMD_WINDOW_RESIZED:
            context->onWindowResized();
            break;
        case APP_CMD_SAVE_STATE:
            // the OS asked us to save the state of the app
            context->onSaveState();
            break;
        case APP_CMD_INIT_WINDOW:
            {
            context->onWindowInit();

            }
            break;
        case APP_CMD_TERM_WINDOW:
        {
            context->onWindowTermination();
        }
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            context->onWindowRedrawNeeded();
            break;
        case APP_CMD_INPUT_CHANGED:
            context->onInputChange();
            break;

        case APP_CMD_CONTENT_RECT_CHANGED:
            context->onContentRectChanged();
            break;
        case APP_CMD_CONFIG_CHANGED:
        {
           context->onConfigChanged();
        }break;

        case APP_CMD_LOST_FOCUS:
            context->onFocusLost();
            //drawggin notification drawer sitching away to another app,(can happen without being paused)
            // if the app lost focus, avoid unnecessary processing
            //(like monitoring the accelerometer)inputs etc//(in games should be paused as control is lost).
            break;
        case APP_CMD_GAINED_FOCUS:
            context->onFocusGained();
            // bring back a certain functionality, like monitoring the accelerometer
            break;
        default:
            Loge("UnknownCommand","onAppCMD");
    }
    Logi("command handling","done");

}

