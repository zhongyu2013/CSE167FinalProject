#include "OBJObject.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include "Window.h"
#include "glm/ext.hpp"
glm::vec3 objcenter;
//cutoff = 12.5f;

OBJObject::OBJObject(const char *filepath, float d)
{
    cutoff = 12.5f;
    outer = 13.5f;
    rot = glm::vec3(0.0,-1.0,0.0);
    mov=d;
    this->essential = glm::vec3(d,0.0f,0.0f);
    toWorld = glm::translate(glm::mat4(1.0f), essential);
    scale = glm::vec3(1.0f);
    parse(filepath);
    this->angle=0.0f;
    deg = 0.0f;
    toWorld = glm::mat4(1.0f);
    
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind fucking all in one vao
    glBindVertexArray(VAO);
    //normal,color vert
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, 2*sizeof(glm::vec3)*vertices.size(), gvertices, GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          6 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);
    /*glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);*/
    //glUseProgram(shaderprogram)
    // We've sent the vertex data over to OpenGL, but there's still something missing.
    // In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*indices.size(), gindices, GL_STATIC_DRAW);
    
    
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
}
OBJObject::~OBJObject()
{
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteBuffers(1, &colorbuffer);
}
void OBJObject::parse(const char *filepath)
{
    float xmin=std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::min();
    float ymin = std::numeric_limits<float>::max();
    float ymax =std::numeric_limits<float>::min();
    float zmin = std::numeric_limits<float>::max();
    float zmax = std::numeric_limits<float>::min();
    int count = 0;
    //TODO parse the OBJ file
    // Populate the face indices, vertices, and normals vectors with the OBJ Object data
    FILE * fp;
    float x,y,z;
    float r,g,b;
    float n1, n2, n3;
    int c1,c2;
    unsigned int f1,f2,f3,f4,f5,f6;
    //std::cout<<filepath<<std::endl;
    fp = fopen(filepath,"rb");
    if(fp==NULL){
        std::cerr<<"error load file"<<std::endl;
        exit (-1);
    }
    while(true){
        if(feof(fp)) break;
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if(c1=='v'&&c2==' '){
            fscanf(fp,"%f %f %f %f %f %f",&x, &y, &z, &r, &g, &b);
            if(x<xmin)
                xmin = x;
            if(x>xmax)
                xmax = x;
            if(y<ymin){
                ymin = y;
            }
            if(y>ymax){
                ymax = y;
            }
            if(z>zmax){
                zmax = z;
            }
            if(z<zmin){
                zmin = z;
            }
            
            vertices.push_back(glm::vec3(x,y,z));
            vertices_prime.push_back(glm::vec4(0));
            //std::cout<<"varray x y z "<<x<<" " <<y<<" "<<z<<std::endl;
        }
        if(c1=='v'&&c2=='n'){
            fscanf(fp,"%f %f %f", &n1,&n2,&n3);
            //std::cout<<n1<<" "<<n2<<" "<<n3<<std::endl;
            normals.push_back(glm::vec3(n1,n2,n3));
        }
        
        if(c1=='f'&&c2==' '){
            count++;
            fscanf(fp, "%u//%u %u//%u %u//%u",&f1, &f2, &f3, &f4, &f5, &f6 );
            //std::cout<<f1<<" "<<f2<<" "<<f3<<std::endl;
            indices.push_back(f1-1);
            indices.push_back(f3-1);
            indices.push_back(f5-1);
        }
        if(c1=='#'||c1==' '){
            int c3 = fgetc(fp);
        }
    }
    float rmax = 0;
    float ratio = 0;
    float xmid = (xmax+xmin)/2;
    float ymid = (ymax+ymin)/2;
    float zmid = (zmax+zmin)/2;
    objcenter = glm::vec3(-xmid,-ymid,-zmid);//sub
    //this->essential = objcenter;
    for(unsigned int n = 0;n<vertices.size();n++){
        vertices[n].x = vertices[n].x-xmid;
        vertices[n].y = vertices[n].y-ymid;
        vertices[n].z = vertices[n].z-zmid;
        
    }
    float yrange = ymax-ymin;
    float xrange = xmax-xmin;
    float zrange = zmax-zmin;
    float rarray[] = {yrange,xrange,zrange};
    for(unsigned int index = 0;index<3;index++){
        if(rarray[index]>rmax)
            rmax=rarray[index];
    }
    if(rmax>2){
        ratio = rmax/2;
    }
    else{
        ratio = 1;
    }
    GLuint* iarray = new GLuint[indices.size()];
    for(unsigned int i = 0;i<indices.size();i++){
        iarray[i]=indices[i];
        //std::cout<<indices[i]<<std::endl;
    }
    
    gindices=iarray;
    //GLfloat varray [3*vertices.size()];
    //std::cout<<varray)<<std::endl;
    for(unsigned int j = 0;j<vertices.size();j++){
        
        vertices[j].x=vertices[j].x/ratio;
        vertices[j].y=vertices[j].y/ratio;
        vertices[j].z=vertices[j].z/ratio;
    }
    std::cout<<"v size is "<<vertices.size()<<std::endl;
    

    std::cout<<normals.size()<<" and "<<vertices.size()<<std::endl;
    GLfloat * varray = new GLfloat[6*vertices.size()];
    for(unsigned int k = 0;k<vertices.size();k++){
        
        varray[6*k]=vertices[k].x;
        
        varray[6*k+1]=vertices[k].y;
        
        varray[6*k+2]=vertices[k].z;

        varray[6*k+3]=normals[k].x;
        
        varray[6*k+4]=normals[k].y;
        
        varray[6*k+5]=normals[k].z;
        
        //std::cout<<varray[k]<<std::endl;
    }
    gvertices=varray;
    //this->essential = objcenter;
    
    fclose(fp);
}

