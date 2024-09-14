#include "VAO.h"
#include <glad/glad.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO vbo, GLuint layout)
{
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}
