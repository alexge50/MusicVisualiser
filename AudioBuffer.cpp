//
// Created by alex on 6/14/18.
//

#include "AudioBuffer.h"
#include <string>
#include <portaudio.h>

BufferData &AudioBuffer::GetData()
{
    return m_data;
}

void AudioBuffer::Init(int nSamples)
{
    m_data.insert(m_data.end(), nSamples, 0);
    PaDeviceIndex deviceId = -1;

    int nDevices = Pa_GetDeviceCount();

    const PaDeviceInfo *deviceInfo;
    for (int i = 0; i < nDevices; i++)
    {
        deviceInfo = Pa_GetDeviceInfo(i);

        if(std::string("pulse") == deviceInfo->name)
            deviceId = i;

        printf("%s: %s (%d ins %d outs)\n", Pa_GetHostApiInfo(deviceInfo->hostApi)->name, deviceInfo->name, deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
    }

    if(deviceId == -1)
    {
        printf("device not found\n");
        return;
    }

    PaStreamParameters inputStreamParameters{deviceId, 1, paFloat32, 0.2, NULL};
    PaError err = Pa_OpenStream(&m_paStream, &inputStreamParameters, NULL, 44800, 100, paNoFlag, NULL, NULL);

    /*PaError err = Pa_OpenDefaultStream( &m_paStream,
                                1,
                                0,
                                paFloat32,
                                44100,
                                256,
                                NULL,
                                NULL );*/

    printf("%d %p\n", err, m_paStream);
    if(err != paNoError)
    {
        printf("%s\n", Pa_GetErrorText(err));
        return;
    }
    printf("errorcode: %d\n", Pa_IsStreamActive(m_paStream));
    printf("error: %s\n", Pa_GetErrorText(Pa_IsStreamActive(m_paStream)));
    Pa_StartStream(m_paStream);

}

void AudioBuffer::Update()
{
    long nFrames = Pa_GetStreamReadAvailable(m_paStream);

    //printf("%d\n", nFrames);
    if(nFrames < 0)
    {
        printf("error\n");
        return;
    }
    printf("%d\n", nFrames);

    m_data.insert(m_data.end(), static_cast<unsigned long>(nFrames), 0);
    int err = Pa_ReadStream(m_paStream, &m_data[m_data.size() - nFrames], static_cast<unsigned long>(nFrames));
    m_data.erase(m_data.begin(), m_data.begin() + nFrames);

    if(err < 0)
        printf("%s\n", Pa_GetErrorText(err));
}

void AudioBuffer::Destroy()
{
    Pa_CloseStream(&m_paStream);
}

