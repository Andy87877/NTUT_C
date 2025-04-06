// 排序演算法之比較
/*
輸入一數列，將數列小到大排序，輸出使用
選擇排序法的比較次數和搬移次數
插入排序法的比較次數和搬移次數
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15
#define SWAP(x, y) \
    {              \
        int t;     \
        t = x;     \
        x = y;     \
        y = t;     \
    }

// 輸出array
void Print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 複製array
void Copy_array(int goal_array[], int array[], int size) {
    for (int i = 0; i < size; i++) {
        goal_array[i] = array[i];
    }
}

// 選擇排序
void Selection_sort(int array[], int size) {
    int compare = 0, move = 0;
    for (int i = 0; i < size; i++) {
        int min_number = array[i];
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            compare++;
            if (min_number > array[j]) {
                min_index = j;
                min_number = array[j];
            }
        }

        if (min_index != i) {
            SWAP(array[i], array[min_index]);
            move += 3;
        }
    }

    printf("%d %d\n", compare, move);
}

// 插入排序
void Insertion_sort(int array[], int size) {
    int compare = 0, move = 0;
    int target = 0, i = 0, j = 0;

    for (i = 1; i < size; i++) {
        target = array[i];
        move++;
        for (j = i; 1 == 1; j--) {
            compare++;
            if (j <= 0) break;

            compare++;
            if (array[j - 1] <= target) break;

            move++;
            array[j] = array[j - 1];
        }
        move++;
        array[j] = target;
    }

    printf("%d %d\n", compare, move);
}

int main() {
    int size;
    scanf("%d", &size);

    // 選擇排序法, 插入排序法
    int array[MAX_SIZE], array_2[MAX_SIZE];
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    Copy_array(array_2, array, size);

    Selection_sort(array, size);   // 選擇排序
    Insertion_sort(array_2, size); // 插入排序
}
