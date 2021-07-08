//
// Created by pspr1 on 7/7/2021.
//

#ifndef CAMSTAR_SHADER_H
#define CAMSTAR_SHADER_H

#include <cstdlib>
#include "GLContext.h"
class Shader {
private:
    char *source=NULL;
public:
    GLuint id=0;
    GLuint compile(GLenum shaderType);
    GLuint loadAndCompileShader(const char *fileName,GLenum shaderType);
    void deleteSource();
    static GLuint createShaderProgram(const char *vertexShader,const char *fragmentShader);
    static GLuint linkShaders(GLuint vertexShaderId,GLuint fragmentShaderId); ////// if return 0 => error;
    static GLuint createComputeProgram(const char *computeShaderFile);
};


#endif //CAMSTAR_SHADER_H
