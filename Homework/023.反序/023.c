#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(a, b) \
    {              \
        int tmp;   \
        tmp = a;   \
        a = b;     \
        b = tmp;   \
    }

// 輸出array
void Print_array(int array[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 輸入array
void Input_array(int array[], int N) {
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
}

// 複製array
void Copy_array(int goal_array[], int array[], int N) {
    for (int i = 0; i < N; i++) {
        goal_array[i] = array[i];
    }
}

// 排序array (用n^2的排序bruh)
void Sort_array(int array[], int N) {
    for (int m = 0; m < N; m++) {
        for (int n = m + 1; n < N; n++) {
            if (array[n] < array[m]) {
                SWAP(array[n], array[m]);
            }
        }
    }
}

// 找到題目的要求
void Find_answer(int array[], int N, int index) {
    int answer[MAX_SIZE]; // 後面符合
    int ok_index = 0;
    for (int k = index + 1; k < N; k++) {
        if (array[index] > array[k]) {
            answer[ok_index] = array[k];
            ok_index++;
            // printf("(%d,%d)\n", array[i], array[j]);
        }
    }

    Sort_array(answer, ok_index);

    int last = -1;
    for (int k = 0; k < ok_index; k++) {
        if (answer[k] == last) continue;
        printf("(%d,%d)\n", array[index], answer[k]);
        last = answer[k];
    }
}

// 檢查是否都沒有 (排序和原始是否相同)
void Check_none(int array[], int sort_array[], int N) {
    int no_answer = 1; // 沒有答案
    for (int i = 0; i < N; i++) {
        if (array[i] != sort_array[i]) {
            no_answer = 0;
            break;
        }
    }
    if (no_answer) printf("0\n");
}

// 開始判斷
void Judge_all(int array[], int N) {
    int sort_array[MAX_SIZE];
    Copy_array(sort_array, array, N);
    Sort_array(sort_array, N); // 排序過了

    int last = -1;
    for (int i = 0; i < N; i++) {
        int goal_num = sort_array[i];
        if (last == goal_num) continue; // 重複

        for (int j = 0; j < N; j++) {
            if (array[j] == goal_num) { // 找到index
                Find_answer(array, N, j);
                break;
            }
        }

        last = sort_array[i];
    }

    Check_none(array, sort_array, N); // 檢查是否都沒有解
}

int main() {
    int N, array[MAX_SIZE];
    scanf("%d", &N);
    Input_array(array, N);
    Judge_all(array, N); // 判斷
}