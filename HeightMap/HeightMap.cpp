#include "stdafx.h"
#include "HeightMap.h"

using namespace glm;

height_map::height_map(const std::string& window_title)
    : core(window_title)
    , height_map_texture("W:\\Projects\\Coding\\RenderingTechniques\\HeightMap\\texture.png")
{
}

bool height_map::initialize()
{
    if (!height_map_shader.load_vertex_shader("W:\\Projects\\Coding\\RenderingTechniques\\HeightMap\\Vertex.glsl"))
    {
        return false;
    }
    if (!height_map_shader.load_fragment_shader("W:\\Projects\\Coding\\RenderingTechniques\\HeightMap\\Fragment.glsl"))
    {
        return false;
    }
    watch(height_map_shader);

    create_mesh();

    return true;
}

void height_map::render()
{
    height_map_shader.bind();
    height_map_shader.set_uniform(height_map_shader.get_uniform_location("view_projection"), 1, &camera.get_view_projection()[0][0]);

    floor.bind();
    height_map_texture.bind(GL_TEXTURE0);
    glDrawElements(GL_TRIANGLES, floor_size * floor_size * 2 * 3, GL_UNSIGNED_INT, (void*)0);
    height_map_texture.release(GL_TEXTURE0);
    floor.release();

    height_map_shader.release();
}

void height_map::create_mesh()
{
    const size_t size = floor_size + 1;

    std::vector<vec3> vertices(size * size);
    std::vector<unsigned int> indices;
    indices.reserve(floor_size * floor_size * 2 * 3);

    for (size_t z = 0; z <= floor_size; ++z)
    {
        for (size_t x = 0; x <= floor_size; ++x)
        {
            const size_t index = z * size + x;
            vertices[index].x = static_cast<float>(x);
            vertices[index].y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            //vertices[index].y = 0.0f;
            vertices[index].z = static_cast<float>(z);
        }
    }

    for (size_t z = 0; z < floor_size; ++z)
    {
        for (size_t x = 0; x < floor_size; ++x)
        {
            const unsigned int index_top_left = z * size + x;
            const unsigned int index_top_right = z * size + x + 1;
            const unsigned int index_bottom_left = (z + 1) * size + x;
            const unsigned int index_bottom_right = (z + 1) * size + x + 1;

            indices.push_back(index_top_left);
            indices.push_back(index_bottom_left);
            indices.push_back(index_bottom_right);

            indices.push_back(index_top_left);
            indices.push_back(index_bottom_right);
            indices.push_back(index_top_right);
        }
    }

    floor.bind();
    floor.create_vertex_buffer(GL_STATIC_DRAW, vertices);
    floor.create_index_buffer(GL_STATIC_DRAW, indices);
    floor.release();
}