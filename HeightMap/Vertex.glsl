#version 460

layout(location = 0) in vec3 vertex;

uniform mat4 view_projection;
uniform sampler2D texture_sampler;

out float height;

void main()
{
    height = texture(texture_sampler, vec2(vertex.x/100.0, vertex.z/100.0)).y * 10.0;
    vec4 position = vec4(vertex.x, height, vertex.z, 1.0);
    gl_Position = view_projection * position;
}