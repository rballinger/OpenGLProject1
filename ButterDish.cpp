#include "ButterDish.h"

using glm::vec3;

void ButterDish::build(void* data){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1;
    // +y side
    v1 = {-TOP_LENGTH/2, TOP_WIDTH/2, HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {-TOP_LENGTH/2, TOP_WIDTH/2, -HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {TOP_LENGTH/2, TOP_WIDTH/2, HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {TOP_LENGTH/2, TOP_WIDTH/2, -HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    // +x side
    v1 = {TOP_LENGTH/2, -TOP_WIDTH/2, HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {TOP_LENGTH/2, -TOP_WIDTH/2, -HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    // -y side
    v1 = {-TOP_LENGTH/2, -TOP_WIDTH/2, HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1 = {-TOP_LENGTH/2, -TOP_WIDTH/2, -HEIGHT/2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    // -x side
    all_index.push_back(0);
    all_index.push_back(1);
    // top
    all_index.push_back(0);
    all_index.push_back(2);
    all_index.push_back(6);
    all_index.push_back(4);
    // bottom
    all_index.push_back(1);
    all_index.push_back(3);
    all_index.push_back(7);
    all_index.push_back(5);

    side_count = all_index.size();

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
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, 0);

    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (225, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2)));

    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (195, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2*2)));

    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (165, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (2*3)));

    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glColor3ub (135, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (side_count - 8)));

    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (105, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 4, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * (side_count - 4)));


    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
