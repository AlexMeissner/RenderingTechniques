#include "XBoxController.h"

using namespace glm;

namespace
{
    float remove_deadzone(const float amplitude)
    {
        constexpr float deadzone = 0.1f;

        if (abs(amplitude) < deadzone)
        {
            return 0.0f;
        }
        else if (amplitude > 0)
        {
            return (amplitude - deadzone) / (1.0f - deadzone);
        }
        else
        {
            return -(abs(amplitude) - deadzone) / (1.0f - deadzone);
        }
    }
}

xbox_controller::xbox_controller(GLFWwindow* context)
    :window(context)
{
}

vec2 xbox_controller::get_left_analog_stick() const
{
    int count = 0;
    const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

    if (count < 2)
    {
        return vec2(0.0f, 0.0f);
    }

    return vec2(remove_deadzone(axes[0]), -remove_deadzone(axes[1]));
}

vec2 xbox_controller::get_right_analog_stick() const
{
    int count = 0;
    const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

    if (count < 4)
    {
        return vec2(0.0f, 0.0f);
    }

    return vec2(remove_deadzone(axes[2]), -remove_deadzone(axes[3]));
}

vec2 xbox_controller::get_digital_pad() const
{
    return glm::vec2();
}