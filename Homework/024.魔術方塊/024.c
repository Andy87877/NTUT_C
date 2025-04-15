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

void Print_color_array(int array[6][MAX_SIZE][MAX_SIZE], int index) {
    // 顏色index 0藍 1紅 2黃 3白 4橘 5綠
    char color[6] = {'B', 'R', 'Y', 'W', 'O', 'G'};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", color[array[index][i][j] - 1]);
        }
        printf("\n");
    }
}

void Print_all_color(int array[6][MAX_SIZE][MAX_SIZE]) {
    char name[6] = {'U', 'R', 'B', 'F', 'L', 'D'};
    for (int tttt = 0; tttt < 6; tttt++) {
        printf("%c: \n", name[tttt]);
        Print_color_array(array, tttt);
        printf("==================\n");
    }
}

void judge(int array[6][MAX_SIZE][MAX_SIZE]) {
    char operater[2];
    scanf("%2s", &operater);
    getchar();

    char operater_col = operater[0];
    char operater_row = operater[1];

    int temp_array[6][3][3];
    Copy_array(temp_array, array);

    // 初始位置  上右後前左下
    // 顏色index 0藍 1紅 2黃 3白 4橘 5綠
    // 顏色符號  1藍 2紅 3黃 4白 5橘 6綠

    // 直線轉
    int row = operater_row - '0';
    if (operater_col == '1') { // 向前轉
        for (int y = 0; y < 3; y++) {
            temp_array[3][y][row] = array[5][y][row];     // 白變綠
            temp_array[5][y][row] = array[2][y][2 - row]; // 綠變黃
            temp_array[2][y][2 - row] = array[0][y][row]; // 黃變藍
            temp_array[0][y][row] = array[3][y][row];     // 藍變白
        }
    } else { // 向前轉
        for (int y = 0; y < 3; y++) {
            temp_array[3][row][y] = array[1][row][y];     // 白變紅
            temp_array[1][row][y] = array[2][2 - row][y]; // 紅變黃
            temp_array[2][2 - row][y] = array[4][row][y]; // 黃變橘
            temp_array[4][row][y] = array[3][row][y];     // 橘變白
        }
    }

    // Print_array(array, 4);

    // 面轉
    int color = -1;
    if (operater_col == '1') {
        if (operater_row == '0')
            color = 4; // 橘轉
        else if (operater_row == '2')
            color = 1; // 紅轉
    } else {
        if (operater_row == '0')
            color = 0; // 藍轉
        else if (operater_row == '2')
            color = 5; // 綠轉
    }

    if (color == 0 || color == 1) { // 紅藍 順時鐘
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_array[color][i][j] = array[color][2 - j][i];
            }
        }
    } else if (color == 4 || color == 5) { // 橘綠轉 逆時鐘
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_array[color][i][j] = array[color][j][2 - i];
            }
        }
    }

    // Print_all_color(array);

    Copy_array(array, temp_array);
}

int main() {
    int array[6][3][3];
    Init_color(array);

    int M;
    scanf("%d", &M);

    for (int judge_times = 0; judge_times < M; judge_times++) {
        judge(array);
    }
    Print_array(array, 3);
}

// 顏色編號，1: 藍色，2: 紅色，3: 黃色，4: 白色，5: 橘色，6:綠色。
// 初始位置 上右後前左下