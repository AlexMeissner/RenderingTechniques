#include "Camera.h"
#include "print.h"

using namespace glm;

void xbox_camera::update(const xbox_controller& controller, const float delta_time)
{
    const vec2 digital_pad = controller.get_digital_pad();

    if (abs(digital_pad.y) && !push_state[0])
    {
        speed_modifier = max(1.0f, speed_modifier + digital_pad.y);
        print::info << "Camera speed modifier: " << speed_modifier << print::endl;
    }
    if (abs(digital_pad.x) && !push_state[1])
    {
        field_of_view = max(45.0f, min(180.0f, field_of_view + digital_pad.x));
        print::info << "Camera field of view: " << field_of_view << print::endl;
    }

    push_state[0] = digital_pad.y;
    push_state[1] = digital_pad.x;

    const vec3 right = cross(direction, up);

    const vec2 right_amplitude = controller.get_right_analog_stick();
    direction = glm::rotate(direction, -right_amplitude.x * delta_time * 0.01f, up);
    direction = glm::rotate(direction, right_amplitude.y * delta_time * 0.01f, right);

    const vec2 left_amplitude = controller.get_left_analog_stick();
    position += direction * left_amplitude.y * delta_time * speed_modifier * 0.01f;
    position += right * left_amplitude.x * delta_time * speed_modifier * 0.01f;
}

mat4 xbox_camera::get_view_projection() const
{
    return glm::perspective(field_of_view, width / height, near_plane, far_plane) * glm::lookAt(position, position + direction, up);
}