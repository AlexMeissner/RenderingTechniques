#include "vbo.h"

using namespace glm;

vbo::vbo(const GLenum type)
    : type(type)
{
    glGenBuffers(1, &buffer_id);
}

vbo::~vbo()
{
    glDeleteBuffers(1, &buffer_id);
}

void vbo::bind() const
{
    glBindBuffer(type, buffer_id);
}

void vbo::release() const
{
    glBindBuffer(type, 0);
}

void vbo::upload(const GLenum usage, const std::vector<float>& data) const
{
    glBufferData(type, sizeof(float) * data.size(), &data[0], usage);
}

void vbo::upload(const GLenum usage, const std::vector<vec2>& data) const
{
    glBufferData(type, sizeof(vec2) * data.size(), &data[0], usage);
}

void vbo::upload(const GLenum usage, const std::vector<vec3>& data) const
{
    glBufferData(type, sizeof(vec3) * data.size(), &data[0], usage);
}

void vbo::upload(const GLenum usage, const std::vector<unsigned int>& data) const
{
    glBufferData(type, sizeof(unsigned int) * data.size(), &data[0], usage);
}

void vbo::upload(const GLenum usage, const std::vector<vec4>& data) const
{
    glBufferData(type, sizeof(vec4) * data.size(), &data[0], usage);
}

void vbo::upload(const GLenum usage, const std::vector<ivec4>& data) const
{
    glBufferData(type, sizeof(ivec4) * data.size(), &data[0], usage);
}