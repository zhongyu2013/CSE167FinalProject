#include "Window.h"
#include "LineCurve.h"
#include "OBJObject.h"
#include "Particles.h"

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

const char* window_title = "CSE 167 Final Project By Kuo Liang and Yu Zhong";
glm::vec3 v0;
glm::vec3 v1;
glm::vec3 v2;
glm::vec3 v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19;
GLuint baseVAO, baseVBO,baseid;
std::vector<glm::vec3> cvertices;
std::vector<glm::vec3> cindices;
GLuint CVAO,CVBO,CEBO,DVAO,DFBO,PVAO,DM;
GLuint uProjection, uModelview,umodel;

//skybox * box;
OBJObject * antenna;
OBJObject * head;
OBJObject * body;
OBJObject * limb;
//Curve * curve;
LineCurve * c1;
LineCurve * c2;
LineCurve * c3;
LineCurve * c4;
LineCurve * c5;
GLint shaderProgram;
GLint shader,pshader;
GLint shader_d;
GLint shader_s;
int Movement=0;
Particles * part;
int move =0;
GLuint depthMap;
double xtrack=320.0;
double ytrack=240.0;
glm::vec3 axtrack;
float angtrack;
glm::vec3 lastpoint;
glm::mat4 toWorldtrack=glm::mat4(1.0f);
glm::vec3 scaletrack;
int sw = 0;
int swn = 0;
int render = 0;
int r = 0;
int fun = 0;
int trackmode=0;
int blood = 0;
float radi = 12.5f;
GLuint depthMapFBO;
GLuint lshader;


// On some systems you need to change this to the absolute path
//#define VERTEX_SHADER_PATH "/Users/apple/Downloads/CSE167StarterCode-master/emmm/startlatewaitforGG/startlatewaitforGG/shader.vert"
//#define FRAGMENT_SHADER_PATH "/Users/apple/Downloads/CSE167StarterCode-master/emmm/startlatewaitforGG/startlatewaitforGG/shader.frag"
#define VERTEX_SHADER_PATH "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/shader.frag"
#define VERTEX_PATH_d "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/toon.vert"
#define FRAGMENT_PATH_d "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/toon.frag"
#define VERTEX_PATH_s "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/sim.vert"
#define FRAGMENT_PATH_s "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/sim.frag"
#define VERTEX_PATH_sl "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/lshader.vert"
#define FRAGMENT_PATH_sl "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/lshader.frag"
#define VERTEX_PATH_pl "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/pshader.vert"
#define FRAGMENT_PATH_pl "/Users/ZhongYu/Google Drive/UCSD Academics/2018 Winter/CSE 167/Week 10/CSE167Collab/CSE167Collab/pshader.frag"
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 translate_offset(0.0f, 0.0f, 0.0f);

// Default camera parameters
glm::vec3 cam_pos(-0.0f, 0.0f, -8.0f);        // e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);    // d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);            // up | What orientation "up" is
glm::vec3 lid_pos(-2.2,4.4,-2.2);
int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
int flag=0;
int spot = 0;
int point = 0;
int travel = 0;
int aa = 0;
glm::mat4 lprojection;
glm::mat4 lview;
glm::mat4 space;
float near =0.0f;
float far = 30.5f;
int shadow_s = 0;


