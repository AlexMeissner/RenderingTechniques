#pragma once

#include "Core.h"
#include "VAO.h"
#include "Shader.h"

class grass : public core
{
public:
    grass(const std::string& window_title);

    bool initialize() override;
    void render() override;

private:
    shader floor_shader;
    vao floor;

    const float floor_size = 100.0f;
};