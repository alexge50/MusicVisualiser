//
// Created by alex on 6/13/18.
//

#ifndef MUSICVISUALISER_RENDERER_H
#define MUSICVISUALISER_RENDERER_H

#include "util.h"
#include "IGraphRenderer.h"

//renders scene to buffer
class Renderer
{
public:
    void SetGraphRenderer(GraphRendererStrongPtr pGraphRenderer);

    void Render(BufferData &data);

private:
    GraphRendererStrongPtr m_pGraphRenderer;
};


#endif //MUSICVISUALISER_RENDERER_H