const float baseVertices[] = {
    
    100.0f, -2.0f,  100.0f,  0.0f, 1.0f, 0.0f,
    -100.0f, -2.0f,  100.0f,  0.0f, 1.0f, 0.0f,
    -100.0f, -2.0f, -100.0f,  0.0f, 1.0f, 0.0f,
    
    100.0f, -2.0f, 100.0f,  0.0f, 1.0f, 0.0f,
    -100.0f, -2.0f, -100.0f,  0.0f, 1.0f, 0.0f,
    100.0f, -2.0f, -100.0f,  0.0f, 1.0f, 0.0f
};
glm::vec3 cp1(-1.5f, 0.0f, 0.0f);
glm::vec3 cp2(-0.5f, 0.0f, 0.0f);
glm::vec3 cp3(0.5f, 0.0f, 0.0f);
glm::vec3 cp4(1.5f, 0.0f, 0.0f);
glm::vec3 cp5(-1.5f, 0.0f, 1.33f);
glm::vec3 cp6(-0.5f, 0.0f, 1.33f);
glm::vec3 cp7(0.5f, 0.0f, 1.33f);
glm::vec3 cp8(1.5f, 0.0f, 1.33f);
glm::vec3 cp9(-1.5f, -2.0f, 1.33f);
glm::vec3 cp10(-0.5f, -2.0f, 1.33f);
glm::vec3 cp11(0.5f, -2.0f, 1.33f);
glm::vec3 cp12(1.5f, -2.0f, 1.33f);
glm::vec3 cp13(-1.5f, -2.0f, 0.0f);
glm::vec3 cp14(-0.5f, -2.0f, 0.0f);
glm::vec3 cp15(0.5f, -2.0f, 0.0f);
glm::vec3 cp16(1.5f, -2.0f, 0.0f);

glm::vec3 scp1(-1.5f, 2.0f, 0.0f);
glm::vec3 scp2(-0.5f, 2.0f, 0.0f);
glm::vec3 scp3(0.5f, 2.0f, 0.0f);
glm::vec3 scp4(1.5f, 2.0f, 0.0f);
glm::vec3 scp5(-1.5f, 2.0f, -1.33f);
glm::vec3 scp6(-0.5f, 2.0f, -1.33f);
glm::vec3 scp7(0.5f, 2.0f, -1.33f);
glm::vec3 scp8(1.5f, 2.0f, -1.33f);
glm::vec3 scp9(-1.5f, 0.0f, -1.33f);
glm::vec3 scp10(-0.5f, 0.0f, -1.33f);
glm::vec3 scp11(0.5f, 0.0f, -1.33f);
glm::vec3 scp12(1.5f, 0.0f, -1.33f);
glm::vec3 scp13(-1.5f, 0.0f, 0.2f);
glm::vec3 scp14(-0.5f, 0.0f, 0.2f);
glm::vec3 scp15(0.5f, 0.0f, 0.2f);
glm::vec3 scp16(1.5f, 0.0f, 0.2f);

glm::vec3 tcp1(-1.5f, 0.0f, -2.0f);
glm::vec3 tcp2(-0.5f, 0.0f, -2.0f);
glm::vec3 tcp3(0.5f, 0.0f, -2.0f);
glm::vec3 tcp4(1.5f, 0.0f, -2.0f);
glm::vec3 tcp5(-1.5f, -1.33f, -2.0f);
glm::vec3 tcp6(-0.5f, -1.33f, -2.0f);
glm::vec3 tcp7(0.5f, -1.33f, -2.0f);
glm::vec3 tcp8(1.5f, -1.33f, -2.0f);
glm::vec3 tcp9(-1.5f, -1.33f, 0.0f);
glm::vec3 tcp10(-0.5f, -1.33f, 0.0f);
glm::vec3 tcp11(0.5f, -1.33f, 0.0f);
glm::vec3 tcp12(1.5f, -1.33f, 0.0f);
glm::vec3 tcp13(-1.5f, 0.2f, 0.0f);
glm::vec3 tcp14(-0.5f, 0.2f, 0.0f);
glm::vec3 tcp15(0.5f, 0.2f, 0.0f);
glm::vec3 tcp16(1.5f, 0.2f, 0.0f);

glm::vec3 fcp1(-1.5f, 0.0f, 0.0f);
glm::vec3 fcp2(-0.5f, 0.0f, 0.0f);
glm::vec3 fcp3(0.5f, 0.0f, 0.0f);
glm::vec3 fcp4(1.5f, 0.0f, 0.0f);
glm::vec3 fcp5(-1.5f, 1.33f, 0.0f);
glm::vec3 fcp6(-0.5f, 1.33f, 0.0f);
glm::vec3 fcp7(0.5f, 1.33f, 0.0f);
glm::vec3 fcp8(1.5f, 1.33f, 0.0f);
glm::vec3 fcp9(-1.5f, 1.33f, 2.0f);
glm::vec3 fcp10(-0.5f, 1.33f, 2.0f);
glm::vec3 fcp11(0.5f, 1.33f, 2.0f);
glm::vec3 fcp12(1.5f, 1.33f, 2.0f);
glm::vec3 fcp13(-1.5f, 0.0f, 2.0f);
glm::vec3 fcp14(-0.5f, 0.0f, 2.0f);
glm::vec3 fcp15(0.5f, 0.0f, 2.0f);
glm::vec3 fcp16(1.5f, 0.0f, 2.0f);

