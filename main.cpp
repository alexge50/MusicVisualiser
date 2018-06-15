#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Renderer.h"
#include "util.h"
#include "OscilloscopeRenderer.h"
#include "AudioBuffer.h"

#include <portaudio.h>

const int SAMPLES_PER_FRAME = 44800;
void SetTestData(BufferData&);

int main()
{
    glfwInit();
    Pa_Initialize();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Music Visualiser", NULL, NULL);
    Renderer renderer;
    GraphRendererStrongPtr graphRenderer;
    BufferData bufferData;
    ScreenDimension windowDimensions, viewDimensions;
    AudioBuffer audioBuffer;

    windowDimensions = viewDimensions = {1920, 1080};

    if(!window)
    {
        printf("Error while creating window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    renderer.Init(windowDimensions, viewDimensions);
    graphRenderer = std::make_shared<OscilloscopeRenderer>();
    graphRenderer->Init(viewDimensions, SAMPLES_PER_FRAME);
    renderer.SetGraphRenderer(graphRenderer);

    audioBuffer.Init(SAMPLES_PER_FRAME);

    while(!glfwWindowShouldClose(window))
    {
        //processing
        audioBuffer.Update();

        //rendering
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        renderer.Render(audioBuffer.GetData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    graphRenderer->Destroy();
    renderer.Destroy();
    audioBuffer.Destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    Pa_Terminate();
    return 0;
}

int timer = 5;

void SetTestData(BufferData &d)
{
    if(timer == 5)
    {
        d.clear();
        for (int i = 0; i < SAMPLES_PER_FRAME; i++)
            //d.push_back(sinf(static_cast<float>(i) / static_cast<float>(SAMPLES_PER_FRAME / 8)));
            d.push_back((rand() % 100) / 99.f - 0.5f);
        timer = 0;
    }
    timer ++;
}
