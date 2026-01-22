#include "Triangle.hpp"
#include <glad/glad.h>

/**
 * Constructor: Sets up the GPU resources for a basic 2D primitive.
 * We're establishing the link between raw CPU data and the GPU's Vertex Fetch stage.
 */
Triangle::Triangle() {
    // Vertex data defined in Normalized Device Coordinates (NDC) space [-1.0, 1.0].
    float vertices[] = {
         0.0f,  0.5f, 0.0f, // Top vertex
        -0.5f, -0.5f, 0.0f, // Bottom-left vertex
         0.5f, -0.5f, 0.0f  // Bottom-right vertex
    };

    unsigned int VBO; // Vertex Buffer Object (the raw memory on the GPU)
    
    // Generate handles for the Vertex Array Object (VAO) and the Vertex Buffer Object (VBO).
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO first. It will "record" the VBO binding and the attribute pointer configuration.
    glBindVertexArray(VAO);

    // Bind and upload the CPU-side data to the GPU's high-speed memory.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define how OpenGL should interpret the vertex data.
    // Attribute 0: position, 3 floats per vertex, non-normalized, stride is 3 * float size.
    glVertexAttribPointer(
        0,                  // Attribute index (corresponds to 'layout (location = 0)' in shader)
        3,                  // Component count (X, Y, Z)
        GL_FLOAT,           // Data type
        GL_FALSE,           // Normalize fixed-point data?
        3 * sizeof(float),  // Stride: offset to the next vertex
        (void*)0            // Offset of the first component
    );
    glEnableVertexAttribArray(0);

    // Technically, we can unbind the VBO here because it's already registered to the VAO.
    // Note: In a real-world engine, we would store the VBO handle to delete it later in the destructor.
}

/**
 * RAII Cleanup: Ensuring we don't leave orphaned handles in GPU memory.
 */
Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    // Engineering Note: You should also delete the VBO handle here to prevent memory leaks.
}

/**
 * Encapsulates the draw command.
 * By binding the VAO, we restore all the state we configured in the constructor.
 */
void Triangle::draw() {
    glBindVertexArray(VAO);
    // Issue the primitive assembly command to the pipeline.
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
