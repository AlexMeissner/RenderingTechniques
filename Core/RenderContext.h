#pragma once

#include "CommonHeaders.h"

class render_context
{
public:
    ~render_context();

    bool create(const std::string& window_title);
    bool should_terminate() const;

    float get_aspect_ratio() const;

    void begin_frame();
    void end_frame() const;

private:
    GLFWwindow* window = nullptr;
};