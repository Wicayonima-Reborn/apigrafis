#include <glad/glad.h>
#include <iostream>

#include "core/Window.hpp"
#include "renderer/Triangle.hpp"

int main() {
    try {
        Window window(800, 600, "Hello Renderer");

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("GLAD init failed");

        Triangle triangle;

        while (!window.shouldClose()) {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangle.draw();

            window.swap();
            window.poll();
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }
}