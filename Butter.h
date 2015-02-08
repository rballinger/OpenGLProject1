/**
 *  Author: Ryan Ballinger      Date: 2-8-15
 *  Professor: Dulimarta        Project: Objects & Transformations
 *  File: Butter.h
 */

#include "BufferObject.h"

class Butter : public BufferObject {
private:
    const float BUTTER_SIDE_LEN = 0.5;
    int total_count,
        top_count,
        before_sides_count;

protected:
public:
    void build ();
    void render(bool) const;
};
