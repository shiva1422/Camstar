//
// Created by pspr1 on 7/9/2021.
//

#ifndef CAMSTAR_IMAGEVIEW_H
#define CAMSTAR_IMAGEVIEW_H

#include "View.h"
#include "Texture.h"
class ImageView : public View {
protected:
public:
    ImageView();
    ImageView(float startX,float startY,float width,float height);
    virtual void setTexture(const char* assetLoc) = 0;

};


#endif //CAMSTAR_IMAGEVIEW_H
