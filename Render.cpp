//
// Created by alex on 6/13/18.
//

#include "Renderer.h"

static const GLfloat quadVertexData[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

static const char* vertexShader = "#version 330 core\n"
                                  "layout (location = 0) in vec2 pos;"
                                  "layout (location = 1) in vec2 tex;"
                                  "out vec2 uv;"
                                  "void main()"
                                  "{"
                                  "gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);"
                                  "uv = tex;"
                                  "}";
static const char* fragmentShader = "#version 330 core\n"
                                    "out vec4 fragmentColor;"
                                    "in vec2 uv;"
                                    "uniform sampler2D screenTexture;"
                                    "void main()"
                                    "{"
                                    "fragmentColor = texture(screenTexture, uv);"
                                    "}\n";

void Renderer::SetGraphRenderer(GraphRendererStrongPtr pGraphRenderer)
{
    m_pGraphRenderer = pGraphRenderer;
}

void Renderer::Init(ScreenDimension windowDimensions, ScreenDimension viewDimensions)
{
    m_windowDimension = windowDimensions;

    glGenFramebuffers(1, &m_fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

    glGenTextures(1, &m_renderTextureId);
    glBindTexture(GL_TEXTURE_2D, m_renderTextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewDimensions.width, viewDimensions.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTextureId, 0);

    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Error frame buffer generation\n");

    glGenVertexArrays(1, &m_quadVaoId);
    glBindVertexArray(m_quadVaoId);

    glGenBuffers(1, &m_quadVboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertexData), quadVertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*shader*/
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

    m_shaderId = glCreateProgram();
    glAttachShader(m_shaderId, vertexShaderId);
    glAttachShader(m_shaderId, fragmentShaderId);
    glLinkProgram(m_shaderId);

    glUniform1i(glGetUniformLocation(m_shaderId, "screenTexture"), 0);
}

void Renderer::Render(BufferData &data)
{
    m_pGraphRenderer->Render(data, m_fboId);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_windowDimension.width, m_windowDimension.height);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_shaderId);
    glBindTexture(GL_TEXTURE_2D, m_renderTextureId);
    glActiveTexture(0);
    glBindVertexArray(m_quadVaoId);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_BLEND);
}

void Renderer::Destroy()
{
    glDeleteTextures(1, &m_renderTextureId);
    glDeleteFramebuffers(1, &m_fboId);
}
