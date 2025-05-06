#include <stdio.h>
typedef union {
        int id;
        struct {
                unsigned int x : 1;
                unsigned int : 0;
                unsigned int y : 2;
                unsigned int z : 2;
        } bits;
} number_t;
void main() {
    number_t number;
    for (number.id = 0; number.id < 16; number.id++) {
        printf("id=%3d,bits=%3d%3d%3d\n", number.id, number.bits.z,
               number.bits.y, number.bits.x);
    }
}