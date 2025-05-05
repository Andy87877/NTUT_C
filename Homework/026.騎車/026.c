#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

void Init_array(int Point_array[SIZE][SIZE], int size, int Went_array[SIZE],
                int Route_array[SIZE], int Temp_route[SIZE]) {
    // Point_array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Point_array[i][j] = -1;
        }
    }
    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size + 1; j++) {
            scanf("%d", &Point_array[i][j]);
        }
    }

    // Went_array
    for (int i = 0; i < SIZE; i++) {
        Went_array[i] = 0;
        Route_array[i] = 0;
        Temp_route[i] = 0;
    }
}

void Print_Route_array(int Route_array[SIZE], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", Route_array[i]);
    }
    printf("\n");
}

int DFS(int Point_array[SIZE][SIZE], int size, int Went_array[SIZE], int count,
        int distance, int current_city, int start_city, int Route_array[SIZE],
        int Temp_route[SIZE]) {
    Temp_route[count] = current_city;

    if (count == size) {
        Print_Route_array(Temp_route, count);
        int total_distance = distance + Point_array[current_city][start_city];
        Temp_route[count + 1] = start_city;

        if (Temp_route[0] == 1) {
            // 更新最短路徑
            for (int i = 0; i <= size; i++) {
                Route_array[i] = Temp_route[i];
            }
            return total_distance;
        }
    }
    Print_Route_array(Route_array, size);

    int min_dist = INT_MAX;

    for (int i = 1; i < size + 1; i++) {
        if (!Went_array[i] && Point_array[current_city][i] != -1 &&
            current_city != i) {
            Went_array[i] = 1;
            int result = DFS(Point_array, size, Went_array, count + 1,
                             distance + Point_array[current_city][i], i,
                             start_city, Route_array, Temp_route);
            if (result < min_dist) {
                min_dist = result;
            }
            Went_array[i] = 0; // backtrack
        }
    }

    return min_dist;
}

int main() {
    int Point_array[SIZE][SIZE]; // 點之距離array
    int Went_array[SIZE];        // 0沒走過 1走過
    int Route_array[SIZE];       // 路徑
    int Temp_route[SIZE];        // 路徑
    int size = 0;
    scanf("%d", &size);

    Init_array(Point_array, size, Went_array, Route_array, Temp_route);

    int walk_break_city;
    int break_city[2];

    scanf("%d", &walk_break_city);
    scanf("%d %d", &break_city[0], &break_city[1]);

    int answer = 0;

    int went_count = 0, distance = 0;
    int from_city = 1, to_city = 1;

    Went_array[from_city] = 1;

    //  Point_array[SIZE][SIZE], size, Went_array[SIZE], went_count, from_city,
    //  to_city, distance, Route_array
    answer = DFS(Point_array, size, Went_array, went_count, distance, from_city,
                 to_city, Route_array, Temp_route);

    Print_Route_array(Route_array, size);

    printf("answer: %d", answer);
}