void OBJObject::update()
{
    //spin(4.0f);
}

void OBJObject::spin(float deg)
{
    //deg = deg+deg;
    this->angle += deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    this->toWorld = glm::translate(glm::mat4(1.0f), essential);
    this->toWorld = glm::scale(this->toWorld, scale);
    
}
void OBJObject::update0()
{
    spin0(4.0f);
}

void OBJObject::spin0(float deg)
{
    
    // This creates the matrix to rotate the cube
    //this->toWorld = glm::translate(glm::mat4(1.0f), essential);
    this->toWorld = glm::scale(this->toWorld, scale);
    //this->toWorld = glm::rotate(this->toWorld, this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void OBJObject::draw(GLuint shaderProgram)
{
    glm::vec3 pointLightColors[] = {
        glm::vec3(1.0f, 0.6f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0, 0.0),
        glm::vec3(0.2f, 0.2f, 1.0f)
    };
    
    glm::mat4 modelview = Window::V * toWorld;
    
    //std::cerr << to_string(toWorld) << std::endl;
    
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    //glUniform1f(glGetUniformLocation(shaderProgram, "material.flag"), 1);
    deg+=4.0f;
    if (deg > 360.0f || deg < -360.0f) deg = 0.0f;
    rot=glm::vec3(0.0,-1.0,0.0);
    rot = glm::rotate(rot, deg/ 180.0f * glm::pi<float>(), glm::vec3(0.0,0.0,1.0));
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.direction"), rot.x,rot.y,rot.z);
    //rot = glm::rotate(rot, 4.0f, glm::vec3(0.0,0.0,1.0));
    
    

    glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), 0.0f, 0.0f, 20.0f);
    

    
    //glUniform3f(glGetUniformLocation(shaderProgram, "lid"), 1.0,0.0,0.0);
    umodel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(umodel, 1, GL_FALSE, &toWorld[0][0]);
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0,25);
    glBindVertexArray(0);
    
}
void OBJObject::larger(){
    GLfloat size;
    glGetFloatv(GL_POINT_SIZE, &size);
    size = size+0.2f;
    glPointSize(size);
}
void OBJObject::smaller(){
    GLfloat size;
    glGetFloatv(GL_POINT_SIZE, &size);
    size=size-0.2f;
    glPointSize(size);
    //this->toWorld = glm::mat4(1.0f);
}
void OBJObject::moveLeft(){
    
    this->essential.x-=0.1f;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::moveRight(){
    
    this->essential.x+=0.1f;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::moveDown(){
    
    this->essential.y--;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::moveUp(){
    
    this->essential.y++;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::moveOut(){
    
    this->essential.z++;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::moveIn(){
    
    this->essential.z--;
    
    //this->toWorld = glm::translate(this->toWorld, glm::vec3(1.0f,0.0f,0.0f));
}
void OBJObject::scaleDown(){
    if(scale.x>0||scale.y>0||scale.z>0){
        scale.x-=0.2f;
        scale.y-=0.2f;
        scale.z-=0.2f;
    }
    
}
void OBJObject::scaleUp(){
    // if(scale.x>0||scale.y>0||scale.z>0){
    scale.x+=0.2f;
    scale.y+=0.2f;
    scale.z+=0.2f;
    
}
void OBJObject::RESET(){
    
    this->scale = glm::vec3(1.0f);
    angle=0;//check
}

void OBJObject::reset(){
    this->essential = glm::vec3(mov,0.0f,0.0f);
}

