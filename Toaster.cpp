#include <cmath>
#include "Toaster.h"
#define M_PI           3.14159265358979323846

using glm::vec3;

void Toaster::build(){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2, c1, c2, c3, c4;

    // build toaster

    // toaster front side
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

    // toaster back side
    for(auto v : all_points){
        v.y += TOASTER_WIDTH;
        all_index.push_back(all_points.size());
        all_points.push_back(v);
    }

    before_bottom_count = all_index.size();
    // toaster bottom
    int odd;
    for(int i = 0; i < side_count; i++){
        odd = 2 * i + 1;
        all_index.push_back(odd);
        all_index.push_back(odd + side_count);
    }

    before_left_top_count = all_index.size();
    // left round top side
    c1.y += TOASTER_WIDTH / 2;  // center of triangle fan
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    all_index.push_back(side_count);
    float newX, newY;
    for(int i = SUBDIV_MAJ_RAD - 1; i > 0; i--){
        newY = c1.y + SUBDIV_MAJ_RAD_AMT * i;
        newX = c1.x - sqrt((1 - (pow(SUBDIV_MAJ_RAD_AMT * i, 2) / pow(TOASTER_MAJ_RAD, 2))) * pow(TOASTER_MIN_RAD, 2));
        v1 = {newX, newY, c1.z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
    }
    for(int i = 0; i < SUBDIV_MAJ_RAD; i++){
        newY = c1.y - SUBDIV_MAJ_RAD_AMT * i;
        newX = c1.x - sqrt((1 - (pow(SUBDIV_MAJ_RAD_AMT * i, 2) / pow(TOASTER_MAJ_RAD, 2))) * pow(TOASTER_MIN_RAD, 2));
        v1 = {newX, newY, c1.z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
    }
    all_index.push_back(0);
    c1.y -= TOASTER_WIDTH / 2;

    round_points = all_index.size() - before_left_top_count;

    before_right_top_count = all_index.size();
    // right round top side
    c2.y += TOASTER_WIDTH / 2;  // center of triangle fan
    all_index.push_back(all_points.size());
    all_points.push_back(c2);
    all_index.push_back(side_count * 2 - 2);
    for(int i = SUBDIV_MAJ_RAD - 1; i > 0; i--){
        newY = c2.y + SUBDIV_MAJ_RAD_AMT * i;
        newX = c2.x + sqrt((1 - (pow(SUBDIV_MAJ_RAD_AMT * i, 2) / pow(TOASTER_MAJ_RAD, 2))) * pow(TOASTER_MIN_RAD, 2));
        v1 = {newX, newY, c2.z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
    }
    for(int i = 0; i < SUBDIV_MAJ_RAD; i++){
        newY = c2.y - SUBDIV_MAJ_RAD_AMT * i;
        newX = c2.x + sqrt((1 - (pow(SUBDIV_MAJ_RAD_AMT * i, 2) / pow(TOASTER_MAJ_RAD, 2))) * pow(TOASTER_MIN_RAD, 2));
        v1 = {newX, newY, c2.z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
    }
    all_index.push_back(side_count - 2);
    c2.y -= TOASTER_WIDTH / 2;

    before_round_bottom_count = all_index.size();
    // bottom of round sides
    for(int i = before_left_top_count; i < before_round_bottom_count; i++){
        v1 = all_points[all_index[i]];
        v1.z -= TOASTER_HEIGHT;
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
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

    // bottom side
    glFrontFace(GL_CCW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_bottom_count));
    glColor3ub (175, 175, 175);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_bottom_count + 2)));
    glColor3ub (150, 150, 150);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, side_count - 8, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_bottom_count + 4)));
    glColor3ub (175, 175, 175);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_bottom_count + side_count - 6)));
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_bottom_count + side_count - 4)));

    // left round top
    glFrontFace(GL_CCW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_TRIANGLE_FAN, 0, 0, round_points, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_left_top_count));
    // right round top
    glFrontFace(GL_CW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_TRIANGLE_FAN, 0, 0, round_points, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_right_top_count));

    // left round bottom
    glFrontFace(GL_CW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_TRIANGLE_FAN, 0, 0, round_points, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_round_bottom_count));
    // right round bottom
    glFrontFace(GL_CCW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(GL_TRIANGLE_FAN, 0, 0, round_points, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_round_bottom_count + round_points)));

    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
