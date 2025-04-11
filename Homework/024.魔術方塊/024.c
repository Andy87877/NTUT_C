#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 3

// 初始位置  上右後前左下
// 顏色index 0藍 1紅 2黃 3白 4橘 5綠

void Put_all_color(int array[6][MAX_SIZE][MAX_SIZE], int index) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            array[index][i][j] = index + 1;
        }
    }
}

void Init_color(int array[6][MAX_SIZE][MAX_SIZE]) {
    for (int index = 0; index < 6; index++) {
        Put_all_color(array, index);
    }
}

void Copy_array(int goal_array[6][MAX_SIZE][MAX_SIZE],
                int array[6][MAX_SIZE][MAX_SIZE]) {
    for (int index = 0; index < 6; index++) {
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                goal_array[index][i][j] = array[index][i][j];
            }
        }
    }
}

void Print_array(int array[6][MAX_SIZE][MAX_SIZE], int index) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", array[index][i][j]);
        }
        printf("\n");
    }
}

void judge(int array[6][MAX_SIZE][MAX_SIZE]) {
    char operater[2];
    scanf("%s", &operater);
    getchar();
    char operater_col = operater[0];
    char operater_row = operater[1];

    int temp_array[6][3][3];
    Copy_array(temp_array, array);

    // 初始位置  上右後前左下
    // 顏色index 0藍 1紅 2黃 3白 4橘 5綠

    // 直線轉
    int row = operater_row - '0';
    if (operater_col == '1') { // 向前轉
        for (int y = 0; y < 3; y++) {
            temp_array[3][y][row] = array[5][y][row]; // 白變綠
            temp_array[5][y][row] = array[2][y][row]; // 綠變黃
            temp_array[2][y][row] = array[0][y][row]; // 黃變藍
            temp_array[0][y][row] = array[3][y][row]; // 藍變白
        }
    } else { // 向前轉
        for (int y = 0; y < 3; y++) {
            temp_array[3][row][y] = array[1][row][y]; // 白變紅
            temp_array[1][row][y] = array[2][row][y]; // 紅變黃
            temp_array[2][row][y] = array[4][row][y]; // 黃變橘
            temp_array[4][row][y] = array[3][row][y]; // 橘變白
        }
    }

    // 面轉
    // int color;
    // if (operater_col == '1') {
    //     if (operater_row == '0')
    //         color = 4; // 橘轉
    //     else
    //         color = 1; // 紅轉
    // } else {
    //     if (operater_row == '0')
    //         color = 0; // 藍轉
    //     else
    //         color = 5; // 綠轉
    // }

    // if (operater_row == '1'){ // 紅轉 逆時鐘
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 0; j < 3; j++) {
    //             temp_array[color][i][j] = array[color][2 - j][i];
    //         }
    //     }
    // } else { // 其他 順時鐘
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 0; j < 3; j++) {
    //             temp_array[color][i][j] = array[color][j][2 - i];
    //         }
    //     }
    // }

    

    Copy_array(array, temp_array);
}

int main() {
    int array[6][3][3];
    Init_color(array);

    int M;
    scanf("%d", &M);

    for (int judge_times = 0; judge_times < M; judge_times++) {
        judge(array);

        Print_array(array, 3);
    }
    // Print_array(array, 3);
}

// 顏色編號，1: 藍色，2: 紅色，3: 黃色，4: 白色，5: 橘色，6:綠色。
// 初始位置 上右後前左下