glm::vec3 xx(0.0f);


std::vector<glm::vec3> allcp;
std::vector<glm::vec3> allscp;
std::vector<glm::vec3> alltcp;
std::vector<glm::vec3> allfcp;
std::vector<glm::vec3> allfcpxx;

void Window::initialize_objects()
{
    
    
    //----------put the following codes inside Window::initialize
        allcp.push_back(cp1);
        allcp.push_back(cp2);
        allcp.push_back(cp3);
        allcp.push_back(cp4);
        allcp.push_back(cp5);
        allcp.push_back(cp6);
        allcp.push_back(cp7);
        allcp.push_back(cp8);
        allcp.push_back(cp9);
        allcp.push_back(cp10);
        allcp.push_back(cp11);
        allcp.push_back(cp12);
        allcp.push_back(cp13);
        allcp.push_back(cp14);
        allcp.push_back(cp15);
        allcp.push_back(cp16);
        allscp.push_back(scp1);
        allscp.push_back(scp2);
        allscp.push_back(scp3);
        allscp.push_back(scp4);
        allscp.push_back(scp5);
        allscp.push_back(scp6);
        allscp.push_back(scp7);
        allscp.push_back(scp8);
        allscp.push_back(scp9);
        allscp.push_back(scp10);
        allscp.push_back(scp11);
        allscp.push_back(scp12);
        allscp.push_back(scp13);
        allscp.push_back(scp14);
        allscp.push_back(scp15);
        allscp.push_back(scp16);
        alltcp.push_back(tcp1);
        alltcp.push_back(tcp2);
        alltcp.push_back(tcp3);
        alltcp.push_back(tcp4);
        alltcp.push_back(tcp5);
        alltcp.push_back(tcp6);
        alltcp.push_back(tcp7);
        alltcp.push_back(tcp8);
        alltcp.push_back(tcp9);
        alltcp.push_back(tcp10);
        alltcp.push_back(tcp11);
        alltcp.push_back(tcp12);
        alltcp.push_back(tcp13);
        alltcp.push_back(tcp14);
        alltcp.push_back(tcp15);
        alltcp.push_back(tcp16);
        allfcp.push_back(fcp1);
        allfcp.push_back(fcp2);
        allfcp.push_back(fcp3);
        allfcp.push_back(fcp4);
        allfcp.push_back(fcp5);
        allfcp.push_back(fcp6);
        allfcp.push_back(fcp7);
        allfcp.push_back(fcp8);
        allfcp.push_back(fcp9);
        allfcp.push_back(fcp10);
        allfcp.push_back(fcp11);
        allfcp.push_back(fcp12);
        allfcp.push_back(fcp13);
        allfcp.push_back(fcp14);
        allfcp.push_back(fcp15);
        allfcp.push_back(fcp16);
    for(int x = 0;x<16;x++){
        allfcpxx.push_back(xx);
    }
    //allfcpxx.push_back(xx);

        c1 = new LineCurve(allcp);
        c2 = new LineCurve(allscp);
        c3 = new LineCurve(alltcp);
        c4 = new LineCurve(allfcp);
    
    c5 = new LineCurve(allfcpxx);
    
    const char * torsop = "/Users/ZhongYu/Desktop/bunny.obj";
    //cube = new Cube();
    // box = new skybox();
    // antenna = new OBJObject(antennap, 0.0f);
    // limb = new OBJObject(limbp, 0.0f);
    //  head = new OBJObject(headp,0.0f);
    body = new OBJObject(torsop,-0.0f);
    translate_offset.x = 5.0f;
    body->toWorld = glm::translate(glm::mat4(1.0f), translate_offset);
    shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
//    shader = LoadShaders(VERTEX_PATH, FRAGMENT_PATH);

    shader_s = LoadShaders(VERTEX_PATH_s, FRAGMENT_PATH_s);
    lshader = LoadShaders(VERTEX_PATH_sl,FRAGMENT_PATH_sl);
    pshader = LoadShaders(VERTEX_PATH_pl,FRAGMENT_PATH_pl);
   // glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), 1);
    glGenVertexArrays(1, &baseVAO);
    glGenBuffers(1, &baseVBO);
    glBindVertexArray(baseVAO);
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindVertexArray(0);
    
    
    
    glGenFramebuffers(1, &depthMapFBO);
    
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 640, 480, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float c[]={1,1,1,1};
    //c = {1,1,1,1};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    
    glUseProgram(shaderProgram);
    
    glUniform1i(glGetUniformLocation(shaderProgram, "dTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "shadowMap"), 1);
    
    part = new Particles();
    
  
    
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
    //delete(box);
    //delete(cube);
    delete(c1);
    delete(c2);
    delete(c3);
    delete(c4);
    delete(body);
    delete(part);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shader);
}

GLFWwindow* Window::create_window(int width, int height)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    
    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    
#ifdef __APPLE__ // Because Apple hates comforming to standards
    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Create the GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    
    // Check if the window could not be created
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
        glfwTerminate();
        return NULL;
    }
    
    // Make the context of the window
    glfwMakeContextCurrent(window);
    
    // Set swap interval to 1
    glfwSwapInterval(1);
    
    // Get the width and height of the framebuffer to properly resize the window
    glfwGetFramebufferSize(window, &width, &height);
    // Call the resize callback to make sure things get drawn immediately
    Window::resize_callback(window, width, height);
    
    return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
    glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
    glViewport(0, 0, width, height);
    
    if (height > 0)
    {
        P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}

