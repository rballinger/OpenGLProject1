#include "BufferObject.h"
class Toaster : public BufferObject {
private:
    const float TOASTER_WIDTH = 6.0;
    const float TOASTER_LENGTH = 9.0;
    const float TOASTER_HEIGHT = 8.5;
    const float TOASTER_RAD = 1.65;
    const float SUBDIV_AMT = 0.5;
    const float LEG_HEIGHT = 1.0;
    const float SUBDIV_TLENGTH = TOASTER_LENGTH / SUBDIV_AMT;
    int total_count,
        side_count;

protected:
public:
    void build ();
    void render(bool) const;
};
