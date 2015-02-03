#include "ButterDish.h"

using glm::vec3;

void ButterDish::build(void* data){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2;

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
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
//    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
//    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */

    // top ridge
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (210, 210, 210);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_ridge_count, GL_UNSIGNED_SHORT, 0);

    // bottom of top ridge
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (60, 60, 60);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_ridge_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (top_ridge_count)));

    // top ridge outer walls
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (180, 180, 180);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (150, 150, 150);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 2)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (120, 120, 120);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 4)));
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (90, 90, 90);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2 * top_ridge_count + 6)));



    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