void Window::idle_callback()
{
    if(r==1){
   c1->update();
    c2->update();
   c3->update();
    c4->update();
    }
    if(blood==1&&r==1)
    part->update();
}

void Window::display_callback(GLFWwindow* window)
{
    //body->toWorld=toWorldtrack;
    //glViewport(0, 0, 640, 480);
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glUseProgram(shaderProgram);
    //body->draw(shaderProgram);
    
    lprojection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
    lview = glm::lookAt(lid_pos, glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    space = lprojection*lview;
    
    glUseProgram(shader_s);
    
    glUniformMatrix4fv(glGetUniformLocation(shader_s, "space"), 1,GL_FALSE, &space[0][0]);
    ///
    glViewport(0, 0, 640, 480);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(shader_s);
    glm::mat4 model = glm::mat4(1.0f);
    // umodel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(glGetUniformLocation(shader_s, "model"), 1, GL_FALSE, &model[0][0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    
    //glBindVertexArray(baseVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    if(fun==1){
    c1->draw(shader_s);
    
    
    c2->draw(shader_s);
    c3->draw(shader_s);
    c4->draw(shader_s);
    c5->draw(shader_s);
    }
    
    if(blood != 1)
    {
        body->draw(shader_s);
    }
    
    glBindVertexArray(baseVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    ///
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // reset viewport
    glViewport(0, 0, 640, 480);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 2. render scene as normal using the generated depth/shadow map
    // --------------------------------------------------------------
    glViewport(0, 0, 640, 480);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    ////
    glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), cam_pos.x,cam_pos.y,cam_pos.z);
    glm::mat4 modelview = Window::V*body->toWorld;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &modelview[0][0]);
    glUniform3f(glGetUniformLocation(shaderProgram, "lid"), lid_pos.x,lid_pos.y, lid_pos.z);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "space"), 1,GL_FALSE, &space[0][0]);
    //
    /*glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, base);*/
    
    
    //glBindVertexArray(baseVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    if(blood != 1)
        body->draw(shaderProgram);

    if(fun==1){
    c1->draw(shaderProgram);
    
    
    c2->draw(shaderProgram);
    c3->draw(shaderProgram);
    c4->draw(shaderProgram);
    c5->draw(shaderProgram);
    }
    glBindVertexArray(baseVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    ///
    glUseProgram(pshader);
    if(translate_offset.x<=1.5&&translate_offset.x>=-1.5&&r==1)
    {
        blood = 1;
        part->draw(pshader);
    }
    glfwPollEvents();
    // Swap buffers
    glfwSwapBuffers(window);
}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        //wasd for moving
        if(key == GLFW_KEY_D)
        {

            if(translate_offset.z   +0.78*translate_offset.x>= -10.72&&translate_offset.z - 0.96*translate_offset.x <= 11.06)
            translate_offset.x-=0.5f;
            
            body->toWorld = glm::translate(glm::mat4(1.0f), translate_offset);
 
        }
        if (key==GLFW_KEY_A)
        {

            if(translate_offset.z - 0.958*translate_offset.x >= -12.45&&translate_offset.z +1.18*translate_offset.x <= 15.36)
            translate_offset.x+=0.5f;
            
            body->toWorld = glm::translate(glm::mat4(1.0f), translate_offset);

            
        }
        if(key == GLFW_KEY_S)
        {
            if(translate_offset.z   +0.78*translate_offset.x>= -10.72&&translate_offset.z - 0.958*translate_offset.x >= -12.45)
            translate_offset.z-=0.5f;
            
            body->toWorld = glm::translate(glm::mat4(1.0f), translate_offset);
            
        }
        if (key==GLFW_KEY_W)
        {
            if(translate_offset.z +1.18*translate_offset.x <= 15.36&&translate_offset.z - 0.96*translate_offset.x <= 11.06)
            translate_offset.z+=0.5f;
            
            body->toWorld = glm::translate(glm::mat4(1.0f), translate_offset);
            
            
        }
        //rotate the fun
        if (key==GLFW_KEY_R)
        {
            r = 1-r;
        }
        
        if (key==GLFW_KEY_1)
        {
            //normal coloring
            trackmode = 0;
            glUseProgram(shaderProgram);
            glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), trackmode);
        }
        if (key==GLFW_KEY_2)
        {
            //toon shading
            trackmode = 1;
            glUseProgram(shaderProgram);
            glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), trackmode);
        }
        if (key==GLFW_KEY_3)
        {
            //greyscale
            trackmode = 2;
            glUseProgram(shaderProgram);
            glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), trackmode);
        }
        if (key==GLFW_KEY_4)
        {
            //shadow mapping
            shadow_s = 1-shadow_s;
            //if(shadow_s==1){
                trackmode = 3;
                glUseProgram(shaderProgram);
                glUniform1f(glGetUniformLocation(shaderProgram, "material.shadow_s"), shadow_s);
           // }
           // else{
           //     glUseProgram(shaderProgram);
           //     glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), trackmode);
           // }
        }
        if (key==GLFW_KEY_Q)
        {
            //display the fun 
            fun = 1-fun;
        }
