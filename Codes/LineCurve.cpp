//
//  LineCurve.cpp
//  CSE167Project3
//
//  Created by Zhong Yu on 3/1/18.
//  Copyright © 2018 Zhong Yu. All rights reserved.
//

#include <stdio.h>
#include "Window.h"
#include <iostream>
#include <algorithm>
#include "LineCurve.h"
#include <math.h>

using namespace std;
using namespace glm;

LineCurve::LineCurve(vector<vec3> controlpoints)
{
    numberOfPoints = 150.0;
    
    vector<vec3> seg1 = getBCurve(controlpoints[0], controlpoints[4], controlpoints[8], controlpoints[12]);
    vector<vec3> seg2 = getBCurve(controlpoints[1], controlpoints[5], controlpoints[9], controlpoints[13]);
    vector<vec3> seg3 = getBCurve(controlpoints[2], controlpoints[6], controlpoints[10], controlpoints[14]);
    vector<vec3> seg4 = getBCurve(controlpoints[3], controlpoints[7], controlpoints[11], controlpoints[15]);
    newcontrol.push_back(seg1);
    newcontrol.push_back(seg2);
    newcontrol.push_back(seg3);
    newcontrol.push_back(seg4);
    
    for (int i = 0; i < 150; i++)
    {
        vector<vec3> temprow = getBCurve(newcontrol[0][i], newcontrol[1][i], newcontrol[2][i], newcontrol[3][i]);
        finalseg.push_back(temprow);
    }
    
    for (int j = 0; j < 150; j++)
    {
        for (int k = 0; k < 150; k++)
        {
            int ind = j*150+k;
            seg[ind][0] = finalseg[j][k].x;
            seg[ind][1] = finalseg[j][k].y;
            seg[ind][2] = finalseg[j][k].z;
        }
    }
    
    int indiindi = 0;
    for (int k = 0; k < 22201; k++)
    {
        if(k % 150 != 149)
        {
            //            indi[indiindi] = [k, k+1, k+151, k+151, k+150, k];
            indi[indiindi][0] = k;
            indi[indiindi][1] = k+1;
            indi[indiindi][2] = k+151;
            indi[indiindi][3] = k+151;
            indi[indiindi][4] = k+150;
            indi[indiindi][5] = k;
            indiindi ++;
        }
    }
    
    for (int l = 0; l < 22500; l++)
    {
        if(l % 150 != 149)
        {
            float downx = seg[l+150][0]-seg[l][0];
            float downy = seg[l+150][1]-seg[l][1];
            float downz = seg[l+150][2]-seg[l][2];
            float rightx = seg[l+1][0]-seg[l][0];
            float righty = seg[l+1][1]-seg[l][1];
            float rightz = seg[l+1][2]-seg[l][2];
            vec3 down, right;
            down.x = downx;
            down.y = downy;
            down.z = downz;
            right.x = rightx;
            right.y = righty;
            right.z = rightz;
            vec3 tempnorm = cross(down, right);
            tempnorm = normalize(tempnorm);
            norm[l][0] = tempnorm.x;
            norm[l][1] = tempnorm.y;
            norm[l][2] = tempnorm.z;
            //            norm[l][0] = (tempnorm.x+1.0)/2.0;
            //            norm[l][1] = (tempnorm.y+1.0)/2.0;
            //            norm[l][2] = (tempnorm.z+1.0)/2.0;
        }
        else
        {
            float downx = seg[l+150][0]-seg[l][0];
            float downy = seg[l+150][1]-seg[l][1];
            float downz = seg[l+150][2]-seg[l][2];
            float leftx = seg[l-1][0]-seg[l][0];
            float lefty = seg[l-1][1]-seg[l][1];
            float leftz = seg[l-1][2]-seg[l][2];
            vec3 down, left;
            down.x = downx;
            down.y = downy;
            down.z = downz;
            left.x = leftx;
            left.y = lefty;
            left.z = leftz;
            vec3 tempnorm = cross(left, down);
            tempnorm = normalize(tempnorm);
            norm[l][0] = tempnorm.x;
            norm[l][1] = tempnorm.y;
            norm[l][2] = tempnorm.z;
            
            //            norm[l][0] = (tempnorm.x+1.0)/2.0;
            //            norm[l][1] = (tempnorm.y+1.0)/2.0;
            //            norm[l][2] = (tempnorm.z+1.0)/2.0;
        }
    }
    
    for (int m = 0; m < 22500; m++)
    {
        all[m*2][0] = seg[m][0];
        all[m*2][1] = seg[m][1];
        all[m*2][2] = seg[m][2];
    }
    
    for (int n = 0; n < 22500; n++)
    {
        all[n*2+1][0] = norm[n][0];
        all[n*2+1][1] = norm[n][1];
        all[n*2+1][2] = norm[n][2];
    }
    
    toWorld = mat4(1.0f);
    trans = mat4(1.0f);
    rotate = mat4(1.0f);
    scale = mat4(1.0f);
    x_offset = 0.0;
    y_offset =0.0;
    z_offset =0.0;
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
    // Consider the VAO as a container for all your buffers.
    glBindVertexArray(VAO);
    
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(all), all, GL_STATIC_DRAW);
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
    
    // We've sent the vertex data over to OpenGL, but there's still something missing.
    // In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
}

