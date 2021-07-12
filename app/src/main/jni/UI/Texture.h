//
// Created by pspr1 on 7/9/2021.
//

#ifndef CAMSTAR_TEXTURE_H
#define CAMSTAR_TEXTURE_H

#include "../Graphics/GLContext.h"
class Texture {
public:
    GLuint tex = 0,buf = 0;
    int32 imageWidth = 0,imageHeight = 0,numChannels = 0;
    void createFromAsset(const char *assetLoc);
};


#endif //CAMSTAR_TEXTURE_H
