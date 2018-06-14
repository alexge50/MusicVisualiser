//
// Created by alex on 6/13/18.
//

#include "Renderer.h"

void Renderer::SetGraphRenderer(GraphRendererStrongPtr pGraphRenderer)
{
    m_pGraphRenderer = pGraphRenderer;
}

void Renderer::Init()
{

}

void Renderer::Render(BufferData &data)
{
    m_pGraphRenderer->Render(data, 0);
}

void Renderer::Destroy()
{

}
