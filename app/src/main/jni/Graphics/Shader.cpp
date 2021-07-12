//
// Created by pspr1 on 7/7/2021.
//

#include "Shader.h"
#include "../FileManager/FileManager.h"
#define GraphicsLog(...)((void)__android_log_print(ANDROID_LOG_ERROR,"GRAPHICS LOG:",__VA_ARGS__))
GLuint Shader::createShaderProgram(const char *vertexShader, const char *fragmentShader)
{
    Shader VertexShader,FragmentShader;
    VertexShader.loadAndCompileShader(vertexShader,GL_VERTEX_SHADER);
    FragmentShader.loadAndCompileShader(fragmentShader,GL_FRAGMENT_SHADER);
    VertexShader.deleteSource();
    FragmentShader.deleteSource();///should the shaderPrograms alo be deleted after linking?
    return linkShaders(VertexShader.id,FragmentShader.id);//Indicate which shader faile if failed.

}
GLuint Shader::loadAndCompileShader(const char *fileName,GLenum shaderType)
{

    if(FileManager::getShaderSource(fileName,&this->source))
    {
        id = compile(shaderType);//// id =0 error;

    }
    return id;

}
GLuint Shader::createComputeProgram( const char *computeShaderFile)
{
    Shader computeShader;
    GLuint program=glCreateProgram();
    computeShader.loadAndCompileShader(computeShaderFile,GL_COMPUTE_SHADER);
    if(computeShader.id && program)
    {

        glAttachShader(program,computeShader.id);
        glLinkProgram(program);
        GLint linkStatus=GL_FALSE;
        glGetProgramiv(program,GL_LINK_STATUS,&linkStatus);
        if(linkStatus!=GL_TRUE)
        {
            GLint buflen=0;
            glGetProgramiv(program,GL_INFO_LOG_LENGTH,&buflen);
            if(buflen)
            {
                char* buf=(char *)malloc(buflen);
                if(buf)
                {
                    glGetProgramInfoLog(program,buflen,NULL,buf);
                    GraphicsLog("could not link the  Compute program reason : %s",buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program=0;
        }
        else
        {
            GraphicsLog("ComputeShader Linked Succesfully");
            return program;

        }
    }
    else
    {
        GraphicsLog("Couldnot create compute progam");
    }
    return program;
}
GLuint  Shader::linkShaders(GLuint vertexShaderId, GLuint fragmentShaderId)
{
    if(!vertexShaderId||!fragmentShaderId)
    {
        return 0;//failure
    }
    GLuint program=glCreateProgram();
    if(program)
    {
        glAttachShader(program,vertexShaderId);
        glAttachShader(program,fragmentShaderId);
        glLinkProgram(program);
        GLint linkStatus=GL_FALSE;
        glGetProgramiv(program,GL_LINK_STATUS,&linkStatus);
        if(linkStatus!=GL_TRUE)
        {
            GLint buflen=0;
            glGetProgramiv(program,GL_INFO_LOG_LENGTH,&buflen);
            if(buflen)
            {
                char* buf=(char *)malloc(buflen);
                if(buf)
                {
                    glGetProgramInfoLog(program,buflen,NULL,buf);
                    GraphicsLog("could not link the  program reason : %s",buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program=0;
        }
        else
            GraphicsLog("shader Linked Succesfully");
    }

    return program;
}

GLuint Shader::compile(GLenum shaderType)
{
    GLuint shader=glCreateShader(shaderType);

    if(shader)
    {    GraphicsLog("createing shader program");

        glShaderSource(shader,1,&source,NULL);
        glCompileShader(shader);
        //status of compilation
        GLint compiled=0;

        glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
        if(!compiled)
        {

            GraphicsLog("shader not compiled getting failure info .....");
            GLint  infolen=0;
            glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infolen);
            if(infolen)
            {
                char* buf=(char *)malloc(infolen);
                if(buf)
                {
                    glGetShaderInfoLog(shader,infolen,NULL,buf);
                    GraphicsLog("the reason for failue of shader compilation %s",buf);
                    free(buf);
                }
                glDeleteShader(shader);
            }
        }
        else GraphicsLog("shader Compile Succesfully");
    }
    return shader;

}
void Shader::deleteSource()
{
    if(source)
    {
        free(source);
        source=NULL;
    }
}
