//
//  Particles.cpp
//  CSE167Proj4
//
//  Created by Zhong Yu on 3/16/18.
//  Copyright © 2018 Zhong Yu. All rights reserved.
//

#include <stdio.h>
#include "Window.h"
#include <iostream>
#include <algorithm>
#include "Particles.h"
#include <math.h>
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

Particles::Particles()
{
    toWorld = glm::mat4(1.0f);
    
    int index = 0;
    float offset = 0.5f;
    for (int y = -100; y < 100; y += 2)
    {
        for (int x = -100; x < 100; x += 2)
        {
            glm::vec3 translation;
            translation.x = (float)x / 50.0f + offset + (float) rand()/ (float) RAND_MAX * 4.0-2.0;
            translation.y = (float)y / 50.0f + offset + (float) rand()/ (float) RAND_MAX * 4.0-2.0;
            translation.z = 0.0f;
            translations[index++] = translation;
        }
    }
    
//    x_offset = 0.0;
//    y_offset = 0.0;
//    z_offset = 0.0;
//    rotate = mat4(1.0f);
//    trans = mat4(1.0f);
//    scale = mat4(1.0f);
    life = 1;
    visible = 1;
    
    glGenBuffers(1, &instVBO);

 //   glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    
    // Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
    // Consider the VAO as a container for all your buffers.
    glBindVertexArray(quadVAO);
    
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadv), quadv, GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          6 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          6 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)(3*sizeof(GLfloat))); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    
//    glBindBuffer(GL_ARRAY_BUFFER, instVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instVBO); // this attribute comes from a different vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 10000, &translations[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
//    glEnableVertexAttribArray(3);
//    glBindBuffer(GL_ARRAY_BUFFER, transVBO); // this attribute comes from a different vertex buffer
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 100, &TOW[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
//    for (int i = 0; i < 100; i++)
//    {
//        float transx = (float) rand()/ (float) RAND_MAX * 5.0;
//        float transy = (float) rand()/ (float) RAND_MAX * 5.0;
//        float transz = (float) rand()/ (float) RAND_MAX * 5.0;
//        TOW[i] = glm::translate(mat4(1.0f), glm::vec3(transx, transy, transz));
//    }
}

void Particles::draw(GLuint shaderProgram)
{
    if (visible)
    {
        // Calculate the combination of the model and view (camera inverse) matrices
        glm::mat4 modelview = Window::V * toWorld;
        // We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
        // Consequently, we need to forward the projection, view, and model matrices to the shader programs
        // Get the location of the uniform variables "projection" and "modelview"
        uProjection = glGetUniformLocation(shaderProgram, "projection");
        uModelview = glGetUniformLocation(shaderProgram, "modelview");
        uModel = glGetUniformLocation(shaderProgram, "model");
        uView = glGetUniformLocation(shaderProgram, "view");
        // Now send these values to the shader program
        glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
        glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
        glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
        glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);
        // Now draw the cube. We simply need to bind the VAO associated with it.
        glBindVertexArray(quadVAO);
        // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 10000);
        // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
        glBindVertexArray(0);
    }
}

Particles::~Particles()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &instVBO);
    glDeleteBuffers(1, &quadVBO);
}

void Particles::update()
{
    if(life % 200 != 0)
    {
        for (int i = 0; i < 10000; i++)
        {
            translations[i].x += rand()/ (float) RAND_MAX/10.0;
            translations[i].y += rand()/ (float) RAND_MAX/10.0;
            translations[i].z += rand()/ (float) RAND_MAX/10.0;
            translations[i].x -= rand()/ (float) RAND_MAX/10.0;
            translations[i].y -= rand()/ (float) RAND_MAX/10.0;
            translations[i].z -= rand()/ (float) RAND_MAX/10.0;
        }
        
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, instVBO); // this attribute comes from a different vertex buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 10000, &translations[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glVertexAttribDivisor(2, 1);
        life ++;
    }
    else
    {
        visible = 0;
    }
}

void Particles::setVisible()
{
    visible = 1;
    life++;
}

//void Particles::updateToWorld()
//{
//    toWorld = trans * scale * rotate * toWorld;
//}
//
//void Particles::translate(float translation, char axis)
//{
//    if(axis == 'x')
//    {
//        x_offset += translation;
//        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        updateToWorld();
//    }
//    else if (axis == 'y')
//    {
//        y_offset += translation;
//        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        updateToWorld();
//    }
//    else
//    {
//        z_offset += translation;
//        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
//        updateToWorld();
//    }
//}

