//
// Created by alex on 6/13/18.
//

#ifndef MUSICVISUALISER_RENDERER_H
#define MUSICVISUALISER_RENDERER_H

#include <glad/glad.h>
#include "util.h"
#include "IGraphRenderer.h"
#include "BaseRenderer.h"

//renders scene to buffer
class Renderer: public BaseRenderer
{
public:
    void SetGraphRenderer(GraphRendererStrongPtr pGraphRenderer);

    void Init(ScreenDimension windowDimensions, ScreenDimension viewDimensions);
    void Render(BufferData &data);
    void Destroy();

private:
    GraphRendererStrongPtr m_pGraphRenderer;
    unsigned int m_fboId;
    unsigned int m_renderTextureId;
    unsigned int m_quadVboId;
    unsigned int m_quadVaoId;
    unsigned int m_shaderId;

    ScreenDimension m_windowDimension;
};

#endif //MUSICVISUALISER_RENDERER_H
