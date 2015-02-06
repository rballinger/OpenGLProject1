#include "BufferObject.h"
class ButterDish : public BufferObject {
private:
    const float THICKNESS = 0.25;
    const float TOP_LENGTH = 8.75;
    const float BOTTOM_LENGTH = 6.5;
    const float TOP_WIDTH = 3.75;
    const float BOTTOM_WIDTH = 2.5;
    const float HEIGHT = 1.25;
    int total_count,
        top_ridge_count,
        top_ridge_points,
        before_bottom_count,
        before_outer_bottom_count,
        before_inner_bottom_count,
        before_butter_count,
        before_butter_points,
        before_butter_sides_count;

protected:
public:
    void build ();
    void render(bool) const;
};
