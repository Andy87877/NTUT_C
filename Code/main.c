#include <stdio.h>
int main() {
    int x,y,z;
    x = y = z = 0;
    /* testing the increment by 1 */
    x = ++y + ++z;
    printf("\1: line 14 result ... %d %d %d\n",x,y,z);
    x = y++ + z++;
    printf("\2: line 16 result ... %d %d %d\n",x,y,z);
    /* testing the decrement by 1 */
    x = y = z = 0;
    x = --y + --z;
    printf("\1: line 20 result ... %d %d %d\n",x,y,z);
    x = y-- + z--;
    printf("\2: line 22 result ... %d %d %d\n",x,y,z);

    printf("\1 1");
}