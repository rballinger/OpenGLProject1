#include "BufferObject.h"
class Toaster : public BufferObject {
private:
    const float TOASTER_WIDTH = 6.0;
    const float TOASTER_LENGTH = 9.0;
    const float TOASTER_HEIGHT = 8.5;
    const float TOASTER_MAJ_RAD = TOASTER_WIDTH / 2;
    const float TOASTER_MIN_RAD = 1.65;
    const float SUBDIV_AMT = 0.5;
    const float LEG_HEIGHT = 1.0;
    const float SUBDIV_TLENGTH = TOASTER_LENGTH / SUBDIV_AMT;
    const int SUBDIV_MAJ_RAD = 10;
    const float SUBDIV_MAJ_RAD_AMT = TOASTER_MAJ_RAD / SUBDIV_MAJ_RAD;
    const float SLOT_FROM_LEFT = 1.5;
    const float SLOT_FROM_FRONT = 1.0;
    const float SLOT_LENGTH = 6.5;
    const float SLOT_FROM_RIGHT = TOASTER_LENGTH - SLOT_FROM_LEFT - SLOT_LENGTH;
    const float SLOT_SEPARATION = 1.0;
    const float SLOT_WIDTH = 1.5;
    const float SLOT_DEPTH = 4.25;
    int total_count,
        side_count,
        before_bottom_count,
        before_left_top_count,
        before_right_top_count,
        round_points,
        before_round_bottom_count,
        before_left_wall_count,
        before_right_wall_count,
        before_top_count,
        before_top_slots_count,
        top_slot_points,
        before_end_top_count,
        before_slots_bottom_count;

protected:
public:
    void build ();
    void render(bool) const;
};
