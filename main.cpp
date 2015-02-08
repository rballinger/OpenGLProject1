/**
 *  Author: Ryan Ballinger      Date: 2-8-15
 *  Professor: Dulimarta        Project: Objects & Transformations
 *  File: main.cpp
 */

#include <iostream>
#include <cmath>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#undef GLFW_DLL
#include <GL/glfw3.h>

#include "ButterDish.h"
#include "Bread.h"
#include "Toaster.h"
#include "Butter.h"

#define BREAD_COUNT 12

using namespace std;

Toaster toaster;
ButterDish butterdish;
Butter big_butter;
Butter small_butterN;
Butter small_butterM;
vector<Bread> bread_objects;

bool wireframe;

void init_model();
void win_refresh(GLFWwindow*);

int screen_ctr_x, screen_ctr_y;

glm::mat4 camera_cf;
glm::mat4 camera_cf1;
glm::mat4 camera_cf2;
glm::mat4 camera_cf3;
glm::mat4 camera_cf4;
glm::mat4 toaster_cf;
glm::mat4 butterdish_cf;
glm::mat4 big_butter_cf;
glm::mat4 small_butterN_cf;
glm::mat4 small_butterM_cf;
vector <glm::mat4> bread_cfs;
glm::mat4 * selected_cf_p;

void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}

void win_resize (GLFWwindow * win, int width, int height)
{
#ifdef DEBUG
    cout << __FUNCTION__ << " " << width << "x" << height << endl;
#endif
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(90.0, static_cast<float> (width)/ static_cast<float> (height), 1, 40);
}

void make_model(){
    butterdish.build();
    toaster.build();
    big_butter.build();
    small_butterN.build();
    small_butterM.build();

    // setup coordinate frames for each object
    toaster_cf = glm::translate(glm::vec3{3, 5, 0});                    // translate 3 along x-axis and 5 along y-axis
    toaster_cf = toaster_cf * glm::rotate(0.52f, glm::vec3{0, 0, 1});   // rotate 30 deg around z-axis
    butterdish_cf = glm::translate(glm::vec3{-8,0,0});                  // translate -8 along x-axis
    butterdish_cf = butterdish_cf * glm::rotate(3.66f, glm::vec3{0, 0, 1}); // rotate 210 deg around z-axis
    big_butter_cf = butterdish_cf * glm::translate(glm::vec3{0,-1.0,0.75}); // translate -8 along x-axis, 1 along y-axis and 0.75 along z-axis
    small_butterN_cf = big_butter_cf * glm::translate(glm::vec3{0,3,0});
    small_butterM_cf = big_butter_cf * glm::translate(glm::vec3(0,4,0));

    // setup bread
    for(int i = 0; i < BREAD_COUNT; i++){
        Bread bread;
        bread_objects.push_back(bread);
        bread_objects[i].build();
        glm::mat4 bread_cf;
        bread_cf = toaster_cf * glm::translate(glm::vec3(i / 2.0f,-0.375 - i,3.25));
        bread_cf = bread_cf * glm::rotate(1.4f, glm::vec3{1,0,0});
        bread_cfs.push_back(bread_cf);
    }
}

void win_refresh (GLFWwindow *win) {
//    cout << __PRETTY_FUNCTION__ << endl;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));

    const float& S = 1;
    /* draw the axes */
//    glBegin(GL_LINES);
//    glColor3ub (255, 0, 0);
//    glVertex2i (0, 0);
//    glVertex2f (S * 1.1, 0);
//    glColor3ub (0, 255, 0);
//    glVertex2i (0, 0);
//    glVertex2f (0, S * 1.1);
//    glColor3ub (0, 0, 255);
//    glVertex2i (0, 0);
//    glVertex3f (0, 0, S * 1.1);
//    glEnd();

    // place toaster
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(toaster_cf));
    toaster.render(wireframe);
    glPopMatrix();
    // place butterdish
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(butterdish_cf));
    butterdish.render(wireframe);
    glPopMatrix();
    // place big block of butter
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(big_butter_cf));
    glScalef(3.0, 8.0, 4.0);
    big_butter.render(wireframe);
    glPopMatrix();
    // place first small block of butter
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(small_butterN_cf));
    glRotatef(-25.0f, 1, 0, 0);
    glScalef(3.0, 1.5, 4.0);
    small_butterN.render(wireframe);
    glPopMatrix();
    // place second small block of butter
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(small_butterM_cf));
    glRotatef(-55.0f, 1, 0, 0);
    glScalef(3.0, 1.5, 4.0);
    small_butterM.render(wireframe);
    glPopMatrix();
    // place all the bread
    for(int i = 0; i < BREAD_COUNT; i++){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(bread_cfs[i]));
        bread_objects[i].render(wireframe);
        glPopMatrix();
    }

    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

