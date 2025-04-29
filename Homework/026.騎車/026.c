#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void Init_array(int Point_array[SIZE][SIZE], int size, int Went_array[SIZE]) {
    // Point_array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Point_array[i][j] = -2;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", Point_array[i][j]);
        }
    }

    // Went_array
    for (int i = 0; i < SIZE; i++) {
        Went_array[i] = 0;
    }
}

int DFS(int Point_array[SIZE][SIZE], int size, int Went_array[SIZE]){
    
}

int main() {
    int Point_array[SIZE][SIZE]; // 點之距離array
    int Went_array[SIZE];        // 0沒走過 1走過
    int size = 0;
    scanf("%d", &size);

    int walk_break_times;
    int break_city_1, break_city_2;

    scanf("%d", walk_break_times);
    scanf("%d %d", break_city_1, break_city_2);

    Init_array(Point_array, size, Went_array);

    int answer = 0;
    answer = DFS(Point_array, size, Went_array);
}