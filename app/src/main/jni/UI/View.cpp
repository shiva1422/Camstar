//
// Created by pspr1 on 5/28/2021.
//

#include <string.h>
#include "View.h"

GLuint View::vertexBufId=0;
GLuint View::indexBufId=0;
GLuint View::uvBufId=0;
float View::vertices[]={-1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f};
DisplayMetrics* View::disMet =nullptr;
/*
 * Check centreX , centre Y without bounds
 */
View::View() {}

View::View(float startX, float startY, float width, float height)
{

    setBounds(startX,startY,width,height);
}
void View::setBounds(float startX, float startY, float width, float height)
{
    this->startX=startX,this->startY=startY,this->width=width,this->height=height;
    scaleX = width/(disMet->screenWidth);
    scaleY = height/(disMet->screenHeight);
    translateX = ( (startX+width/2.0)- disMet->screenWidth/2.0 )* 2.0/ disMet->screenWidth;
    translateY = ( -(startY+height/2.0) + disMet->screenHeight/2.0 ) *2.0 / disMet->screenHeight;
}
void View::setBackgroundColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
void View ::draw()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glUniform2f(0,scaleX,scaleY);
    glUniform2f(2,translateX,translateY);

    glBindBuffer(GL_ARRAY_BUFFER,vertexBufId);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void *)0);//make one array for vertices and color and make throgh stride

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufId);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,(void *)0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void View::fitToBounds(float bStartX, float bStartY, float bWidth, float bHeight)
{
    float newWidth,newHeight;
    //float aspectRatioImage=width/height;
    float xRation,yRation;
    xRation=width/bWidth;
    yRation=height/bHeight;
    if(xRation>1 || yRation>1)
    {
        float finalRatio;
        if(xRation>=yRation)
            finalRatio=xRation;
        else
            finalRatio=yRation;

        newHeight=height/finalRatio;
        newWidth=width/finalRatio;

    }
    else
    {
        newWidth=width;
        newHeight=height;
    }
    float  xdiff=bWidth-newWidth;
    float  ydiff=bHeight-newHeight;
    //  {UILogE("negative difference xdiff %f and ydiff %f",xdiff,ydiff);}
    setBounds(bStartX+(xdiff/2.0),bStartY+(ydiff/2.0),newWidth,newHeight);
}
void View::fitToBoundsWithCentre(float centreX, float centreY, float bWidth, float bHeight)
{
    fitToBounds(centreX - bWidth/2.0,centreY - bHeight/2.0,bWidth,bHeight);
}
void View::onScreenRotation()
{
    //Display Metric should also be rotated x<->y
    Logi("view screenRot","%f %f %f %f",startX,startY,width,height);
    setBounds(startY,startX,width,height);
}
bool View::onDispatchTouch(float touchX, float touchY, int pointerId, TouchAction touchAction)
{
    //later based on translate ,scale ,rotation.
    if(touchX>=startX && touchX <= (startX + width) && touchY >= startY && touchY <= (startY + height) )// macro
    {
        Logi("Dispathc Touch :","i'm touched ");
        if(touchListener)
        {
           return touchListener->onTouch(touchX,touchY,pointerId,touchAction,this);
        }

    }
    else //remove
    Logi("Dispathc Touch :","i'm not touched");
    return false;
}
void View::initializeUI()
{
    //improve anything fails return statusKo and assert;

    GLuint bufferIds[3];
    glGenBuffers(3,bufferIds);
    View::indexBufId=bufferIds[0], View::uvBufId=bufferIds[1], View::vertexBufId=bufferIds[2];
    //for(int i=0;i<3;i++)UILogE("%d, vertexBufId %d",bufferIds[i],vertexBufId);

    glBindBuffer(GL_ARRAY_BUFFER,View::vertexBufId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*8,(void *)0,GL_STATIC_DRAW);
    float *verts=(float *)glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(float)*8,GL_MAP_WRITE_BIT);
    if(verts)
    {
        Logi("initialize ui","vets");
        memcpy(verts,View::vertices,8*sizeof(float));

    }
    else
        Logi("initialize ui","vertex upload failed");
    glUnmapBuffer(GL_ARRAY_BUFFER);//return GL_false if error


    glBindBuffer(GL_ARRAY_BUFFER,View::uvBufId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*8,(void *)0,GL_STATIC_DRAW);
    float *textCoords=(float *)glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(float)*8,GL_MAP_WRITE_BIT);
    if(textCoords)
    {

        //0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f
        textCoords[0]=0.0f,textCoords[1]=0.0f,textCoords[2]=1.0f,textCoords[3]=0.0f,textCoords[4]=1.0f,textCoords[5]=1.0f,textCoords[6]=0.0f,textCoords[7]=1.0f;

    }
    else
    {////lazy draw on
        ///uploading vertices everydrawcall
        Logi("failed","UIINITIalize()-error uploading textCoods");
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);//return GL_false if error
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,View::indexBufId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short )*6, (void *)0, GL_STATIC_DRAW);
    GLushort *indices=(GLushort *)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(short )*6,GL_MAP_WRITE_BIT);
    if(indices)
    {
        indices[0]=0, indices[1]=1, indices[2]=2, indices[3]=2, indices[4]=3, indices[5]=0;

    }
    else
    {////lazy draw on
        ///uploading vertices everydrawcall
        Loge("failed","UIINITIALIZe()-error uploading indices");
    }
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