//        if (key==GLFW_KEY_Z)
//        {
//            glm::vec3 cam_pos(-0.0f, 0.0f, -8.0f);        // e  | Position of camera
//            glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);    // d  | This is where the camera looks at
//            glm::vec3 cam_up(0.0f, 1.0f, 0.0f);            // up | What orientation "up" is
//            P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
//            V = glm::lookAt(cam_pos, cam_look_at, cam_up);
//        }
    }
    
}
void Window::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    //on button down
    if (action == GLFW_PRESS)
    {
        if(button==GLFW_MOUSE_BUTTON_LEFT){
            double x,y;
            glfwGetCursorPos(window, &x, &y);
            std::cout<<"x and y "<<x<<" "<<y<<std::endl;
            
            //obj->moveLeft();
            Movement = 1;
            lastpoint = trackballmapping( glm::vec2(x,y) );
            
            
        }
        if(button==GLFW_MOUSE_BUTTON_RIGHT){
            
            move=0;
            double x,y;
            glfwGetCursorPos(window, &x, &y);
            xtrack = x;
            ytrack = y;
        }
        
        
    }
    if (action == GLFW_RELEASE){
        Movement = 0;
        move=0;
    }
}int count = 0;

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //count++;
    //std::cout<<"sagre"<<std::endl;
    if(Movement==1)
        Window::OnMouseMove(glm::vec2(xpos,ypos));
    if(move==1){
        //std::cerr << "!!!" << std::endl;
        /*
         translate_offset.x += (xpos-xtrack)/(640.0/30.0);
         translate_offset.y += -(ypos-ytrack) /24;
         
         glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3((xpos-xtrack)/(640.0/30.0), -(ypos-ytrack) /24, 0.0f));
         
         box->toWorld = T * box->toWorld;
         toWorldtrack = box->toWorld;
         xtrack = xpos;
         ytrack = ypos;*/
        
    }
    //std::cout<<"enter"<<count<<std::endl;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    /*glm::mat4 T_inverse = glm::translate(glm::mat4(1.0f), -translate_offset);
     
     glm::mat4 T_in = glm::translate(glm::mat4(1.0f), translate_offset);
     //std::cout<<(T_in).toString()<<std::endl;
     translate_offset.z += xoffset * 5;
     glm::mat4 T = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, xoffset * 5));
     //cube->toWorld = T_in*T * T_inverse*cube->toWorld;
     box->toWorld = T_in*T * T_inverse*box->toWorld;
     toWorldtrack = box->toWorld;*/
}

