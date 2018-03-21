#version 330 core
out vec4 ocolor;

in vec2 TexC;

uniform sampler2D depthM;
uniform float near;
uniform float far;


void main()
{
    float depth = texture(depthM, TexC).r;
    ocolor = vec4(vec3(depth), 1.0);
}
