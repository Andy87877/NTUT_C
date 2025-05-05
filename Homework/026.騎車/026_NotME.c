#include <limits.h> // For INT_MAX
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For memcpy

#define SIZE 15

int N;                       // 城市數量
int Point_array[SIZE][SIZE]; // 距離矩陣
int Visited[SIZE];           // 標記城市是否已訪問 (用於當前回溯)
int Temp_path[SIZE];         // 當前回溯的路徑
int Best_path[SIZE];         // 儲存找到的最佳路徑
int min_distance = INT_MAX;  // 儲存找到的最短距離

// 回溯函數尋找最短路徑
// current_city: 當前所在的城市
// count: 已經訪問的城市數量
// current_distance: 當前路徑的總距離
void find_shortest_path(int current_city, int count, int current_distance) {
    Temp_path[count - 1] = current_city; // 將當前城市加入臨時路徑 (索引從0開始)
    Visited[current_city] = 1;           // 標記為已訪問

    // 基底情況：訪問了所有 N 個城市
    if (count == N) {
        if (current_distance < min_distance) {
            min_distance = current_distance;
            memcpy(Best_path, Temp_path, N * sizeof(int)); // 複製找到的最佳路徑
        }
    } else {
        // 探索下一個可能的城市
        for (int next_city = 1; next_city <= N; ++next_city) {
            // 條件：有路徑、下個城市未訪問過
            if (Point_array[current_city][next_city] != -1 &&
                !Visited[next_city]) {
                int new_distance =
                    current_distance + Point_array[current_city][next_city];
                // 剪枝：如果當前路徑加上下一步已經超過已知最短路徑，則不再繼續
                if (new_distance < min_distance) {
                    find_shortest_path(next_city, count + 1, new_distance);
                }
            }
        }
    }

    // 回溯：取消標記，以便其他路徑可以訪問此城市
    Visited[current_city] = 0;
}

