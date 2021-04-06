#version 460

in float height;

out vec4 fragment_color;

void main()
{
    float color = height / 10.0;
    fragment_color = vec4(color, 1.0-color, 0.0, 1.0);
}