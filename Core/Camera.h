#pragma once

#include "CommonHeaders.h"
#include "XBoxController.h"

class xbox_camera
{
public:
    void update(const xbox_controller& controller, const float delta_time);
    glm::mat4 get_view_projection() const;

private:
    float width = 1.0f;
    float height = 1.0f;
    float field_of_view = 90.0f;
    float near_plane = 0.1f;
    float far_plane = 1000.0f;
    float speed_modifier = 10.0f;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    std::array<bool, 2> push_state = { false, false };
};