/* action: GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT */
void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods)
{
    if(selected_cf_p == NULL){
        selected_cf_p = &toaster_cf;
    }
    cout << __FUNCTION__ << endl;
    if (action != GLFW_PRESS) return;
    if (mods == GLFW_MOD_SHIFT) {
        switch (key) {
            case GLFW_KEY_LEFT:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{-1, 0, 0});
                break;
            case GLFW_KEY_RIGHT:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{1, 0, 0});
                break;
            case GLFW_KEY_DOWN:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{0, -1, 0});
                break;
            case GLFW_KEY_UP:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{0, 1, 0});
                break;
            case GLFW_KEY_PERIOD:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{0, 0, -1});
                break;
            case GLFW_KEY_SLASH:
                *selected_cf_p = (*selected_cf_p) * glm::rotate(0.1f, glm::vec3{0, 0, 1});
                break;
        }
    }
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(win, true);
                break;
            case GLFW_KEY_Z:
                camera_cf = camera_cf1;
                break;
            case GLFW_KEY_X:
                camera_cf = camera_cf2;
                break;
            case GLFW_KEY_C:
                camera_cf = camera_cf3;
                break;
            case GLFW_KEY_V:
                camera_cf = camera_cf4;
                break;
            case GLFW_KEY_W:
                wireframe = !wireframe;
                break;
            case GLFW_KEY_T:
                selected_cf_p = &toaster_cf;
                break;
            case GLFW_KEY_D:
                selected_cf_p = &butterdish_cf;
                break;
            case GLFW_KEY_B:
                selected_cf_p = &big_butter_cf;
                break;
            case GLFW_KEY_N:
                selected_cf_p = &small_butterN_cf;
                break;
            case GLFW_KEY_M:
                selected_cf_p = &small_butterM_cf;
                break;
            case GLFW_KEY_F1:
                selected_cf_p = &(bread_cfs[0]);
                break;
            case GLFW_KEY_F2:
                selected_cf_p = &(bread_cfs[1]);
                break;
            case GLFW_KEY_F3:
                selected_cf_p = &(bread_cfs[2]);
                break;
            case GLFW_KEY_F4:
                selected_cf_p = &(bread_cfs[3]);
                break;
            case GLFW_KEY_F5:
                selected_cf_p = &(bread_cfs[4]);
                break;
            case GLFW_KEY_F6:
                selected_cf_p = &(bread_cfs[5]);
                break;
            case GLFW_KEY_F7:
                selected_cf_p = &(bread_cfs[6]);
                break;
            case GLFW_KEY_F8:
                selected_cf_p = &(bread_cfs[7]);
                break;
            case GLFW_KEY_F9:
                selected_cf_p = &(bread_cfs[8]);
                break;
            case GLFW_KEY_F10:
                selected_cf_p = &(bread_cfs[9]);
                break;
            case GLFW_KEY_F11:
                selected_cf_p = &(bread_cfs[10]);
                break;
            case GLFW_KEY_F12:
                selected_cf_p = &(bread_cfs[11]);
                break;
            case GLFW_KEY_LEFT:
                *selected_cf_p = glm::translate(glm::vec3{-0.2f, 0, 0}) * (*selected_cf_p);
                break;
            case GLFW_KEY_RIGHT:
                *selected_cf_p = glm::translate(glm::vec3{0.2f, 0, 0}) * (*selected_cf_p);
                break;
            case GLFW_KEY_DOWN:
                *selected_cf_p = glm::translate(glm::vec3{0, -0.2f, 0}) * (*selected_cf_p);
                break;
            case GLFW_KEY_UP:
                *selected_cf_p = glm::translate(glm::vec3{0, 0.2f, 0}) * (*selected_cf_p);
                break;
            case GLFW_KEY_PERIOD:
                *selected_cf_p = glm::translate(glm::vec3{0, 0, -0.2f}) * (*selected_cf_p);
                break;
            case GLFW_KEY_SLASH:
                *selected_cf_p = glm::translate(glm::vec3{0, 0, 0.2f}) * (*selected_cf_p);
                break;
        }
    }
    win_refresh(win);
}

void init_gl() {
    glEnable (GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_CULL_FACE);
    glLineWidth(2.0);

    /* initialize camera angles (note opposite values) */
    camera_cf1 *= glm::translate(glm::vec3{-4, -3, -15});
    camera_cf1 *= glm::rotate(-0.523f, glm::vec3{1,0,0});
    camera_cf2 *= glm::translate(glm::vec3{6, 3, -8});
    camera_cf2 *= glm::rotate(-0.7f, glm::vec3{1,0,0});
    camera_cf2 *= glm::rotate(0.3f, glm::vec3{0,0,1});
    camera_cf3 *= glm::translate(glm::vec3{4, 0, -18});
    camera_cf3 *= glm::rotate(3.8f, glm::vec3{0,0,1});
    camera_cf3 *= glm::rotate(0.5f, glm::vec3{1,0,0});
    camera_cf4 *= glm::translate(glm::vec3{-2, -3, -11});
    camera_cf4 *= glm::rotate(-2.5f, glm::vec3{1,0,0});
    camera_cf = camera_cf1;
}

int main() {
    wireframe = false;
    cout << "Hello" << endl;

    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "Test", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }

    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    // glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwMakeContextCurrent(win);

    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }

    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);

    glfwSetWindowSize(win, 450, 300);
    glfwSwapInterval(1);
    init_gl();
    make_model();

    win_refresh(win);
    while (!glfwWindowShouldClose(win)) {
        glfwWaitEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
