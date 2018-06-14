//
// Created by alex on 6/14/18.
//

#ifndef MUSICVISUALISER_BASERENDERER_H
#define MUSICVISUALISER_BASERENDERER_H

#include <glad/glad.h>

class BaseRenderer
{
public:
    static unsigned int LoadShader(const char* vertexShader, const char* fragmentShader);
    static unsigned int CreateTexture2D(GLint width, GLint height, GLint internalFormat, GLenum format, GLenum type);
};


#endif //MUSICVISUALISER_BASERENDERER_H
