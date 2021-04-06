#pragma once

#include "Core.h"
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

class height_map : public core
{
public:
    height_map(const std::string& window_title);

    bool initialize() override;
    void render() override;

private:
    void create_mesh();

private:
    shader height_map_shader;
    vao floor;
    texture height_map_texture;

    const size_t floor_size = 100;
};