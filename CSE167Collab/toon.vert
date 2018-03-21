#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 Tex;

out vec2 TexC;

void main()
{
    TexC = Tex;
    gl_Position = vec4(position, 1.0);
}