LineCurve::~LineCurve()
{
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

vector<vec3> LineCurve::getBCurve(vec3 P0, vec3 P1, vec3 P2, vec3 P3)
{
    vector<vec3> answer;
    for(int i = 0; i < 150; i++)
    {
        float t = (float) i / numberOfPoints;
        GLfloat tempx = (pow((1-t), 3.0) * P0.x) +
        (3 * pow((1-t),2) * t * P1.x) +
        (3 * (1-t) * t * t * P2.x) +
        (pow(t, 3) * P3.x);
        GLfloat tempy = (pow((1-t), 3.0) * P0.y) +
        (3 * pow((1-t),2) * t * P1.y) +
        (3 * (1-t) * t * t * P2.y) +
        (pow(t, 3) * P3.y);
        GLfloat tempz = (pow((1-t), 3.0) * P0.z) +
        (3 * pow((1-t),2) * t * P1.z) +
        (3 * (1-t) * t * t * P2.z) +
        (pow(t, 3) * P3.z);
        
        vec3 temp;
        temp.x = tempx;
        temp.y = tempy;
        temp.z = tempz;
        answer.push_back(temp);
    }
    
    return answer;
}

void LineCurve::draw(GLuint shaderProgram)
{
    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 modelview = Window::V * toWorld;
    // We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
    // Consequently, we need to forward the projection, view, and model matrices to the shader programs
    // Get the location of the uniform variables "projection" and "modelview"
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    uModel = glGetUniformLocation(shaderProgram, "model");
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    // Now draw the cube. We simply need to bind the VAO associated with it.
    glBindVertexArray(VAO);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
    //    glDrawElements(GL_LINE, 8, GL_UNSIGNED_INT, 0);
    
    //    drawing line strip
    //    glLineWidth(100.0f);
    //    glDrawArrays(GL_LINE_STRIP, 0, 22500);
    
    glDrawElements(GL_TRIANGLES, 133206, GL_UNSIGNED_INT, 0);
    
    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
}

void LineCurve::update()
{
    //    updateToWorld();
    spin(1.0f);
}

void LineCurve::spin(float deg)
{
    // If you haven't figured it out from the last project, this is how you fix spin's behavior
    toWorld = toWorld * glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
}

void LineCurve::updateToWorld()
{
    toWorld = trans * scale * rotate * toWorld;
}

void LineCurve::translate(float translation, char axis)
{
    if(axis == 'x')
    {
        x_offset += translation;
        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        updateToWorld();
    }
    else if (axis == 'y')
    {
        y_offset += translation;
        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        updateToWorld();
    }
    else
    {
        z_offset += translation;
        //        this->toWorld = toWorld * glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        this->trans = glm::translate(mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset));
        updateToWorld();
    }
}

