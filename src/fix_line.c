#include "fdf.h"

#define INSIDE  0  // 0000
#define LEFT    1  // 0001
#define RIGHT   2  // 0010
#define BOTTOM  4  // 0100
#define TOP     8  // 1000

int computeOutCode(float x, float y) {
    int code = INSIDE;

    if (x < 0)
        code |= LEFT;
    else if (x > WIDTH)
        code |= RIGHT;
    
    if (y < 0)
        code |= TOP;
    else if (y > HEIGHT)
        code |= BOTTOM;

    return code;
}

int cohenSutherlandClip(t_vector2 *v1, t_vector2 *v2)
{
    int outCode1 = computeOutCode(v1->x, v1->y);
    int outCode2 = computeOutCode(v2->x, v2->y);
    int accept = 0;
    float   x;
    float   y;

    while (1) {
        if ((outCode1 == 0) && (outCode2 == 0)) {
            accept = 1;
            break;
        } else if (outCode1 & outCode2) {
            return 0;
        } else {
            int outCodeOut = outCode1 ? outCode1 : outCode2;

            if (outCodeOut & TOP) {
                x = v1->x + (v2->x - v1->x) * (0 - v1->y) / (v2->y - v1->y);
                y = 0;
            } else if (outCodeOut & BOTTOM) {
                x = v1->x + (v2->x - v1->x) * (HEIGHT - v1->y) / (v2->y - v1->y);
                y = HEIGHT;
            } else if (outCodeOut & RIGHT) {
                y = v1->y + (v2->y - v1->y) * (WIDTH - v1->x) / (v2->x - v1->x);
                x = WIDTH;
            } else if (outCodeOut & LEFT) {
                y = v1->y + (v2->y - v1->y) * (0 - v1->x) / (v2->x - v1->x);
                x = 0;
            } else
                return (0);
            if (outCodeOut == outCode1)
            {
                v1->x = x;
                v1->y = y;
                outCode1 = computeOutCode(v1->x, v1->y);
            } else {
                v2->x = x;
                v2->y = y;
                outCode2 = computeOutCode(v2->x, v2->y);
            }
        }
    }

    return (accept);
}
