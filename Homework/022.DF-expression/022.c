#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 8

void All_white(int array[][MAX_N]) {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            array[i][j] = 2;
        }
    }
}

int Judge(int array[][MAX_N], char input_str[], int now_index, int x_begin,
          int x_end, int y_begin, int y_end) {
    char now_char = input_str[now_index];
    now_index++;

    // printf("%d:   %d~%d , %d~%d\n", now_index, x_begin, x_end, y_begin,
    // y_end);

    if (now_char == '1') {
        for (int i = x_begin; i < x_end; i++) {
            for (int j = y_begin; j < y_end; j++) {
                array[i][j] = 1;
            }
        }
    }

    if (now_char == '2') {
        int x_mid = (x_begin + x_end) / 2;
        int y_mid = (y_begin + y_end) / 2;

        now_index =
            Judge(array, input_str, now_index, x_begin, x_mid, y_begin, y_mid);
        now_index =
            Judge(array, input_str, now_index, x_mid, x_end, y_begin, y_mid);
        now_index =
            Judge(array, input_str, now_index, x_begin, x_mid, y_mid, y_end);
        now_index =
            Judge(array, input_str, now_index, x_mid, x_end, y_mid, y_end);
    }

    return now_index;
}

void Get_answer(int array[][MAX_N], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[j][i] == 1){
                printf("%d,%d\n", i, j);
            }
        }
    }
}

int main() {
    char input_str[101]; // 第一行:輸入一個DF-expression的表達式 S (1 <=
                         // strlen(S) <= 100)，
    int N; // 第二行:輸入該張圖像的寬度 N(必為2的非負整數次方，2<=N<=8)。

    scanf("%s", &input_str);
    scanf("%d", &N);

    int str_size = strlen(input_str);
    int array[MAX_N][MAX_N];
    All_white(array);
    if (input_str[0] == '0'){
        printf("all white\n");
        return 0;
    }

    int tmp;
    tmp = Judge(array, input_str, 0, 0, N, 0, N); // 判斷
    Get_answer(array, N);
}