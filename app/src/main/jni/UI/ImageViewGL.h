//
// Created by pspr1 on 7/9/2021.
//

#ifndef CAMSTAR_IMAGEVIEWGL_H
#define CAMSTAR_IMAGEVIEWGL_H

#include "ImageView.h"
#include "Texture.h"
class ImageViewGL : public ImageView {
protected:
    Texture texture;
public:
    ImageViewGL(const char * assetLoc);
    ImageViewGL(const char *assetLoc,float startX,float startY,float width,float height);
    virtual void setTexture(const char *assetLoc) override;
    virtual void draw() override;


};


#endif //CAMSTAR_IMAGEVIEWGL_H
