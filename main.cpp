#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "util.h"

int main()
{
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(640, 480, "Music Visualiser", NULL, NULL);

    if(!window)
    {
        printf("Error while creating window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}