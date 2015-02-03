#include "BufferObject.h"
class Bread : public BufferObject {
private:
    const float BREAD_THICKNESS = 0.25;
    const float CRUST_THICKNESS = 8.75;
    const float BREAD_WIDTH = 3.75;
    const float LARGE_RAD = 1.25;
    const float SMALL_RAD = 1.5;
    int total_count;

protected:
public:
    void build (void*);
    void render(bool) const;
};
