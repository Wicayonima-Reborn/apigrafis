#include "Window.hpp"
#include <stdexcept>

Window::Window(int width, int height, const char* title) {
    if (!glfwInit())
        throw std::runtime_error("GLFW init failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
        throw std::runtime_error("Window creation failed");

    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::poll() {
    glfwPollEvents();
}

void Window::swap() {
    glfwSwapBuffers(window);
}