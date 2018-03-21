/*#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>*/


#ifndef _OBJOBJECT_H_
#define _OBJOBJECT_H_

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
//#include "Node.hpp"
class OBJObject /*: public Node*/
{
private:
    std::vector<GLuint> indices;
    GLuint* gindices;
    GLfloat * col;
    std::vector<glm::vec3> vertices;
    GLfloat* gvertices;
    std::vector<glm::vec4> vertices_prime;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vindex;
    std::vector<glm::vec3> vnindex;
    //glm::mat4 toWorld;
    //glm::vec3 essential;
    float mov;
    //glm::vec3 scale;
    float * pixels;
    int psize;
    float* zbuffer;
    
    // std::vector<>
public:
    glm::vec3 rot;
    float deg;
    //glm::vec3 rot;
    float cutoff;
    float outer;
    glm::mat4 toWorld;
    glm::vec3 scale;
    glm::vec3 essential;
    GLuint VBO, VAO, EBO;
    GLuint uProjection, uModelview,umodel;
    GLuint colorbuffer;
    OBJObject(const char* filepath,float);
    ~OBJObject();
    void update();
    void spin(float);
    void update0();
    void spin0(float);
    void parse(const char* filepath);
    void draw(GLuint);
    float angle;
    void larger();
    void smaller();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void moveOut();
    void moveIn();
    void reset();
    void RESET();
    void mreset();
    void scaleDown();
    void scaleUp();
    void loadData();
    void drawPoint(int x, int y,float z, float r, float g, float b);
    void rasterize();
    float * getPixels();
    void mLarger();
    void mSmaller();
    void setZbuffer();
};

#endif

