#include <stdio.h>
void findCode(int areaCode) {
    switch(areaCode) { //依區域號碼判斷
        case 2:
            printf("02\n");
            
        case 3:
            printf("03 \n");
            
        default:
            printf("None\n");
}
}
int main() {
    findCode(2);
    findCode(3);
    findCode(9);
    return 0;
}