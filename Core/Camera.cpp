#include "Camera.h"

using namespace glm;

void xbox_camera::update(const xbox_controller& controller, const float delta_time)
{
    delta_time;
    speed_modifier;

    // digipad:
    // [up/down] speed up/down
    // [left/right]fov

    // [right stick] direction
    // [left stick] position
    // position += direction * delta_time * speed_modifier; // falsch stick nicht drin
    //controller.get_left_analog_stick();
}

mat4 xbox_camera::get_view_projection() const
{
    return glm::perspective(field_of_view, width / height, near_plane, far_plane) * glm::lookAt(position, direction, up);
}