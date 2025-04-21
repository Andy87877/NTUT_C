#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int MAX(int a, int b) {
    if (a > b) return a;
    return b;
}
int MIN(int a, int b) {
    if (a < b) return a;
    return b;
}

void Copy_array(int goal_array[][SIZE], int array[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            goal_array[i][j] = array[i][j];
        }
    }
}

void Array_fill_black(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = -1;
    }
}

// Judge 一行
int Judge_line(int line_array[SIZE], int size, int debug) {
    if (debug == 1) {
        for (int i = 0; i < size; i++) {
            printf("%d", line_array[i]);
        }
        printf("\n");
    }

    int now_black = 0;
    if (size < 5) return 0;

    for (int i = 0; i < size; i++) {
        if (line_array[i] == 0) {
            if (now_black == 5) { // 剛好五子
                return 1;
            }
            now_black = 0;
        } else if (line_array[i] == 1) { // black
            now_black++;
        }
    }

    return (now_black == 5);
}

int Judge_single_coordinate(int array[SIZE][SIZE], int index_i, int index_j) {
    // printf("%d, %d\n", index_i, index_j);
    int All_line = 0;
    int debug = 0;

    // if (index_i == 0 && index_j == 0) {
    //     // printf("0:1\n");
    //     debug = 1;
    // }

    int line_array[SIZE];
    int index_begin, index_end, size, now_index;

    // 上下
    Array_fill_black(line_array, SIZE);
    index_begin = MAX(index_i - 5, 0);
    index_end = MIN(index_i + 6, SIZE);
    size = index_end - index_begin;
    now_index = 0;
    for (int i = index_begin; i < index_end; i++) {
        line_array[now_index] = array[i][index_j];
        now_index++;
    }
    All_line += Judge_line(line_array, size, debug);

    // 左右
    Array_fill_black(line_array, SIZE);
    index_begin = MAX(index_j - 5, 0);
    index_end = MIN(index_j + 6, SIZE);
    size = index_end - index_begin;
    now_index = 0;
    for (int j = index_begin; j < index_end; j++) {
        line_array[now_index] = array[index_i][j];
        now_index++;
    }
    All_line += Judge_line(line_array, size, debug);

    // 左上到右下
    Array_fill_black(line_array, SIZE);
    int diff = index_i - index_j;
    now_index = 0;
    int now_i, now_j;
    if (diff >= 0) {
        for (int j = 0; j < 10; j++) {
            if (j + 5 < index_j) continue;
            if (j - 5 > index_j) break;
            if (j + diff >= 10) break;
            now_i = j + diff;
            now_j = j;
            line_array[now_index] = array[now_i][now_j];
            now_index++;
        }
    } else {
        diff *= -1;
        for (int i = 0; i < 10; i++) {
            if (i + 5 < index_i) continue;
            if (i - 5 > index_i) break;
            if (i + diff >= 10) break;
            now_i = i;
            now_j = i + diff;
            line_array[now_index] = array[now_i][now_j];
            now_index++;
        }
    }
    size = now_index;

    All_line += Judge_line(line_array, size, debug);

    // 右上到左下
    Array_fill_black(line_array, SIZE);
    int sum = index_i + index_j;
    now_index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i + j == sum && i >= index_i - 5 && i <= index_i + 5 &&
                j >= index_j - 5 && j <= index_j + 5) {
                line_array[now_index] = array[i][j];
                now_index++;
            }
        }
    }
    size = now_index;
    All_line += Judge_line(line_array, size, debug);

    return All_line;
}

void Print_answer(char coordinate_array[][2], int line_array[],
                  int array_size) {
    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            int change = 0;
            if (line_array[i] > line_array[j]) {
                change = 1;
            }
            if (line_array[i] == line_array[j]) {
                if (coordinate_array[i][0] < coordinate_array[j][0]) {
                    change = 1;
                }
                if (coordinate_array[i][0] == coordinate_array[j][0]) {
                    if (coordinate_array[i][1] < coordinate_array[j][1]) {
                        change = 1;
                    }
                }
            }

            if (change == 1) {
                int tmp = line_array[i];
                line_array[i] = line_array[j];
                line_array[j] = tmp;

                char tmp_chr = coordinate_array[i][0];
                coordinate_array[i][0] = coordinate_array[j][0];
                coordinate_array[j][0] = tmp_chr;

                tmp_chr = coordinate_array[i][1];
                coordinate_array[i][1] = coordinate_array[j][1];
                coordinate_array[j][1] = tmp_chr;
            }
            change = 0;
        }
    }
    for (int i = 0; i < array_size; i++) {
        printf("%c%c %d\n", coordinate_array[i][0], coordinate_array[i][1],
               line_array[i]);
    }
}

void Judge_all(int origin_array[SIZE][SIZE]) {
    int now_array[SIZE][SIZE];

    int array_index = 0;
    char coordinate_array[SIZE * SIZE][2];
    int line_array[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (origin_array[i][j] == 0) {
                Copy_array(now_array, origin_array);
                now_array[i][j] = 1;
                // printf("%d %d\n", i, j);

                int line = 0;
                line = Judge_single_coordinate(now_array, i, j);

                if (line != 0) {
                    coordinate_array[array_index][0] = i + '0';
                    coordinate_array[array_index][1] = j + '0';

                    line_array[array_index] = line;
                    array_index++;
                }
            }
        }
    }

    Print_answer(coordinate_array, line_array, array_index);
}

int main() {
    int array[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    Judge_all(array);
}