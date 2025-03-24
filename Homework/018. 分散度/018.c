#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 10

// 輸出array
void Print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 檢查重複的數字
int Check_repeat_number(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (array[i] == array[j]) {
                return 1; // 重複了
            }
        }
    }
    return 0;
}

// 檢查重複的子序列
int Check_repeat_array(int *array, int size, int (*ok_array)[MAX_M],
                       int ok_size) {
    for (int ok_index = 0; ok_index < ok_size; ok_index++) {
        int repeat = 1;
        for (int check_index = 0; check_index < size; check_index++) {
            if (ok_array[ok_index][check_index] != array[check_index]) {
                repeat = 0;
                break;
            }
        }
        if (repeat) return 1;
    }
    return 0;
}

// 交換array交換array
void Swap_array(int *array1, int *array2, int size){
    int temp_array[MAX_M];
    for (int i = 0; i < size; i++){
        temp_array[i] = array1[i];
        array1[i] = array2[i];
        array2[i] = temp_array[i];
    }
}

// 排序子序列
void Sort_ok_array(int (*ok_array)[MAX_M], int ok_size, int size){
    // 氣泡排序
    for (int i = 0; i < ok_size; i++){
        for (int j = i+1; j < ok_size; j++){
            // 從最前面的開始檢查
            for (int k = 0; k < size; k++){
                if (ok_array[i][k] < ok_array[j][k]){
                    break; // 不變
                }
                if (ok_array[i][k] > ok_array[j][k]){
                    Swap_array(ok_array[i], ok_array[j], size);
                    break; // 交換array (i, j)
                }
            }
        }
    }

    // 輸出排序後的結果
    for (int i = 0; i < ok_size; i++){
        Print_array(ok_array[i], size);
    }
}

int main() {
    int m; // 分散度
    scanf("%d", &m);

    int array_all[21], index = 0; // 整數序列

    // 輸入數字
    while (scanf("%d", &array_all[index]) != EOF) {
        index++;
    }

    int size_array = index;
    int ok_array[100][MAX_M];
    index = 0;
    int sequeue_number = 0; // 連續子序列

    // 找每一個子序列
    for (int i = 0; i < size_array - m + 1; i++) {
        int array_check[MAX_M];

        for (int j = 0; j < m; j++) {
            int now_number = array_all[i + j];
            array_check[j] = now_number;
        }

        // 不包含重複數字
        if (Check_repeat_number(array_check, m)) {
            continue;
        }
        sequeue_number++;

        // 不包含重複子序列
        if (Check_repeat_array(array_check, m, ok_array, index)) {
            continue;
        }
        for (int k = 0; k < m; k++) {
            ok_array[index][k] = array_check[k];
        }
        index++;
    }

    printf("%d\n", sequeue_number); // 連續子序列總數

    // 排序ok_array 並且輸出答案
    int ok_size = index;
    Sort_ok_array(ok_array, ok_size, m);
}