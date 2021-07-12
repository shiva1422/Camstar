//
// Created by pspr1 on 7/9/2021.
//

#include "Texture.h"
#include "FileManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void Texture::createFromAsset(const char *assetLoc)
{
    //check all texture params are set apptly using any image loader;
    AAsset *asset = FileManager::getAsset(assetLoc);
    if(!asset)
    {
        Loge("TextureCreate","could not getAsset check asset path ");
        //set texture params to 0?
        return;
    }
    //#if using stb
    //control num components and create textures based on format;
    stbi_info_from_callbacks(&FileManager::assetIOCallbacks,asset,&imageWidth,&imageHeight,&numChannels);
    AAsset_seek(asset,0,SEEK_SET);
    stbi_uc *pixels = stbi_load_from_callbacks(&FileManager::assetIOCallbacks, asset, &imageWidth, &imageHeight, &numChannels, 4);
    if(pixels == NULL)
    {
        Loge("Texture:","Image Decode error");
        //goto fail;
    }

    //#endif

    //if previous image dims same as present need not recreate buf and tex
    if(glIsBuffer(buf))
    {
        glDeleteBuffers(1,&buf);
        buf = 0; //not needed?test same for texture
    }
    glGenBuffers(1,&buf);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buf);
    glBufferData(GL_PIXEL_UNPACK_BUFFER,imageWidth*imageHeight*4,pixels,GL_STATIC_COPY);
    if(GLContext::getGlError("texture")==GL_OUT_OF_MEMORY)
    {
        Loge("Texture","couldnot create texture buffer - out of memory");
    }
    if(glIsTexture(tex))
    {
        glDeleteTextures(1,&tex);
    }
    glGenTextures(1,&tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, imageWidth,imageHeight);//wiki commonmistakes//use glTexImage for mutable textures.//glpixelstore for way to read(pack)and write(unpack) image using this fun.
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,imageWidth,imageHeight,GL_RGBA,GL_UNSIGNED_BYTE,0);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    if(GLContext::getGlError("texture set") == GL_NO_ERROR)
    Loge("SetTexture","done");

    Logi("Image dims","width %d and height %d and numChannels %d",imageWidth,imageHeight,numChannels);
    stbi_image_free(pixels);
    AAsset_close(asset);//do in call back for stb_io
}