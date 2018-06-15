//
// Created by alex on 6/14/18.
//

#ifndef MUSICVISUALISER_AUDIOBUFFER_H
#define MUSICVISUALISER_AUDIOBUFFER_H

#include "util.h"
#include <portaudio.h>

class AudioBuffer
{
public:
    BufferData& GetData();

    void Init(int nSamples);
    void Update();
    void Destroy();

private:
    BufferData m_data;
    PaStream *m_paStream;
};


#endif //MUSICVISUALISER_AUDIOBUFFER_H