glm::vec3 Window::trackballmapping(glm::vec2 point){
    glm::vec3 v;
    float d;
    v.x = (2.0*point.x - width) / width;
    v.y = (height - 2.0*point.y) / height;
    v.z = 0.0;
    d = sqrtf(powf(v.x,2.0)+powf(v.y,2.0)+powf(v.z,2.0));
    d = (d<1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d*d);
    v=glm::normalize(v);
    return v;
    
}

//void Window::OnMouseMove()
void Window::OnMouseMove(glm::vec2 point)
{
    //glMatrixMode( GL_MODELVIEW );
    count++;
    glm::vec3 direction;
    float pixel_d;
    float rot_angle=0;//,zoom_factor;
    glm::vec3 curPoint;
    //int Movement = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    switch(Movement){
        case 0: break;
        case 1:
        {
            curPoint = trackballmapping(point);
            direction = glm::vec3((curPoint.x-lastpoint.x),(curPoint.y-lastpoint.y),(curPoint.z-lastpoint.z));
            //std::cout<<direction.x<<" and "<<direction.y<<std::endl;
            float velocity = sqrtf(powf(direction.x,2.0)+powf(direction.y,2.0)+powf(direction.z,2.0));
            //std::cout<<velocity<<"count"<<count<<std::endl;
            
            if(velocity>0.0001){
                glm::vec3 rotAxis;
                rotAxis = glm::cross(lastpoint, curPoint);
                rot_angle = velocity/180.0f*glm::pi<float>();//lllllllllllllllllllllllllllllll
                //obj->essential=glm::vec3(10,0,0);
                
                /* glm::mat3 R = glm::rotate(glm::vec3(1.0f), 2 * rot_angle, rotAxis);
                 
                 glm::mat3 T_inverse = glm::translate(glm::mat3(1.0f), -cam_pos);
                 glm::mat3 T = glm::translate(glm::mat3(1.0f), cam_pos);*/
                //cube->toWorld=T * R * T_inverse * box->toWorld;
                //box->toWorld = T * R * T_inverse * box->toWorld;
                cam_up =glm::rotate(cam_up, 2*rot_angle, rotAxis);
                cam_pos = glm::rotate(cam_pos, 2*rot_angle, rotAxis);
                if (height > 0)
                {
                    P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
                    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
                }
                //   toWorldtrack = box->toWorld;
                
            }
            break;
        }
            lastpoint = curPoint;
            //std::cout<<lastpoint<<curpoint<<std::endl;
            
    }
    // lastpoint = curPoint;
}

