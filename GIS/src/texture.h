#pragma once

#include <string>
#include <glad/glad.h>

class Texture
{
private:
    unsigned int m_RenderId;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BitsPerPixel;

public:
    Texture(const std::string &path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};