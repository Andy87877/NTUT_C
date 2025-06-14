#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
        int times;
        int x;
        int y;
} data_t;

void Copy_array(int copy_array[MAX_SIZE][MAX_SIZE],
                int array[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            copy_array[i][j] = array[i][j];
        }
    }
}

int MAX(int a, int b) {
    if (a > b) return a;
    return b;
}

int MIN(int a, int b) {
    if (a < b) return a;
    return b;
}

int check_one_line(int line_array[MAX_SIZE], int size) {
    int check_times = 0;
    for (int i = 0; i < size; i++) {
        if (line_array[i] == 1) {
            check_times++;
        } else {
            check_times = 0;
        }
        if (check_times == 5) {
            return 1;
        }
    }

    return 0;
}

int check_line(int check_array[MAX_SIZE][MAX_SIZE], int x, int y) {
    int All_line = 0;
    int x_begin = MAX(0, x - 5), x_end = MIN(MAX_SIZE, x + 6);
    int y_begin = MAX(0, y - 5), y_end = MIN(MAX_SIZE, y + 6);

    int x_index = 0;
    int line_array[MAX_SIZE];
    for (int i = x_begin; i < x_end; i++) {
        int now_point = check_array[i][y];
        line_array[x_index] = now_point;
        x_index++;
    }
    All_line += check_one_line(line_array, x_index);

    int y_index = 0;
    for (int j = y_begin; j < y_end; j++) {
        int now_point = check_array[x][j];
        line_array[y_index] = now_point;
        y_index++;
    }
    All_line += check_one_line(line_array, y_index);

    int now_index = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (x - i != y - j) continue;
            if (abs(x - i) > 5) continue;

            int now_point = check_array[i][j];
            line_array[now_index] = now_point;
            now_index++;
        }
    }
    All_line += check_one_line(line_array, now_index);

    return All_line;
}

void Print_answer(data_t All_data[MAX_SIZE * MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int change = 0;
            if (All_data[i].times > All_data[j].times) {
                change = 1;
            } else if (All_data[i].times == All_data[j].times) {
                if (All_data[i].x < All_data[j].x) {
                    change = 1;
                } else if (All_data[i].x == All_data[j].x) {
                    if (All_data[i].y < All_data[j].y) {
                        change = 1;
                    }
                }
            }

            if (change == 1) {
                data_t tmp = All_data[i];
                All_data[i] = All_data[j];
                All_data[j] = tmp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("%d%d %d\n", All_data[i].x, All_data[i].y, All_data[i].times);
    }
}

void judge_all(int array[MAX_SIZE][MAX_SIZE]) {
    data_t All_data[MAX_SIZE * MAX_SIZE];
    int now_index = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (array[i][j] == 1) continue;

            int check_array[MAX_SIZE][MAX_SIZE];
            Copy_array(check_array, array);
            check_array[i][j] = 1;

            int line = check_line(check_array, i, j);

            printf("%d\n", line);

            if (line == 0) continue;

            All_data[now_index].times = line;
            All_data[now_index].x = i;
            All_data[now_index].y = j;
            now_index++;
        }
    }

    Print_answer(All_data, now_index);
}

int main() {
    int array[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    judge_all(array);
}