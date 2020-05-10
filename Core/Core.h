#pragma once

#include "RenderContext.h"

class shader;

class core
{
public:
    core(const std::string& window_title);

    void watch(shader& wachted_shader);
    void run(void render_function());

private:
    render_context context;

    std::vector<shader*> wachted_shaders;
};