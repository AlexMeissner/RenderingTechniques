#pragma once

#include "CommonHeaders.h"

class xbox_controller
{
public:
    xbox_controller(GLFWwindow* context);

    glm::vec2 get_left_analog_stick() const;
    glm::vec2 get_right_analog_stick() const;
    glm::vec2 get_digital_pad() const;

private:
    GLFWwindow* window = nullptr;
};