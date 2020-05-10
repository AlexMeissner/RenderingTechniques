#pragma once

#include "VBO.h"

class vao
{
public:
    vao();
    ~vao();

    void bind() const;
    void release() const;
    void create_vertex_buffer(const GLenum usage, const std::vector<glm::vec3>& data);
    void create_normal_buffer(const GLenum usage, const std::vector<glm::vec3>& data);
    void create_uv_buffer(const GLenum usage, const std::vector<glm::vec2>& data);
    void create_color_buffer(const GLenum usage, const std::vector<glm::vec3>& data);
    void create_index_buffer(const GLenum usage, const std::vector<unsigned int>& data);

private:
    GLuint buffer_id = 0;
    std::vector<vbo> vertex_buffer_objects;
};