#include <stdio.h>
typedef union {
        int id;
        struct {
                unsigned int x : 2;
                unsigned int y : 2;
                unsigned int z : 1;
        } bits;
} number_t;
void main() {
    number_t number;
    for (number.id = 0; number.id < 16; number.id++) {
        printf("id=%3d,bits=%3d%3d%3d\n", number.id, number.bits.z,
               number.bits.y, number.bits.x);
    }
}