// 氣泡排序
#include <stdio.h>
#define SWAP(x,y) {int t; t = x; x = y; y = t;}


void Printf_array(int array[]) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[10] = {93, 69, 70, 88, 29, 25, 22, 74, 27, 26};
    Printf_array(array);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - i; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
                Printf_array(array);
            }
        }
    }
}