#include "BufferObject.h"
class ButterDish : public BufferObject {
private:
    const float GLASS_THICKNESS = 2.5;
    const float TOP_LENGTH = 8.75;
    const float BOTTOM_LENGTH = 6.5;
    const float TOP_WIDTH = 3.75;
    const float BOTTOM_WIDTH = 2.5;
    const float HEIGHT = 1.25;
    int side_count;

protected:
public:
    void build (void*);
    void render(bool) const;
};
