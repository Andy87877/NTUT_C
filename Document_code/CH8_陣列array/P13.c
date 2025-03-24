#include <stdio.h>
int find2Min(int data[], int size) {
    int minIndex, index = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] < data[minIndex]) minIndex = i;
    }

    for (int i = 0; i < size; i++) {
        if (i != minIndex) {
            if (data[i] < data[index]) index = i;
        }
    }
    return data[index];
}
int main() {
    printf("hello main\n"); // 沒有這個會跑不出來 神奇
    int data[] = {5, 1, 3, 6, 2};
    printf("2 min=%d\n", find2Min(data, 5));
    return 0;
}