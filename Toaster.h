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
    const float GRATE_FROM_FRONT = 0.1;
    const float GRATE_VERT_SEP = 1.5;
    const float GRATE_HORIZ_SEP = 1.5;
    const float GRATE_FROM_SIDE = 1.0;
    const int NUM_OF_GRATES = 3;
    const float GRATE_HEIGHT = 3.75;
    const float HANDLE_LENGTH = 3.0;
    const float HANDLE_WIDTH = 2.5;
    const float HANDLE_HEIGHT = 2.0;
    const float HANDLE_FROM_GROUND = 7.5;
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
        start_slot_points,
        end_slot_points,
        before_end_top_count,
        before_slots_bottom_count,
        before_front_slot_count,
        before_back_slot_count,
        before_grate_count,
        grate_points,
        before_handle_count;

protected:
public:
    void build ();
    void render(bool) const;
};
