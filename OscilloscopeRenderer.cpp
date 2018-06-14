//
// Created by alex on 6/14/18.
//

#include "OscilloscopeRenderer.h"

static const char* vertexShader = "#version 330 core\n"
                                  "layout (location = 0) in vec3 pos;"
                                  "void main()"
                                  "{"
                                  "gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
                                  "}";
static const char* fragmentShader = "#version 330 core\n"
                                    "layout(location = 0) out vec4 fragmentColor;"
                                    "void main()"
                                    "{"
                                    "fragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);"
                                    "}";

void OscilloscopeRenderer::Init(ScreenDimension viewDimension, int nSamples)
{
    m_viewDimension = viewDimension;
    m_nSamples = nSamples;

    for (int i = 0; i < nSamples; i++)
        m_vertexData.push_back({(2./(nSamples - 1) * static_cast<float>(i) - 1.f), 0., 0});

    glGenVertexArrays(1, &m_vaoId);
    glGenBuffers(1, &m_vboId);

    glBindVertexArray(m_vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(OscilloscopeRenderer::Vertex) * m_nSamples, &m_vertexData[0], GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OscilloscopeRenderer::Vertex), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*shader creation*/ //TODO: Move in GraphRendererBase
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

}

void OscilloscopeRenderer::Render(BufferData &data, Id framebufferId)
{
    //convert data to points
    for(int i = 0; i < m_nSamples; i++)
        m_vertexData[i].y = data[i];

    //set buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(OscilloscopeRenderer::Vertex) * m_nSamples, &m_vertexData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //render pass
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
    //glViewport(0, 0, m_viewDimension.width, m_viewDimension.height);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderId);
    glBindVertexArray(m_vaoId);
    glLineWidth(10);
    glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(m_vertexData.size()));
    glBindVertexArray(0);
    glUseProgram(0);
}

void OscilloscopeRenderer::Destroy()
{
    glDeleteBuffers(1, &m_vboId);
    glDeleteVertexArrays(1, &m_vaoId);
    glDeleteProgram(m_shaderId);
}
