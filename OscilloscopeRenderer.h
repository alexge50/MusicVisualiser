//
// Created by alex on 6/14/18.
//

#ifndef MUSICVISUALISER_OSCILLOSCOPERENDERER_H
#define MUSICVISUALISER_OSCILLOSCOPERENDERER_H

#include <glad/glad.h>
#include "IGraphRenderer.h"
#include "BaseRenderer.h"

class OscilloscopeRenderer: public IGraphRenderer, public BaseRenderer
{
public:
    void Init(ScreenDimension viewDimension, int nSamples) override;
    void Render(BufferData &data, Id framebufferId) override;
    void Destroy() override;

private:
    int m_nSamples;
    unsigned int m_vboId, m_vaoId;
    unsigned int m_shaderId;
    ScreenDimension m_viewDimension;

    struct Vertex
    {
        float x, y, z;
    };
    std::vector<Vertex> m_vertexData;
};


#endif //MUSICVISUALISER_OSCILLOSCOPERENDERER_H
