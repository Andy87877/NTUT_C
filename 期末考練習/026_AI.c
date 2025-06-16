#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

int N;
int Point_array[SIZE][SIZE];
int Visited[SIZE];
int Temp_path[SIZE];
int Best_path[SIZE];
int min_distance_global = INT_MAX;

void find_shortest_path(int current_city, int count, int current_distance) {
    Temp_path[count - 1] = current_city;
    Visited[current_city] = 1;

    if (count == N) {
        if (current_distance < min_distance_global) {
            min_distance_global = current_distance;
            memcpy(Best_path, Temp_path, N * sizeof(int));
        }
    } else {
        for (int next_city = 1; next_city <= N; ++next_city) {
            if (Point_array[current_city][next_city] != -1 &&
                !Visited[next_city]) {
                int new_distance =
                    current_distance + Point_array[current_city][next_city];
                if (new_distance < min_distance_global) {
                    find_shortest_path(next_city, count + 1, new_distance);
                }
            }
        }
    }
    Visited[current_city] = 0;
}

int main() {
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &Point_array[i][j]);
        }
    }

    int walk_break_city_index;
    int break_u, break_v;
    scanf("%d", &walk_break_city_index);
    scanf("%d %d", &break_u, &break_v);

    // Phase 1: Find initial shortest path
    memset(Visited, 0, sizeof(Visited));
    min_distance_global = INT_MAX;
    find_shortest_path(1, 1, 0);

    int initial_best_path_prefix[SIZE];
    memcpy(initial_best_path_prefix, Best_path, N * sizeof(int));

    int initial_distance_prefix = 0;
    int city_at_break = -1;

    memset(Visited, 0, sizeof(Visited));
    for (int i = 0; i < walk_break_city_index; ++i) {
        Visited[initial_best_path_prefix[i]] = 1;
        if (i > 0) {
            initial_distance_prefix +=
                Point_array[initial_best_path_prefix[i - 1]]
                           [initial_best_path_prefix[i]];
        }
        if (i == walk_break_city_index - 1) {
            city_at_break = initial_best_path_prefix[i];
        }
    }

    // Phase 2: Handle road break and find new path
    Point_array[break_u][break_v] = -1;
    Point_array[break_v][break_u] = -1;

    min_distance_global = INT_MAX;
    memcpy(Temp_path, initial_best_path_prefix,
           walk_break_city_index * sizeof(int));

    find_shortest_path(city_at_break, walk_break_city_index,
                       initial_distance_prefix);

    // Output results
    for (int i = 0; i < N; i++) {
        printf("%d%c", Best_path[i], (i == N - 1) ? '\n' : ' ');
    }
    printf("%d\n", min_distance_global);

    return 0;
}