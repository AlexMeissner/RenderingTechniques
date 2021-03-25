#include "stdafx.h"
#include "HeightMap.h"

using namespace glm;

height_map::height_map(const std::string& window_title)
    :core(window_title)
{
}

bool height_map::initialize()
{
    if (!floor_shader.load_vertex_shader("W:\\Projects\\Coding\\RenderingTechniques\\HeightMap\\Vertex.glsl"))
    {
        return false;
    }
    if (!floor_shader.load_fragment_shader("W:\\Projects\\Coding\\RenderingTechniques\\HeightMap\\Fragment.glsl"))
    {
        return false;
    }
    watch(floor_shader);

    const std::vector<vec3> vertices = { vec3(-floor_size, 0.0f, -floor_size), vec3(floor_size, 0.0f, -floor_size), vec3(-floor_size, 0.0f, floor_size), vec3(floor_size, 0.0f, floor_size) };
    const std::vector<vec3> colors = { vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f) };
    const std::vector<unsigned int> indices = { 0, 1, 2, 1, 2, 3 };

    floor.bind();
    floor.create_vertex_buffer(GL_STATIC_DRAW, vertices);
    floor.create_color_buffer(GL_STATIC_DRAW, colors);
    floor.create_index_buffer(GL_STATIC_DRAW, indices);
    floor.release();

    return true;
}

void height_map::render()
{
    floor_shader.bind();
    floor_shader.set_uniform(floor_shader.get_uniform_location("view_projection"), 1, &camera.get_view_projection()[0][0]);

    floor.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    floor.release();
    
    floor_shader.release();
}