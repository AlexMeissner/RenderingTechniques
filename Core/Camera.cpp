#include "Camera.h"

using namespace glm;

void xbox_camera::update(const render_context& render_context, const float delta_time)
{
    delta_time;
    speed_modifier;

    // digipad:
    // [up/down] speed up/down
    // [left/right]fov

    // [right stick] direction
    // [left stick] position
    // position += direction * delta_time * speed_modifier; // falsch stick nicht drin
}

mat4 xbox_camera::get_view_projection() const
{
    return glm::perspective(field_of_view, width / height, near_plane, far_plane) * glm::lookAt(position, direction, up);
}