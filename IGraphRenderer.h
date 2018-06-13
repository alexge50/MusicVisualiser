//
// Created by alex on 6/13/18.
//

#ifndef MUSICVISUALISER_IGRAPHRENDERER_H
#define MUSICVISUALISER_IGRAPHRENDERER_H

#include "util.h"

class IGraphRenderer;
typedef std::shared_ptr<IGraphRenderer> GraphRendererStrongPtr;

//renders a graph from data to buffer
class IGraphRenderer
{
public:
    virtual void Render(BufferData &data, Id framebufferId) = 0;
};


#endif //MUSICVISUALISER_IGRAPHRENDERER_H
