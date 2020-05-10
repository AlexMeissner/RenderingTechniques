#include "Core.h"
#include "Shader.h"

core::core(const std::string& window_title)
{
    context.create(window_title);
}

void core::watch(shader& wachted_shader)
{
    wachted_shaders.push_back(&wachted_shader);
}

void core::run(void render_function())
{
    while (!context.should_terminate())
    {
        for (shader* wachted_shader : wachted_shaders)
        {
            wachted_shader->hot_reload();
        }

        context.begin_frame();
        render_function();
        context.end_frame();
    }
}