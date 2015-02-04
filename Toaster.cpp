#include <cmath>
#include "Toaster.h"
#define M_PI           3.14159265358979323846

using glm::vec3;

void Toaster::build(void* data){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2, c1, c2, c3, c4;

    // build bread

    // bread bottom square
    c1 = {-TOASTER_LENGTH / 2, 0, TOASTER_HEIGHT};
    c2 = {TOASTER_LENGTH / 2, 0, TOASTER_HEIGHT};
    c3 = {-TOASTER_LENGTH / 2, 0, 0};
    c4 = {TOASTER_LENGTH / 2, 0, 0};
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    all_index.push_back(all_points.size());
    all_points.push_back(c3);

    for(int i = 1; i < SUBDIV_TLENGTH; i++){
        float t = (float) i / SUBDIV_TLENGTH;
        v1 = {t * c2 + (1 - t) * c1};
        v2 = {t * c4 + (1 - t) * c3};
        if(i != 1 && i != (SUBDIV_TLENGTH - 1)){
            v2.z += LEG_HEIGHT;
        }
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
        all_index.push_back(all_points.size());
        all_points.push_back(v2);
    }

    all_index.push_back(all_points.size());
    all_points.push_back(c2);
    all_index.push_back(all_points.size());
    all_points.push_back(c4);

    side_count = all_index.size();

    for(auto v : all_points){
        v.y += TOASTER_WIDTH;
        all_index.push_back(all_points.size());
        all_points.push_back(v);
    }

    total_count = all_index.size();

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Toaster::render(bool outline) const{
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
//    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
//    glColorPointer(3, GL_FLOAT, 0, 0);v1 = {TOP_WIDTH/2, -TOP_LENGTH/2, HEIGHT/2};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    // set mode
    if(outline){
        glPolygonMode(GL_FRONT, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT, GL_FILL);
    }

    // front side
    glFrontFace(GL_CCW);
    glColor3ub (255, 255, 255);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, side_count, GL_UNSIGNED_SHORT, 0);

    // back side
    glFrontFace(GL_CW);
    glColor3ub (255, 255, 255);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, side_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * side_count));

    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
