#include "Camera.h"
#include "print.h"

using namespace glm;

void xbox_camera::update(const xbox_controller& controller, const float delta_time)
{
    const vec2 digital_pad = controller.get_digital_pad();

    if (abs(digital_pad.y))
    {
        speed_modifier = max(1.0f, speed_modifier + digital_pad.y * delta_time);
        print::info << "Camera speed modifier: " << speed_modifier << print::endl;
    }
    if (abs(digital_pad.x))
    {
        field_of_view = max(45.0f, min(180.0f, field_of_view + digital_pad.x * delta_time));
        print::info << "Camera field of view: " << field_of_view << print::endl;
    }

    const float factor = delta_time * speed_modifier;
    const vec3 right = cross(direction, up);

    // [right stick] direction
    const vec2 right_amplitude = controller.get_right_analog_stick();

    // [left stick] position
    const vec2 left_amplitude = controller.get_left_analog_stick();
    position += direction * left_amplitude.y * factor;
    position += right * left_amplitude.x * factor;
}

mat4 xbox_camera::get_view_projection() const
{
    return glm::perspective(field_of_view, width / height, near_plane, far_plane) * glm::lookAt(position, direction, up);
}