#pragma once

#include "CommonHeaders.h"
#include "RenderContext.h"

class xbox_camera
{
public:
    void update(const render_context& render_context, const float delta_time);
    glm::mat4 get_view_projection() const;

private:
    float width = 1.0f;
    float height = 1.0f;
    float field_of_view = 90.0f;
    float near_plane = 1.0f;
    float far_plane = 100.0f;
    float speed_modifier = 1.0f;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};