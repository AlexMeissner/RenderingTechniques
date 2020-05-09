#include "Core.h"

core::core(const std::string& window_title)
{
    context.create(window_title);
}

void core::run(void render_function())
{
    while (!context.should_terminate())
    {
        context.begin_frame();
        render_function();
        context.end_frame();
    }
}