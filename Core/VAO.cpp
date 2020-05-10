#include "vao.h"

vao::vao()
{
    glGenVertexArrays(1, &buffer_id);
    vertex_buffer_objects.reserve(5);
}

vao::~vao()
{
    vertex_buffer_objects.clear();
    glDeleteVertexArrays(1, &buffer_id);
}

void vao::bind() const
{
    glBindVertexArray(buffer_id);
}

void vao::release() const
{
    glBindVertexArray(0);
}

void vao::create_vertex_buffer(const GLenum usage, const std::vector<glm::vec3>& data)
{
    vbo& vertex_buffer_object = vertex_buffer_objects.emplace_back(GL_ARRAY_BUFFER);
    vertex_buffer_object.bind();
    vertex_buffer_object.upload(usage, data);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    vertex_buffer_object.release();
}

void vao::create_normal_buffer(const GLenum usage, const std::vector<glm::vec3>& data)
{
    vbo& vertex_buffer_object = vertex_buffer_objects.emplace_back(GL_ARRAY_BUFFER);
    vertex_buffer_object.bind();
    vertex_buffer_object.upload(usage, data);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    vertex_buffer_object.release();
}

void vao::create_uv_buffer(const GLenum usage, const std::vector<glm::vec2>& data)
{
    vbo& vertex_buffer_object = vertex_buffer_objects.emplace_back(GL_ARRAY_BUFFER);
    vertex_buffer_object.bind();
    vertex_buffer_object.upload(usage, data);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    vertex_buffer_object.release();
}

void vao::create_color_buffer(const GLenum usage, const std::vector<glm::vec3>& data)
{
    vbo& vertex_buffer_object = vertex_buffer_objects.emplace_back(GL_ARRAY_BUFFER);
    vertex_buffer_object.bind();
    vertex_buffer_object.upload(usage, data);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    vertex_buffer_object.release();
}

void vao::create_index_buffer(const GLenum usage, const std::vector<unsigned int>& data)
{
    vbo& vertex_buffer_object = vertex_buffer_objects.emplace_back(GL_ELEMENT_ARRAY_BUFFER);
    vertex_buffer_object.bind();
    vertex_buffer_object.upload(usage, data);
}