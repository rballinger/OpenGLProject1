#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#endif
#include <vector>
#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
using namespace std;

#ifndef BufferObject_H
#define BufferObject_H
class BufferObject {
protected:
    GLuint vertex_buffer, color_buffer, index_buffer;
    std::vector <glm::vec3> all_points, all_colors;
    vector<GLushort> all_index;
private:
    bool build_complete;
public:
    BufferObject() {
        vertex_buffer = color_buffer = index_buffer = 0;
        build_complete = false;
    }

    ~BufferObject() {
#if 0
        if (glIsBuffer(vertex_buffer))
            glDeleteBuffers(1, &vertex_buffer);
        if (glIsBuffer(color_buffer))
            glDeleteBuffers(1, &color_buffer);
        if (glIsBuffer(index_buffer))
            glDeleteBuffers(1, &index_buffer);
#endif
    }

    void post_build() {
        build_complete = true;
    }

    virtual void build(void *data) = 0;

    virtual void render(bool draw_outline) const = 0;
};
#endif
