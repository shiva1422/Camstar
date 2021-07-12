//
// Created by pspr1 on 7/9/2021.
//

#include "ImageViewGL.h"
#include "FileManager.h"
ImageViewGL::ImageViewGL(const char *assetLoc)
{
    setTexture(assetLoc);
}
ImageViewGL::ImageViewGL(const char *assetLoc, float startX, float startY, float width,float height) : ImageView(startX,startY,width,height)
{
    setTexture(assetLoc);
}
void ImageViewGL::setTexture(const char *assetLoc)
{
    texture.createFromAsset(assetLoc);
}
void ImageViewGL::draw()
{
    //View::draw();//backGround
    // glEnable(GL_BLEND);//check needed wholly(keep globlally enable ) correspond with disable.
    // glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glUniform2f(0,scaleX,scaleY);
    glUniform2f(2,translateX,translateY);

    glBindBuffer(GL_ARRAY_BUFFER,vertexBufId);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void *)0);

    glBindBuffer(GL_ARRAY_BUFFER,uvBufId);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void *)0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture.tex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufId);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,(void *)0);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);

   // glDisable(GL_BLEND);
}