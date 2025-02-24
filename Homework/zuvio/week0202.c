// 不定參數
#include <stdio.h>
#include <stdarg.h>

int computeArea(int len, ...){
    int Area = 1, Side_length = 0;

    va_list args;
    va_start(args, len);

    if (len == 1){
        Side_length = va_arg(args, int);
        Area = Side_length * Side_length;
    } else {
        for (int j = 0; j < len; j++){
            Area *= va_arg(args, int);
        }
    }
    
    va_end(args);
    // printf("%d\n", Area);
    return Area;
}

int main(){
    int x = 7, y = 4;

    printf("x: \n");
    computeArea(1, x);

    printf("x, y: \n");
    computeArea(2, x, y);
}