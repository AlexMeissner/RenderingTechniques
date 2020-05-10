#include "stdafx.h"

#include "Shader.h"

void render()
{

}

int main()
{
    core render_core("Grass Rendering");

    shader test_shader;
    test_shader.load_vertex_shader("W:\\Projects\\Coding\\Super Mario Bros\\SuperMarioBros\\Rendering\\Shader\\Vertex\\TempPass.glsl");
    test_shader.load_fragment_shader("W:\\Projects\\Coding\\Super Mario Bros\\SuperMarioBros\\Rendering\\Shader\\Fragment\\TempPass.glsl");

    render_core.watch(test_shader);
    render_core.run(render);

    return 0;
}