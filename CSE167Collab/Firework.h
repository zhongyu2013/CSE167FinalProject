//
//  Firework.h
//  CSE167Proj4
//
//  Created by Zhong Yu on 3/18/18.
//  Copyright © 2018 Zhong Yu. All rights reserved.
//

#ifndef Firework_h
#define Firework_h

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h> // Needed for a new class
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct Particle
{
    glm::vec3 pos, speed;
    unsigned char r,g,b,a; // Color
    float size, angle, weight;
    float life; // Remaining life of the particle. if < 0 : dead and unused.
    float cameradistance;
    
    bool operator<(Particle& that)
    {
        // Sort in reverse order : far particles drawn first.
        return this->cameradistance > that.cameradistance;
    }
};

class Firework
{
public:
    Firework();
    ~Firework();
    glm::mat4 toWorld;
    void draw(GLuint);
    glm::vec3 campos(0.0f, 0.0f, 20.0f);
    float delta;
    
    // These variables are needed for the shader program
    const int MaxParticles = 1000;
    Particle ParticlesContainer[MaxParticles];
    GLuint billboard_vertex_buffer, particles_position_buffer, particles_color_buffer;
    GLuint uProjection, uModelview;
};

static const GLfloat g_vertex_buffer_data[] =
{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
};



#endif /* Firework_h */
