#ifndef GLMAIN_H
#define GLMAIN_H

#include <QGLApp.hpp>
#include <chrono>

// Also does not belong here
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 


class GLMain : public QGLApp
{
    Q_OBJECT

public:
    GLMain(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    void idleGL();
    float getDT();

    static const GLuint V_POSITION = 1;
    static const GLuint V_COLOR = 2;
    static const GLuint M_POSITION = 1;
    static const GLuint DEFAULT_BLOCK = 0;

    // Does not belong here
    const float FOV = 45.0f; // half-angle FOV
    const float sensor_distance = 0.01f;
    const float focal_distance = 100.0f;

    GLuint vbo_geometry;
    float angle;
   
    //transform matrices
    glm::mat4 model;//obj->world each object should have its own model matrix
    glm::mat4 view;//world->eye
    glm::mat4 projection;//eye->clip
    glm::mat4 mvp;//premultiplied modelviewprojection
    std::chrono::time_point<std::chrono::high_resolution_clock> time;


};

#endif 

