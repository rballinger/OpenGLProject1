/**
 *  Author: Ryan Ballinger      Date: 2-8-15
 *  Professor: Dulimarta        Project: Objects & Transformations
 *  File: Toaster.cpp
 */

#include <cmath>
#include "Toaster.h"
#define M_PI           3.14159265358979323846

using glm::vec3;

void Toaster::build(){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2, v3, v4, c1, c2, c3, c4, top, bottom, left, right;

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
    for(int i = 0; i < side_count / 2; i++){
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
        if(i == before_left_top_count + 1){
            all_index.push_back(1 + side_count);
        }else if(i == before_left_top_count + round_points - 1){
            all_index.push_back(1);
        }else if(i == before_right_top_count + 1){
            all_index.push_back(side_count * 2 - 1);
        }else if(i == before_right_top_count + round_points - 1){
            all_index.push_back(side_count - 1);
        }else{
            v1 = all_points[all_index[i]];
            v1.z -= TOASTER_HEIGHT;
            all_index.push_back(all_points.size());
            all_points.push_back(v1);
        }
    }

    before_left_wall_count = all_index.size();
    //    left wall
    for(int i = before_left_top_count + 1; i < before_round_bottom_count - round_points; i++){
        all_index.push_back(all_index[i]);
        all_index.push_back(all_index[i + round_points * 2]);
    }

    before_right_wall_count = all_index.size();
    // right wall
    for(int i = before_left_top_count + round_points + 1; i < before_round_bottom_count; i++){
        all_index.push_back(all_index[i]);
        all_index.push_back(all_index[i + round_points * 2]);
    }

    before_top_count = all_index.size();
    // top
    int start = 0;
    int p_end = SLOT_FROM_LEFT / SUBDIV_AMT;
    int even;
    for(int i = 0; i <= p_end; i++){
        even = 2 * i;
        all_index.push_back(even);
        all_index.push_back(even + side_count);
    }

    before_top_slots_count = all_index.size();
    // top of slots
    start_slot_points = all_points.size();
    start = p_end;
    p_end += SLOT_LENGTH / SUBDIV_AMT;
    for(int i = start; i <= p_end; i++){
        even = 2 * i;
        v1 = all_points[all_index[even]];
        v1.y += SLOT_FROM_FRONT;
        all_points.push_back(v1);
        v1.y += SLOT_WIDTH;
        all_points.push_back(v1);
        v1.y += SLOT_SEPARATION;
        all_points.push_back(v1);
        v1.y += SLOT_WIDTH;
        all_points.push_back(v1);
    }

    end_slot_points = all_points.size();

    int j = 0;
    for(int i = start; i < p_end; i++){
        even = 2 * i;
        all_index.push_back(even);
        all_index.push_back(even + 2);
        all_index.push_back(4 + j + start_slot_points);
        all_index.push_back(0 + j + start_slot_points);
        all_index.push_back(1 + j + start_slot_points);
        all_index.push_back(5 + j + start_slot_points);
        all_index.push_back(6 + j + start_slot_points);
        all_index.push_back(2 + j + start_slot_points);
        all_index.push_back(3 + j + start_slot_points);
        all_index.push_back(7 + j + start_slot_points);
        all_index.push_back(even + side_count + 2);
        all_index.push_back(even + side_count);
        j += 4;
    }

    before_end_top_count = all_index.size();
    // finish top
    start = p_end;
    p_end = start + SLOT_FROM_RIGHT / SUBDIV_AMT;
    for(int i = start; i <= p_end; i++){
        even = 2 * i;
        all_index.push_back(even);
        all_index.push_back(even + side_count);
    }

    before_slots_bottom_count = all_index.size();
    // slot bottoms
    v1 = all_points[start_slot_points];
    v1.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v2 = all_points[start_slot_points + 1];
    v2.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    v3 = all_points[end_slot_points - 3];
    v3.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(v3);
    v4 = all_points[end_slot_points - 4];
    v4.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(v4);

    c1 = all_points[start_slot_points + 2];
    c1.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    c2 = all_points[start_slot_points + 3];
    c2.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(c2);
    c3 = all_points[end_slot_points - 1];
    c3.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(c3);
    c4 = all_points[end_slot_points - 2];
    c4.z -= SLOT_DEPTH;
    all_index.push_back(all_points.size());
    all_points.push_back(c4);

    before_front_slot_count = all_index.size();
    // front slot
    all_index.push_back(all_index[before_top_slots_count + 3]);
    all_index.push_back(all_index[before_slots_bottom_count]);
    all_index.push_back(all_index[before_top_slots_count + 4]);
    all_index.push_back(all_index[before_slots_bottom_count + 1]);
    all_index.push_back(all_index[before_end_top_count - 7]);
    all_index.push_back(all_index[before_slots_bottom_count + 2]);
    all_index.push_back(all_index[before_end_top_count - 10]);
    all_index.push_back(all_index[before_slots_bottom_count + 3]);
    all_index.push_back(all_index[before_top_slots_count + 3]);
    all_index.push_back(all_index[before_slots_bottom_count]);

    before_back_slot_count = all_index.size();
    // back slot
    all_index.push_back(all_index[before_top_slots_count + 7]);
    all_index.push_back(all_index[before_slots_bottom_count + 4]);
    all_index.push_back(all_index[before_top_slots_count + 8]);
    all_index.push_back(all_index[before_slots_bottom_count + 5]);
    all_index.push_back(all_index[before_end_top_count - 3]);
    all_index.push_back(all_index[before_slots_bottom_count + 6]);
    all_index.push_back(all_index[before_end_top_count - 6]);
    all_index.push_back(all_index[before_slots_bottom_count + 7]);
    all_index.push_back(all_index[before_top_slots_count + 7]);
    all_index.push_back(all_index[before_slots_bottom_count + 4]);

    before_grate_count = all_index.size();
    // grates
    bottom = {v1.x + GRATE_FROM_SIDE, v1.y + GRATE_FROM_FRONT, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(bottom);
    top = {bottom.x, bottom.y, bottom.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(top);
    left = {v1.x, v1.y + GRATE_FROM_FRONT, v1.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(left);
    right = {left.x + SLOT_LENGTH, left.y, left.z};
    all_index.push_back(all_points.size());
    all_points.push_back(right);
    for(int i = 0; i < NUM_OF_GRATES; i++){
        // vertical bars
        bottom.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(bottom);
        top.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(top);
    }

    bottom = {v2.x + GRATE_FROM_SIDE, v2.y - GRATE_FROM_FRONT, v2.z};
    all_index.push_back(all_points.size());
    all_points.push_back(bottom);
    top = {bottom.x, bottom.y, bottom.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(top);
    left = {v2.x, v2.y - GRATE_FROM_FRONT, v2.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(left);
    right = {left.x + SLOT_LENGTH, left.y, left.z};
    all_index.push_back(all_points.size());
    all_points.push_back(right);
    for(int i = 0; i < NUM_OF_GRATES; i++){
        // vertical bars
        bottom.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(bottom);
        top.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(top);
    }

    bottom = {c1.x + GRATE_FROM_SIDE, c1.y + GRATE_FROM_FRONT, c1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(bottom);
    top = {bottom.x, bottom.y, bottom.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(top);
    left = {c1.x, c1.y + GRATE_FROM_FRONT, c1.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(left);
    right = {left.x + SLOT_LENGTH, left.y, left.z};
    all_index.push_back(all_points.size());
    all_points.push_back(right);
    for(int i = 0; i < NUM_OF_GRATES; i++){
        // vertical bars
        bottom.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(bottom);
        top.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(top);
    }

    bottom = {c2.x + GRATE_FROM_SIDE, c2.y - GRATE_FROM_FRONT, c2.z};
    all_index.push_back(all_points.size());
    all_points.push_back(bottom);
    top = {bottom.x, bottom.y, bottom.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(top);
    left = {c2.x, c2.y - GRATE_FROM_FRONT, c2.z + GRATE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(left);
    right = {left.x + SLOT_LENGTH, left.y, left.z};
    all_index.push_back(all_points.size());
    all_points.push_back(right);
    for(int i = 0; i < NUM_OF_GRATES; i++){
        // vertical bars
        bottom.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(bottom);
        top.x += GRATE_HORIZ_SEP;
        all_index.push_back(all_points.size());
        all_points.push_back(top);
    }
    grate_points = all_index.size() - before_grate_count;

    before_handle_count = all_index.size();
    // handle
    v1 = all_points[all_index[1]];
    v1.y += (TOASTER_WIDTH / 2 - HANDLE_WIDTH / 2);
    v1.z += HANDLE_FROM_GROUND;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v2 = {v1.x, v1.y + HANDLE_WIDTH, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    v3 = {v1.x - HANDLE_LENGTH, v1.y, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v3);
    v4 = {v2.x - HANDLE_LENGTH, v2.y, v2.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v4);
    c1 = {v1.x, v1.y, v1.z - HANDLE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    c2 = {v2.x, v2.y, v2.z - HANDLE_HEIGHT};
    all_index.push_back(all_points.size());
    all_points.push_back(c2);

    for(int i = 0; i < 2; i++){
        all_index.push_back(all_index[before_handle_count + i]);
        all_index.push_back(all_index[before_handle_count + 2 + i]);
        all_index.push_back(all_index[before_handle_count + 4 + i]);
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
    glColor3ub (245, 245, 245);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, side_count, GL_UNSIGNED_SHORT, 0);

    // back side
    glFrontFace(GL_CW);
    glColor3ub (245, 245, 245);
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

    // left round wall
    glFrontFace(GL_CCW);
    glColor3ub (225, 225, 225);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, round_points * 2 - 2, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_left_wall_count));
    // right round wall
    glFrontFace(GL_CW);
    glColor3ub (225, 225, 225);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, round_points * 2 - 2, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_right_wall_count));

    // top
    glFrontFace(GL_CW);
    glColor3ub(200, 200, 200);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, (SLOT_FROM_LEFT / SUBDIV_AMT + 1) * 2, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_top_count));
    // room for slots
    glFrontFace(GL_CCW);
    glColor3ub(200, 200, 200);
    glDrawRangeElements(GL_QUADS, 0, 0, (2 * SLOT_LENGTH / SUBDIV_AMT) * 6 , GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_top_slots_count));
    // finish top
    glFrontFace(GL_CW);
    glColor3ub(200, 200, 200);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, (SLOT_FROM_RIGHT / SUBDIV_AMT + 1) * 2, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_end_top_count));

    // slots bottom
    glFrontFace(GL_CW);
    glColor3ub(170, 170, 170);
    glDrawRangeElements(GL_QUADS, 0, 0, 8, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_slots_bottom_count));

    // front slot sides
    glFrontFace(GL_CCW);
    glColor3ub(150, 150, 150);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_front_slot_count));
    glColor3ub(130, 130, 130);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_front_slot_count + 2)));
    glColor3ub(110, 110, 110);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_front_slot_count + 4)));
    glColor3ub(90, 90, 90);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_front_slot_count + 6)));

    // back slot sides
    glFrontFace(GL_CCW);
    glColor3ub(150, 150, 150);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_back_slot_count));
    glColor3ub(130, 130, 130);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_back_slot_count + 2)));
    glColor3ub(110, 110, 110);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_back_slot_count + 4)));
    glColor3ub(90, 90, 90);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_back_slot_count + 6)));

    // grates
    glFrontFace(GL_CCW);
    glColor3ub(50, 50, 50);
    glDrawRangeElements(GL_LINES, 0, 0, grate_points, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_grate_count));

    // handle
    glFrontFace(GL_CCW);
    glColor3ub (135, 135, 135);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_handle_count));
    glFrontFace(GL_CCW);
    glColor3ub (110, 110, 110);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_handle_count + 2)));
    glFrontFace(GL_CCW);
    glColor3ub (160, 160, 160);
    glDrawRangeElements(GL_TRIANGLES, 0, 0, 3, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_handle_count + 6)));
    glFrontFace(GL_CW);
    glDrawRangeElements(GL_TRIANGLES, 0, 0, 3, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_handle_count + 9)));

    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
