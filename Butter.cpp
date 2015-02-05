#include "Butter.h"

using glm::vec3;

void Butter::build(){
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vec3 v1, v2;

    // build butter
    // top side
    v1 = {BUTTER_SIDE_LEN / 2, -BUTTER_SIDE_LEN / 2, BUTTER_SIDE_LEN / 2};
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1.y += BUTTER_SIDE_LEN;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1.x -= BUTTER_SIDE_LEN;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);
    v1.y -= BUTTER_SIDE_LEN;
    all_index.push_back(all_points.size());
    all_points.push_back(v1);

    top_count = all_index.size();

    // bottom side
    for(auto v : all_points){
        v.z -= BUTTER_SIDE_LEN;
        all_index.push_back(all_points.size());
        all_points.push_back(v);
    }

    before_sides_count = all_index.size();
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

void Butter::render(bool outline) const{
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

    // top side
    glFrontFace(GL_CCW);
    glColor3ub (253, 243, 174);
    glDrawRangeElements(GL_QUADS, 0, 0, top_count, GL_UNSIGNED_SHORT, 0);
    // bottom side
    glFrontFace(GL_CW);
    glColor3ub (253, 243, 174);
    glDrawRangeElements(GL_QUADS, 0, 0, top_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * top_count));

    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}
