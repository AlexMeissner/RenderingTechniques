#version 460

layout(location = 0) in vec3 vertex;
layout(location = 2) in vec3 color;

uniform mat4 view_projection;

out vec3 vertex_color;

void main()
{
    gl_Position  = view_projection * vec4(vertex, 1.0);
    vertex_color = color;
}