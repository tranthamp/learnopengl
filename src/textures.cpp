#include <iostream>
#include "Common.h"
#include "Shader.h"

//=============================================================================
int main() {
    GLFWwindow* window = initGraphics(1000, 1000);
    if (window == nullptr) {
        std::cout << "ERROR: COULD NOT CREATE WINDOW" << std::endl;
        return -1;
    }

    GLfloat vertices[] = {
         // Positions, XYZ     // Colors, RGB       // Texture Coords, ST
         0.9f,  0.9f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // Top Right
         0.9f, -0.9f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Bottom Right
        -0.9f, -0.9f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
        -0.9f,  0.9f, 0.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture Coordinate Attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth = 1024;
    int rawWidth = textureWidth * 3;
    unsigned char* image = (unsigned char*)malloc(rawWidth * textureWidth);
    for (int row = 0; row < textureWidth; row++) {
        for (int col = 0; col < rawWidth; col += 3) {
            unsigned char* pixel = image + ((row * rawWidth) + col);
            pixel[0] = pixel[1] = pixel[2] = col * row / 100;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Compile the shader program
    Shader ourShader("textures.vert", "textures.frag");

    float r = 0.2f, g = 0.2f, b = 0.2f, a = 1.0f;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Render
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Use the shader
        ourShader.Use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}
