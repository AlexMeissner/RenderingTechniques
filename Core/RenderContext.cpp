#include "RenderContext.h"
#include "print.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <glfw3.h>

namespace
{
    void window_resize(GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

render_context::~render_context()
{
    glfwTerminate();
}

bool render_context::create(const std::string& window_title)
{
    if (!glfwInit())
    {
        print::critical << "GLFW initialization failed.";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (window = glfwCreateWindow(1024, 800, window_title.c_str(), nullptr, nullptr))
    {
        glfwSetWindowPos(window, 2400, 100);
        glfwMakeContextCurrent(window);
        glfwSetWindowSizeCallback(window, window_resize);
        glfwSwapInterval(0);
    }
    else
    {
        print::critical << "Window creation failed.";
        return false;
    }

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.4f, 0.7f, 0.4f, 1.0f);

    return true;
}

bool render_context::should_terminate() const
{
    return glfwWindowShouldClose(window);
}

float render_context::get_aspect_ratio() const
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return static_cast<float>(width) / height;
}

void render_context::begin_frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_context::end_frame() const
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}