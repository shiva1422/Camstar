//
// Created by shiva1422 on 5/29/2021.
//

#ifndef DJMAGIC_FILEMANAGER_H
#define DJMAGIC_FILEMANAGER_H
#include "android/asset_manager.h"
#include "../Commons.h"
#include "stb_image.h"
class Texture;
class FileManager{
public:
    static stbi_io_callbacks  assetIOCallbacks;
    static AAsset * getAsset(const char* assetLoc);
    static bool getShaderSource(const char *fileName,char **toSource);

    //aasset io callbacks
    //fill data from asset with size bytes and return acutually read size;
    static int32 readAsset(void *asset,char *data,int size);

    //skip the next n byte or unget the last -n bytes if negative
    static void skip(void *asset,int n);

    //return nonZero if we are at end of file/data
    static int eof(void *asset);
};

#endif //DJMAGIC_FILEMANAGER_H
