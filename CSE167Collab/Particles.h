//
//  Particles.h
//  CSE167Proj4
//
//  Created by Zhong Yu on 3/16/18.
//  Copyright © 2018 Zhong Yu. All rights reserved.
//

#ifndef Particles_h
#define Particles_h

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

class Particles
{
public:
    Particles();
    ~Particles();
    
    glm::mat4 toWorld;
    glm::vec3 translations[10000];
//    glm::mat4 TOW[100];
    void update();
    int life;
    int visible;
    
    void draw(GLuint);
    void setVisible();
    // These variables are needed for the shader program
    GLuint quadVAO, quadVBO, instVBO, transVBO;
    GLuint uProjection, uModelview, uView, uModel;
    
//    void updateToWorld();
//    //    void generateBCurve(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
//    //    std::vector<glm::vec3> getTrack();
//    
//    //  void update();
//    //    void spin(float, char axis);
//    void translate(float, char axis);
//    //    float angle;
//    float x_offset;
//    float y_offset;
//    float z_offset;
//    glm::mat4 rotate;
//    glm::mat4 trans;
//    glm::mat4 scale;
};

static const GLfloat quadv[] =
{
    -0.05f,  0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.05f, -0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
    
    -0.05f,  0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.05f,  0.05f,0.0f,  1.0f, 0.0f, 0.0f
};
#endif /* Particles_h */
