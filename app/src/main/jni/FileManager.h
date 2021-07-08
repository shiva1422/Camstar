//
// Created by shiva1422 on 5/29/2021.
//

#ifndef DJMAGIC_FILEMANAGER_H
#define DJMAGIC_FILEMANAGER_H
#include "android/asset_manager.h"
class FileManager{
public:
    static AAsset * getAsset(const char* assetLoc);
    static bool getShaderSource(const char *fileName,char **toSource);
};

#endif //DJMAGIC_FILEMANAGER_H
