#include <glad/glad.h>
#include <iostream>

#include "core/Window.hpp"
#include "renderer/Triangle.hpp"

/**
 * Entry point for the application. 
 * Manages the OpenGL context lifecycle and the main render loop.
 */
int main() {
    try {
        // Initialize the window abstraction and the underlying GLFW/Platform context.
        // The ctor handles window creation and making the GL context current.
        Window window(800, 600, "Hello Renderer");

        // GLAD acts as the loader for OpenGL function pointers. 
        // This must be called after the context is created but before any GL calls.
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD: OpenGL function pointers could not be resolved.");
        }

        // Encapsulates VAO, VBO, and Shader Program state for a simple primitive.
        // Resource allocation (GPU side) happens during construction.
        Triangle triangle;

        /* --- Main Render Loop --- */
        while (!window.shouldClose()) {
            // Set the clear color state and execute the clear command on the color buffer.
            // Using a dark slate gray (0.1, 0.1, 0.15) for a professional look.
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Bind the shader program, bind the VAO, and issue the draw call (glDrawArrays/Elements).
            triangle.draw();

            // Swap the front and back buffers to display the rendered frame.
            window.swap();
            
            // Process OS window events (input, resizing, etc.) to keep the application responsive.
            window.poll();
        }
    }
    catch (const std::exception& e) {
        // Standardized error logging for critical failures during init or runtime.
        std::cerr << "Critical Error: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
