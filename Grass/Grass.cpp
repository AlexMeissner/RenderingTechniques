#include "stdafx.h"
#include "Grass.h"

using namespace glm;

grass::grass(const std::string& window_title)
    :core(window_title)
{
}

bool grass::initialize()
{
    if (!test_shader.load_vertex_shader("W:\\Projects\\Coding\\Super Mario Bros\\SuperMarioBros\\Rendering\\Shader\\Vertex\\TempPass.glsl"))
    {
        return false;
    }
    if (!test_shader.load_fragment_shader("W:\\Projects\\Coding\\Super Mario Bros\\SuperMarioBros\\Rendering\\Shader\\Fragment\\TempPass.glsl"))
    {
        return false;
    }
    watch(test_shader);

    //std::vector<vec3> vertices;
    //std::vector<vec3> colors;
    //std::vector<unsigned int> indices;
    //
    //vao floor;
    //floor.create_vertex_buffer(GL_STATIC_DRAW, vertices);
    //floor.create_color_buffer(GL_STATIC_DRAW, colors);
    //floor.create_index_buffer(GL_STATIC_DRAW, indices);

    return true;
}

void grass::render()
{
}