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


    m_renderTextureId = CreateTexture2D(viewDimensions.width, viewDimensions.height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTextureId, 0);

    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Error frame buffer generation\n");

    InitQuadVao();

    m_shaderId = LoadShader(vertexShader, fragmentShader);
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

    /* Render Background */

    /* Render Graphs */
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

void Renderer::InitQuadVao()
{
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
}
