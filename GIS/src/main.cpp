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
#include "texture.h"

// Vertices coordinates
GLfloat vertices[] =
    {
        //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // Upper right corner
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
};

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Triforce", NULL, NULL);
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

    Texture texture("res/stone_texture.jpg");
    texture.Bind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        vao.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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