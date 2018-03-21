#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.

//in vec3 FragPos;
//in vec3 FragPos;
in float sampleOutput;
in vec3 Nnormal;

out vec4 ocolor;

void main()
{
    vec3 norm = Nnormal;
    ocolor = vec4(norm.x, norm.y, norm.z, sampleOutput);
}

