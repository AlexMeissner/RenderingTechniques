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

void core::run()
{
    auto last_time = std::chrono::system_clock::now();

    while (!context.should_terminate())
    {
        for (shader* wachted_shader : wachted_shaders)
        {
            wachted_shader->hot_reload();
        }

        const auto now = std::chrono::system_clock::now();
        const float time_delta = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count());
        last_time = now;

        update();
        camera.update(context.get_controller(), time_delta);

        context.begin_frame();
        render();
        context.end_frame();
    }
}

bool core::initialize()
{
    return false;
}

void core::update()
{
}

void core::render()
{
}