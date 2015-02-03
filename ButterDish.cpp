#include "ButterDish.h"

using glm::vec3;

void ButterDish::build(void* data){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2, v3, v4;

    // top ridge
    v1 = {TOP_WIDTH/2, -TOP_LENGTH/2, HEIGHT/2};
    v2 = {v1.x - THICKNESS, v1.y + THICKNESS, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {TOP_WIDTH/2, TOP_LENGTH/2, HEIGHT/2};
    v2 = {v1.x - THICKNESS, v1.y - THICKNESS, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {-TOP_WIDTH/2, TOP_LENGTH/2, HEIGHT/2};
    v2 = {v1.x + THICKNESS, v1.y - THICKNESS, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {-TOP_WIDTH/2, -TOP_LENGTH/2, HEIGHT/2};
    v2 = {v1.x + THICKNESS, v1.y + THICKNESS, v1.z};
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    all_index.push_back(all_points.size());
    all_points.push_back(v1);

    all_index.push_back(0);
    all_index.push_back(1);

    top_ridge_count = all_index.size();
    top_ridge_points = all_points.size();

    // bottom of top ridge
    for(auto v : all_points){
        v1 = {v.x, v.y, v.z - THICKNESS};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
    }

    all_index.push_back(top_ridge_points);
    all_index.push_back(top_ridge_points + 1);

    // top ridge outer sides
    for(int i = 0; i < top_ridge_points / 2; i++){
        all_index.push_back(2 * i + 1);
        all_index.push_back(2 * i + 1 + top_ridge_points);
    }
    all_index.push_back(1);
    all_index.push_back(top_ridge_points + 1);

    before_bottom_count = all_index.size();

    // bottom
    v1 = {BOTTOM_WIDTH/2, -BOTTOM_LENGTH/2, -HEIGHT/2};
    v2 = {BOTTOM_WIDTH/2, BOTTOM_LENGTH/2, -HEIGHT/2};
    v3 = {-BOTTOM_WIDTH/2, BOTTOM_LENGTH/2, -HEIGHT/2};
    v4 = {-BOTTOM_WIDTH/2, -BOTTOM_LENGTH/2, -HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    all_index.push_back(all_points.size());
    all_points.push_back(v4);
    all_index.push_back(all_points.size());
    all_points.push_back(v3);
    v1.x -= THICKNESS;
    v1.y += THICKNESS;
    v1.z += THICKNESS;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v2.x -= THICKNESS;
    v2.y -= THICKNESS;
    v2.z += THICKNESS;
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    v4.x += THICKNESS;
    v4.y += THICKNESS;
    v4.z += THICKNESS;
    all_index.push_back(all_points.size());
    all_points.push_back(v4);
    v3.x += THICKNESS;
    v3.y -= THICKNESS;
    v3.z += THICKNESS;
    all_index.push_back(all_points.size());
    all_points.push_back(v3);

    before_butter_count = all_index.size();
    before_butter_points = all_points.size();

    // butter
    v1.x = BUTTER_WIDTH / 2;
    v1.y = -1.5;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v2.x = BUTTER_WIDTH / 2;
    v2.y = 2.5;
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    v3.x = -BUTTER_WIDTH / 2;
    v3.y = -1.5;
    all_index.push_back(all_points.size());
    all_points.push_back(v3);
    v4.x = -BUTTER_WIDTH / 2;
    v4.y = 2.5;
    all_index.push_back(all_points.size());
    all_points.push_back(v4);
    v1.z += BUTTER_HEIGHT;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v2.z += BUTTER_HEIGHT;
    all_index.push_back(all_points.size());
    all_points.push_back(v2);
    v3.z += BUTTER_HEIGHT;
    all_index.push_back(all_points.size());
    all_points.push_back(v3);
    v4.z += BUTTER_HEIGHT;
    all_index.push_back(all_points.size());
    all_points.push_back(v4);

    before_butter_sides_count = all_index.size();
    // butter sides
    all_index.push_back(before_butter_points + 4);
    all_index.push_back(before_butter_points);
    all_index.push_back(before_butter_points + 5);
    all_index.push_back(before_butter_points + 1);
    all_index.push_back(before_butter_points + 7);
    all_index.push_back(before_butter_points + 3);
    all_index.push_back(before_butter_points + 6);
    all_index.push_back(before_butter_points + 2);
    all_index.push_back(before_butter_points + 4);
    all_index.push_back(before_butter_points);

    before_outer_bottom_count = all_index.size();

    // outer sides of bottom
    all_index.push_back(8);
    all_index.push_back(16);
    all_index.push_back(10);
    all_index.push_back(17);
    all_index.push_back(12);
    all_index.push_back(19);
    all_index.push_back(14);
    all_index.push_back(18);
    all_index.push_back(8);
    all_index.push_back(16);

    before_inner_bottom_count = all_index.size();

    // inner sides of bottom
    all_index.push_back(0);
    all_index.push_back(20);
    all_index.push_back(2);
    all_index.push_back(21);
    all_index.push_back(4);
    all_index.push_back(23);
    all_index.push_back(6);
    all_index.push_back(22);
    all_index.push_back(0);
    all_index.push_back(20);

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

void ButterDish::render(bool outline) const{
    // set mode
    auto mode = GL_QUAD_STRIP;
    if(outline){
        mode = GL_LINE_LOOP;
    }else{
        mode = GL_QUAD_STRIP;
    }

    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
//    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
//    glColorPointer(3, GL_FLOAT, 0, 0);v1 = {TOP_WIDTH/2, -TOP_LENGTH/2, HEIGHT/2};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */

    // top ridge
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (210, 210, 210);
    glDrawRangeElements(mode, 0, 0, top_ridge_count, GL_UNSIGNED_SHORT, 0);

    // bottom of top ridge
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (60, 60, 60);
    glDrawRangeElements(mode, 0, 0, top_ridge_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (top_ridge_count)));

    // top ridge outer walls
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (180, 180, 180);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (150, 150, 150);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 2)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (120, 120, 120);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 4)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (90, 90, 90);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 6)));

    // bottom
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (90, 90, 90);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_bottom_count));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (90, 90, 90);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_bottom_count + 4)));

    // butter bottom
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (253, 243, 174);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_butter_count));
    // butter top
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (253, 243, 174);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_butter_count + 4)));
    // butter sides
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (252, 235, 118);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_butter_sides_count));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (251, 231, 87);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_butter_sides_count + 2)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (250, 223, 35);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_butter_sides_count + 4)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (211, 186, 5);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_butter_sides_count + 6)));

    // outer sides of bottom
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (110, 110, 110);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_outer_bottom_count));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (140, 140, 140);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_outer_bottom_count + 2)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (170, 170, 170);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_outer_bottom_count + 4)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_outer_bottom_count + 6)));

    // inner sides of bottom
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (110, 110, 110);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * before_inner_bottom_count));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (140, 140, 140);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_inner_bottom_count + 2)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (170, 170, 170);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_inner_bottom_count + 4)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (200, 200, 200);
    glDrawRangeElements(mode, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (before_inner_bottom_count + 6)));

    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
