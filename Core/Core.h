#pragma once

#include "RenderContext.h"
#include "Camera.h"

class shader;

class core
{
public:
    core(const std::string& window_title);

    void watch(shader& wachted_shader);
    void run();

    virtual bool initialize();
    virtual void update();
    virtual void render();

private:
    render_context context;
    xbox_camera camera;

    std::vector<shader*> wachted_shaders;
};