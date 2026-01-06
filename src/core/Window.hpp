#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    void poll();
    void swap();

private:
    GLFWwindow* window;
};