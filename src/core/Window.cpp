#include "Window.hpp"
#include <stdexcept>

/**
 * Constructor: Initializes the graphics library and creates the platform-specific window.
 * We enforce the Core Profile here to ensure modern programmable pipeline usage.
 */
Window::Window(int width, int height, const char* title) {
    // Initialize GLFW library. Must be called before any other GLFW functions.
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW abstraction layer.");

    // Set precision for the OpenGL Context. We're targeting Version 3.3 Core.
    // Core Profile removes deprecated "fixed-function" legacy features.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Platform-specific window and implicit OpenGL context creation.
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate(); // Clean up if windowing fails to prevent ghost processes.
        throw std::runtime_error("Failed to create GLFW window context.");
    }

    // Bind the OpenGL context of the specified window to the current thread.
    // All subsequent GL calls will affect this context.
    glfwMakeContextCurrent(window);
}

/**
 * Destructor: Ensures graceful teardown of resources.
 * In a professional engine, this prevents memory leaks and dangling context handles.
 */
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate(); // Finalize the library and release OS-level resources.
}

/**
 * Returns the state of the window's close flag.
 */
bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

/**
 * Dispatches window and input events (keyboard, mouse, resize) to the application.
 */
void Window::poll() {
    glfwPollEvents();
}

/**
 * Implements Double Buffering. 
 * Swaps the back buffer (where we just drew) with the front buffer (what the user sees).
 */
void Window::swap() {
    glfwSwapBuffers(window);
}
