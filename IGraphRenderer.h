//
// Created by alex on 6/13/18.
//

#ifndef MUSICVISUALISER_IGRAPHRENDERER_H
#define MUSICVISUALISER_IGRAPHRENDERER_H

#include <memory>
#include "util.h"

class IGraphRenderer;
typedef std::shared_ptr<IGraphRenderer> GraphRendererStrongPtr;

//renders a graph from data to buffer
class IGraphRenderer
{
public:
    virtual void Init(int nSamples) = 0;
    virtual void Render(BufferData &data, Id framebufferId) = 0;
    virtual void Destroy() = 0;
};


#endif //MUSICVISUALISER_IGRAPHRENDERER_H
