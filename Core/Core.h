#pragma once

#include "RenderContext.h"

class core
{
public:
    core(const std::string& window_title);

    void run(void render_function());

private:
    render_context context;
};