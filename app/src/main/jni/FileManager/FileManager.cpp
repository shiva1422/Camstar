//
// Created by shiva1422 on 5/29/2021.
//

#include <android/asset_manager.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <malloc.h>
#include "../FileManager.h"
#include "../AppContext.h"
#include "android/log.h"
#include "stb_image.h"

AAsset * FileManager::getAsset(const char *assetLoc)
{

    AAssetManager *assetManager = AppContext::getApp()->activity->assetManager;
    AAsset *asset =AAssetManager_open(assetManager,assetLoc,AASSET_MODE_RANDOM);

   // AAsset_close(asset);//CLose after done
    return asset;

}
bool FileManager::getShaderSource(const char *fileName, char **toSource)
{
    android_app *app=AppContext::getApp();
    int32_t  shaderSize=0;
    AAssetManager *assetManager=app->activity->assetManager;
    AAsset *asset=AAssetManager_open(assetManager,fileName,AASSET_MODE_UNKNOWN);
    if(asset)
    {
        shaderSize=AAsset_getLength(asset);
        *toSource=(char *)malloc(shaderSize+1);
        int noOfBytesRead=AAsset_read(asset,*toSource,shaderSize);
        AAsset_close(asset);
        if(shaderSize==noOfBytesRead)
        {
            (*toSource)[shaderSize]='\0';
            Logi("file:shader","the shader %s size in is %d bytes is read Succesfully",fileName,shaderSize);
            //   GE("the shader Source is \n %s",this->source);
            return true;
        }
            return false;
    }
    Loge("fileManger Shader::getSournce","shader source could not be loaded check location %s",fileName);
    return false;
}