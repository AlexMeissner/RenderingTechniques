#pragma once

#include "CommonHeaders.h"

class texture
{
public:
    texture(const fs::path& file_path);
    ~texture();

    void bind(const GLenum texture_unit) const;
    void release(const GLenum texture_unit) const;

private:
    GLuint texture_id = 0;
    GLenum type = GL_TEXTURE_2D;
};