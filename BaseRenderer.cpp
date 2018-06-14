//
// Created by alex on 6/14/18.
//

#include <cstdio>
#include "BaseRenderer.h"

unsigned int BaseRenderer::LoadShader(const char *vertexShader, const char *fragmentShader)
{
    unsigned int shaderId;
    int  success;
    char infoLog[512];

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }


    unsigned int fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    shaderId = glCreateProgram();
    glAttachShader(shaderId, vertexShaderId);
    glAttachShader(shaderId, fragmentShaderId);
    glLinkProgram(shaderId);

    return shaderId;
}

unsigned int BaseRenderer::CreateTexture2D(GLint width, GLint height, GLint internalFormat, GLenum format, GLenum type)
{
    unsigned int renderTextureId;
    glGenTextures(1, &renderTextureId);
    glBindTexture(GL_TEXTURE_2D, renderTextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return renderTextureId;
}