int main() {
    scanf("%d", &N);

    // 初始化距離矩陣 (讀取輸入)
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &Point_array[i][j]);
        }
    }

    int walk_break_city_index; // 第幾個城市發生中斷 (注意是第幾個, index C)
    int break_u, break_v;      // 中斷的兩端城市 u, v
    scanf("%d", &walk_break_city_index);
    scanf("%d %d", &break_u, &break_v);

    // --- 第一階段：找到初始最短路徑 ---
    memset(Visited, 0, sizeof(Visited)); // 清空 Visited 陣列
    min_distance = INT_MAX;              // 重設最小距離
    find_shortest_path(1, 1, 0);         // 從城市 1 開始，已訪問 1 個，距離 0

    // 儲存初始最佳路徑和其走到第 C 個城市時的狀態
    int initial_best_path[SIZE];
    memcpy(initial_best_path, Best_path, N * sizeof(int));
    int initial_distance_prefix = 0;
    int city_at_break = -1;
    memset(Visited, 0, sizeof(Visited)); // 重新使用 Visited 標記走過的前綴

    // 計算前 C 個城市的路徑和距離，並標記
    for (int i = 0; i < walk_break_city_index; ++i) {
        Visited[initial_best_path[i]] = 1; // 標記前綴城市
        if (i > 0) {
            initial_distance_prefix +=
                Point_array[initial_best_path[i - 1]][initial_best_path[i]];
        }
        if (i == walk_break_city_index - 1) {
            city_at_break = initial_best_path[i]; // 記錄下發生中斷時所在的城市
        }
    }

    // --- 第二階段：處理道路中斷並尋找剩餘路徑 ---

    // 修改距離矩陣，表示道路中斷
    int original_uv = Point_array[break_u][break_v]; // (可選) 保存原始值
    int original_vu = Point_array[break_v][break_u];
    Point_array[break_u][break_v] = -1;
    Point_array[break_v][break_u] = -1;

    // 從 city_at_break 開始，尋找訪問剩下 (N - walk_break_city_index)
    // 個城市的最短路徑
    min_distance = INT_MAX;           // 重設最小距離，尋找剩餘路徑的最短距離
    int remaining_path[SIZE];         // 存放剩餘路徑
    int final_path[SIZE];             // 最終完整路徑
    int remaining_min_dist = INT_MAX; // 剩餘路徑的最小距離
    int temp_remaining_path[SIZE];    // 臨時存放剩餘路徑

    // 需要一個修改版的回溯函數或類似邏輯來處理剩餘部分
    // 這裡為了簡化，我們重新定義一個回溯函數，但目標不同
    // (或者，更複雜但可能更優的方式是修改原回溯函數以接受起始狀態)

    // --- 使用一個新的回溯函數 find_remaining_path ---
    // 這個函數需要知道哪些點已經在初始路徑中(Visited 陣列已經標記好了)
    // 並且從 city_at_break 開始

    void find_remaining_path(int current_city, int count_remaining,
                             int current_rem_distance) {
        // count_remaining: 在剩餘路徑中已訪問的城市數量 (不含起始的
        // city_at_break)
        temp_remaining_path[count_remaining] = current_city;
        Visited[current_city] = 1; // 標記訪問 (雖然它可能在 prefix 裡已經是 1)

        // 基底情況: 加上初始 C 個城市，總共訪問了 N 個
        if (walk_break_city_index + count_remaining == N) {
            if (current_rem_distance < remaining_min_dist) {
                remaining_min_dist = current_rem_distance;
                // 儲存的是從 city_at_break *之後* 的路徑
                memcpy(remaining_path, temp_remaining_path + 1,
                       count_remaining * sizeof(int));
            }
        } else {
            for (int next_city = 1; next_city <= N; ++next_city) {
                // 條件: 有路徑(修改後), 且該城市不在已訪問集合中(包括 prefix
                // 和當前剩餘路徑)
                if (Point_array[current_city][next_city] != -1 &&
                    !Visited[next_city]) {
                    int new_rem_distance = current_rem_distance +
                                           Point_array[current_city][next_city];
                    if (new_rem_distance < remaining_min_dist) { // 剪枝
                        find_remaining_path(next_city, count_remaining + 1,
                                            new_rem_distance);
                    }
                }
            }
        }
        // 回溯: 只有當這個點 *不是* 初始 prefix 的一部分時才需要重置 visited
        // 為了簡化，這裡先不重置 prefix 的 visited 狀態，因為
        // find_remaining_path 不會回到 prefix 裡的點 (除了起點 city_at_break)
        // 如果 next_city 不是 prefix 的一部分，則 Visited[next_city] = 0;
        // 但因為我們檢查
        // !Visited[next_city]，所以只需要在遞迴返回後將當前加入的點（如果它不在
        // prefix 裡）標記回 0
        int is_in_prefix = 0;
        for (int i = 0; i < walk_break_city_index; ++i) {
            if (current_city == initial_best_path[i]) {
                is_in_prefix = 1;
                break;
            }
        }
        if (!is_in_prefix) {
            Visited[current_city] = 0; // 只有非 prefix 的點才需要回溯清除標記
        }
        // 注意：更嚴謹的回溯需要仔細處理 Visited 狀態，特別是起點 city_at_break
        // 一個替代方法是傳遞一個副本 Visited 數組或使用不同的標記值。
    }

    // 為了正確執行，需要重置 Visited 陣列，僅保留 prefix 的標記
    memset(Visited, 0, sizeof(Visited));
    for (int i = 0; i < walk_break_city_index; ++i) {
        Visited[initial_best_path[i]] = 1;
    }

    find_remaining_path(city_at_break, 0,
                        0); // 從中斷點開始，已訪問0個剩餘點，剩餘距離0

    // --- 第三階段：組合結果並輸出 ---
    int total_distance = initial_distance_prefix + remaining_min_dist;

    // 構建最終路徑
    memcpy(final_path, initial_best_path, walk_break_city_index * sizeof(int));
    memcpy(final_path + walk_break_city_index, remaining_path,
           (N - walk_break_city_index) * sizeof(int));

    // 輸出結果
    for (int i = 0; i < N; i++) {
        printf("%d%c", final_path[i], (i == N - 1) ? '\n' : ' ');
    }
    printf("%d\n", total_distance);

    return 0;
}