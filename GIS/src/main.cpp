#include <iostream>
#include <glad/glad.h>
#include "glad.c"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

// Vertices for a triforce (= positions of corners)
GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};

// Indices storing the order of the corners in a specific order (rendering is counter clock wise by default)
GLuint indices[] =
    {
        5, 0, 3,
        3, 2, 4,
        5, 4, 1};

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Triforce", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current (needs to be put before gladLoad) */
    glfwMakeContextCurrent(window);

    // Load glad to configure OPENGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    Shader shaderProgram("/home/rino/Desktop/Uni/GIS/src/default.vert", "/home/rino/Desktop/Uni/GIS/src/default.frag");
    // Create VAO
    VAO vao;
    vao.Bind();

    // Create VBO
    VBO vbo(vertices, sizeof(vertices));

    // Create EBO
    EBO ebo(indices, sizeof(indices));

    // Link VBO to VAO
    vao.LinkVBO(vbo, 0);

    // Unbind all
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        vao.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Check for qutting with key stroke
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        /* Poll for and process events */
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}