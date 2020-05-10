#pragma once

#include "CommonHeaders.h"

class vbo
{
public:
    vbo(const GLenum type);
    ~vbo();

    void bind() const;
    void release() const;
    void upload(const GLenum usage, const std::vector<float>& data) const;
    void upload(const GLenum usage, const std::vector<unsigned int>& data) const;
    void upload(const GLenum usage, const std::vector<glm::vec2>& data) const;
    void upload(const GLenum usage, const std::vector<glm::vec3>& data) const;
    void upload(const GLenum usage, const std::vector<glm::vec4>& data) const;
    void upload(const GLenum usage, const std::vector<glm::ivec4>& data) const;

private:
    GLuint buffer_id = 0;
    const GLenum type;
};