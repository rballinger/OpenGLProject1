#include "BufferObject.h"
class Toaster : public BufferObject {
private:
    const float TOASTER_WIDTH = 6.0f;
    const float TOASTER_LENGTH = 9.0f;
    const float TOASTER_HEIGHT = 8.5f;
    const float TOASTER_MAJ_RAD = TOASTER_WIDTH / 2;
    const float TOASTER_MIN_RAD = 1.65f;
    const float SUBDIV_AMT = 0.5f;
    const float LEG_HEIGHT = 1.0f;
    const float SUBDIV_TLENGTH = TOASTER_LENGTH / SUBDIV_AMT;
    const int SUBDIV_MAJ_RAD = 10;
    const float SUBDIV_MAJ_RAD_AMT = TOASTER_MAJ_RAD / SUBDIV_MAJ_RAD;
    int total_count,
        side_count,
        before_bottom_count,
        before_left_top_count,
        before_right_top_count,
        round_points,
        before_round_bottom_count,
        before_left_wall_count,
        before_right_wall_count;

protected:
public:
    void build ();
    void render(bool) const;
};
