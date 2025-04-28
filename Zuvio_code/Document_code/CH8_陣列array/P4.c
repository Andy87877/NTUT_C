// 陣列的記憶空間及大小
#include <stdio.h>

int main() {
    double data[101];
    printf("陣列所佔位元組%d\n", sizeof(data));
    printf("陣列元素所佔位元組%d\n", sizeof(data[0]));
    printf("陣列個數%d", sizeof(data) / sizeof(double));
    return 0;
}