#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Renderer.h"
#include "util.h"
#include "OscilloscopeRenderer.h"

const int SAMPLES_PER_FRAME = 1024;
void SetTestData(BufferData&);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Music Visualiser", NULL, NULL);
    Renderer renderer;
    GraphRendererStrongPtr graphRenderer;
    BufferData bufferData;
    ScreenDimension windowDimensions, viewDimensions;

    windowDimensions = viewDimensions = {1920, 1080};

    if(!window)
    {
        printf("Error while creating window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    renderer.Init(windowDimensions, viewDimensions);
    graphRenderer = std::make_shared<OscilloscopeRenderer>();
    graphRenderer->Init(viewDimensions, SAMPLES_PER_FRAME);
    renderer.SetGraphRenderer(graphRenderer);
    while(!glfwWindowShouldClose(window))
    {
        //processing
        SetTestData(bufferData);

        //rendering
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        renderer.Render(bufferData);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    graphRenderer->Destroy();
    renderer.Destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void SetTestData(BufferData &d)
{
    d.clear();
    for (int i = 0; i < SAMPLES_PER_FRAME; i++)
        d.push_back(sinf(static_cast<float>(i) / static_cast<float>(SAMPLES_PER_FRAME / 8)));
}
