//
//  LineCurve.h
//  CSE167Project3
//
//  Created by Zhong Yu on 3/1/18.
//  Copyright © 2018 Zhong Yu. All rights reserved.
//

#ifndef LineCurve_h
#define LineCurve_h

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

class LineCurve
{
public:
    LineCurve(std::vector<glm::vec3>);
    ~LineCurve();
    
    glm::mat4 toWorld;
    float numberOfPoints;
    std::vector<std::vector<glm::vec3> > finalseg;
    std::vector<std::vector<glm::vec3> > newcontrol;
    GLfloat seg[22500][3];
    GLuint indi[22201][6];
    GLfloat norm[22500][3];
    GLfloat all[45000][3];
    
    void draw(GLuint);
    std::vector<glm::vec3> getBCurve(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    void update();
    void spin(float);
    void updateToWorld();
    //    void generateBCurve(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    //    std::vector<glm::vec3> getTrack();
    
    //  void update();
    //    void spin(float, char axis);
    void translate(float, char axis);
    //    float angle;
    float x_offset;
    float y_offset;
    float z_offset;
    glm::mat4 rotate;
    glm::mat4 trans;
    glm::mat4 scale;
    
    // These variables are needed for the shader program
    GLuint VBO, VAO, EBO;
    GLuint uProjection, uModelview, uModel;
};


//LineCurve* c1;
//LineCurve* c2;
//LineCurve* c3;
//LineCurve* c4;
//
//std::vector<glm::vec3> allcp;
//std::vector<glm::vec3> allscp;
//std::vector<glm::vec3> alltcp;
//std::vector<glm::vec3> allfcp;
//
//glm::vec3 cp1(-1.5f, 0.0f, 0.0f);
//glm::vec3 cp2(-0.5f, 0.0f, 0.0f);
//glm::vec3 cp3(0.5f, 0.0f, 0.0f);
//glm::vec3 cp4(1.5f, 0.0f, 0.0f);
//glm::vec3 cp5(-1.5f, 0.0f, 1.33f);
//glm::vec3 cp6(-0.5f, 0.0f, 1.33f);
//glm::vec3 cp7(0.5f, 0.0f, 1.33f);
//glm::vec3 cp8(1.5f, 0.0f, 1.33f);
//glm::vec3 cp9(-1.5f, -2.0f, 1.33f);
//glm::vec3 cp10(-0.5f, -2.0f, 1.33f);
//glm::vec3 cp11(0.5f, -2.0f, 1.33f);
//glm::vec3 cp12(1.5f, -2.0f, 1.33f);
//glm::vec3 cp13(-1.5f, -2.0f, 0.0f);
//glm::vec3 cp14(-0.5f, -2.0f, 0.0f);
//glm::vec3 cp15(0.5f, -2.0f, 0.0f);
//glm::vec3 cp16(1.5f, -2.0f, 0.0f);
//
//glm::vec3 scp1(-1.5f, 2.0f, 0.0f);
//glm::vec3 scp2(-0.5f, 2.0f, 0.0f);
//glm::vec3 scp3(0.5f, 2.0f, 0.0f);
//glm::vec3 scp4(1.5f, 2.0f, 0.0f);
//glm::vec3 scp5(-1.5f, 2.0f, -1.33f);
//glm::vec3 scp6(-0.5f, 2.0f, -1.33f);
//glm::vec3 scp7(0.5f, 2.0f, -1.33f);
//glm::vec3 scp8(1.5f, 2.0f, -1.33f);
//glm::vec3 scp9(-1.5f, 0.0f, -1.33f);
//glm::vec3 scp10(-0.5f, 0.0f, -1.33f);
//glm::vec3 scp11(0.5f, 0.0f, -1.33f);
//glm::vec3 scp12(1.5f, 0.0f, -1.33f);
//glm::vec3 scp13(-1.5f, 0.0f, 0.2f);
//glm::vec3 scp14(-0.5f, 0.0f, 0.2f);
//glm::vec3 scp15(0.5f, 0.0f, 0.2f);
//glm::vec3 scp16(1.5f, 0.0f, 0.2f);
//
//glm::vec3 tcp1(-1.5f, 0.0f, -2.0f);
//glm::vec3 tcp2(-0.5f, 0.0f, -2.0f);
//glm::vec3 tcp3(0.5f, 0.0f, -2.0f);
//glm::vec3 tcp4(1.5f, 0.0f, -2.0f);
//glm::vec3 tcp5(-1.5f, -1.33f, -2.0f);
//glm::vec3 tcp6(-0.5f, -1.33f, -2.0f);
//glm::vec3 tcp7(0.5f, -1.33f, -2.0f);
//glm::vec3 tcp8(1.5f, -1.33f, -2.0f);
//glm::vec3 tcp9(-1.5f, -1.33f, 0.0f);
//glm::vec3 tcp10(-0.5f, -1.33f, 0.0f);
//glm::vec3 tcp11(0.5f, -1.33f, 0.0f);
//glm::vec3 tcp12(1.5f, -1.33f, 0.0f);
//glm::vec3 tcp13(-1.5f, 0.2f, 0.0f);
//glm::vec3 tcp14(-0.5f, 0.2f, 0.0f);
//glm::vec3 tcp15(0.5f, 0.2f, 0.0f);
//glm::vec3 tcp16(1.5f, 0.2f, 0.0f);
//
//glm::vec3 fcp1(-1.5f, 0.0f, 0.0f);
//glm::vec3 fcp2(-0.5f, 0.0f, 0.0f);
//glm::vec3 fcp3(0.5f, 0.0f, 0.0f);
//glm::vec3 fcp4(1.5f, 0.0f, 0.0f);
//glm::vec3 fcp5(-1.5f, 1.33f, 0.0f);
//glm::vec3 fcp6(-0.5f, 1.33f, 0.0f);
//glm::vec3 fcp7(0.5f, 1.33f, 0.0f);
//glm::vec3 fcp8(1.5f, 1.33f, 0.0f);
//glm::vec3 fcp9(-1.5f, 1.33f, 2.0f);
//glm::vec3 fcp10(-0.5f, 1.33f, 2.0f);
//glm::vec3 fcp11(0.5f, 1.33f, 2.0f);
//glm::vec3 fcp12(1.5f, 1.33f, 2.0f);
//glm::vec3 fcp13(-1.5f, 0.0f, 2.0f);
//glm::vec3 fcp14(-0.5f, 0.0f, 2.0f);
//glm::vec3 fcp15(0.5f, 0.0f, 2.0f);
//glm::vec3 fcp16(1.5f, 0.0f, 2.0f);
//
//Particles* trialPart;
//
//void Window::initialize_objects()
//{
//    //    cube = new Cube();
//    allcp.push_back(cp1);
//    allcp.push_back(cp2);
//    allcp.push_back(cp3);
//    allcp.push_back(cp4);
//    allcp.push_back(cp5);
//    allcp.push_back(cp6);
//    allcp.push_back(cp7);
//    allcp.push_back(cp8);
//    allcp.push_back(cp9);
//    allcp.push_back(cp10);
//    allcp.push_back(cp11);
//    allcp.push_back(cp12);
//    allcp.push_back(cp13);
//    allcp.push_back(cp14);
//    allcp.push_back(cp15);
//    allcp.push_back(cp16);
//    allscp.push_back(scp1);
//    allscp.push_back(scp2);
//    allscp.push_back(scp3);
//    allscp.push_back(scp4);
//    allscp.push_back(scp5);
//    allscp.push_back(scp6);
//    allscp.push_back(scp7);
//    allscp.push_back(scp8);
//    allscp.push_back(scp9);
//    allscp.push_back(scp10);
//    allscp.push_back(scp11);
//    allscp.push_back(scp12);
//    allscp.push_back(scp13);
//    allscp.push_back(scp14);
//    allscp.push_back(scp15);
//    allscp.push_back(scp16);
//    alltcp.push_back(tcp1);
//    alltcp.push_back(tcp2);
//    alltcp.push_back(tcp3);
//    alltcp.push_back(tcp4);
//    alltcp.push_back(tcp5);
//    alltcp.push_back(tcp6);
//    alltcp.push_back(tcp7);
//    alltcp.push_back(tcp8);
//    alltcp.push_back(tcp9);
//    alltcp.push_back(tcp10);
//    alltcp.push_back(tcp11);
//    alltcp.push_back(tcp12);
//    alltcp.push_back(tcp13);
//    alltcp.push_back(tcp14);
//    alltcp.push_back(tcp15);
//    alltcp.push_back(tcp16);
//    allfcp.push_back(fcp1);
//    allfcp.push_back(fcp2);
//    allfcp.push_back(fcp3);
//    allfcp.push_back(fcp4);
//    allfcp.push_back(fcp5);
//    allfcp.push_back(fcp6);
//    allfcp.push_back(fcp7);
//    allfcp.push_back(fcp8);
//    allfcp.push_back(fcp9);
//    allfcp.push_back(fcp10);
//    allfcp.push_back(fcp11);
//    allfcp.push_back(fcp12);
//    allfcp.push_back(fcp13);
//    allfcp.push_back(fcp14);
//    allfcp.push_back(fcp15);
//    allfcp.push_back(fcp16);
//    c1 = new LineCurve(allcp);
//    c2 = new LineCurve(allscp);
//    c3 = new LineCurve(alltcp);
//    c4 = new LineCurve(allfcp);
//

#endif /* LineCurve_h */
