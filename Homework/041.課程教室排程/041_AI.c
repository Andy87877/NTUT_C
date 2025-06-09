#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_M 10
#define MAX_N 100
#define MAX_TIME 24

// 定義教室結構
typedef struct {
        int id;
        int capacity;
        bool schedule[MAX_TIME]; // 時間表，true 表示該時段已被佔用
        int assigned_courses_count;
        int assigned_course_ids[MAX_N];
} Classroom;

// 定義課程結構
typedef struct {
        int id;
        int students;
        int start_time;
        int end_time;
        int duration; // 課程持續時間 (end_time - start_time)
} Course;

// 全域變數，儲存問題資料和最佳解
int M, N;                        // 教室數量，課程數量
Classroom classrooms[MAX_M + 1]; // 教室陣列
Course courses[MAX_N];           // 課程陣列
int b_option;                    // 選項 b

int max_total_hours = INT_MIN;   // 最佳解的總時數
int max_total_courses = INT_MIN; // 最佳解的總課程數
int best_assignment_count = 0;   // 最佳解中排定的課程數量
// 儲存最佳排定細節：每對 (課程ID, 教室ID)
int best_assignment_details[MAX_N][2];

// 排序課程
int compareCourses(const void *a, const void *b) {
    Course *courseA = (Course *)a;
    Course *courseB = (Course *)b;

    // 持續時間降序
    if (courseA->duration != courseB->duration) {
        return courseB->duration - courseA->duration;
    }
    // 課程ID降序
    return courseB->id - courseA->id;
}

// 排序最佳排定結果：先依課程ID升序，再依教室ID升序
int compareAssignmentDetails(const void *a, const void *b) {
    // detailA[0] = 課程ID, detailA[1] = 教室ID
    int *detailA = (int *)a;
    int *detailB = (int *)b;

    // 課程編號排序
    if (detailA[0] != detailB[0]) {
        return detailA[0] - detailB[0];
    }
    // 教室編號升序排列
    return detailA[1] - detailB[1];
}

/*
// course_idx: 當前正在考慮的課程索引
// current_hours: 目前累計的總時數
// current_courses_count: 目前排定的課程總數
// current_assignment: 暫存目前排定方案的陣列 (課程ID, 教室ID 對)
// current_assignment_idx: current_assignment 陣列中的當前索引
*/
void dfs(int course_idx, int current_hours, int current_courses_count,
         int current_assignment[MAX_N][2], int current_assignment_idx) {
    // 遞迴終止條件：所有課程都已考慮完畢
    if (course_idx == N) {
        // 檢查當前解是否優於已找到的最佳解
        // 優先比較總時數，若相同則比較總課程數
        if (current_hours > max_total_hours) {
            max_total_hours = current_hours;
            max_total_courses = current_courses_count;
            best_assignment_count = current_assignment_idx;
            // 複製當前排定方案到最佳解儲存區
            for (int i = 0; i < current_assignment_idx; i++) {
                best_assignment_details[i][0] = current_assignment[i][0];
                best_assignment_details[i][1] = current_assignment[i][1];
            }
        } else if (current_hours == max_total_hours) {
            if (current_courses_count > max_total_courses) {
                max_total_courses = current_courses_count;
                best_assignment_count = current_assignment_idx;
                // 複製當前排定方案到最佳解儲存區
                for (int i = 0; i < current_assignment_idx; i++) {
                    best_assignment_details[i][0] = current_assignment[i][0];
                    best_assignment_details[i][1] = current_assignment[i][1];
                }
            }
        }
        return;
    }

    // DFS 不排定當前課程
    dfs(course_idx + 1, current_hours, current_courses_count,
        current_assignment, current_assignment_idx);

    // 將當前課程排定到可用的教室
    Course current_course = courses[course_idx];

    // 遍歷所有教室
    for (int i = 1; i <= M; i++) {
        Classroom *room = &classrooms[i];

        // 檢查教室容量限制 (如果 b = 1 or 2)
        if ((b_option == 1 || b_option == 2) &&
            current_course.students > room->capacity) {
            continue; // 因容量不足而無法排定
        }

        // 檢查時間衝突
        bool conflict = false;
        for (int t = current_course.start_time; t < current_course.end_time;
             t++) {
            if (room->schedule[t]) {
                conflict = true; // 時間已佔用
                break;
            }
        }

        // 沒有時間衝突
        if (!conflict) {
            // 排定課程：將時間段標記為已佔用
            for (int t = current_course.start_time; t < current_course.end_time;
                 t++) {
                room->schedule[t] = true;
            }

            // 暫時記錄這次排定
            current_assignment[current_assignment_idx][0] = current_course.id;
            current_assignment[current_assignment_idx][1] = room->id;

            // 進行遞迴呼叫，考慮下一門課程
            dfs(course_idx + 1, current_hours + current_course.duration,
                current_courses_count + 1, current_assignment,
                current_assignment_idx + 1);

            // 回溯
            for (int t = current_course.start_time; t < current_course.end_time;
                 t++) {
                room->schedule[t] = false;
            }
        }
    }
}

int main() {
    // 教室數量 M 和課程數量 N
    scanf("%d %d", &M, &N);

    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &classrooms[i].id, &classrooms[i].capacity);
        for (int t = 0; t < MAX_TIME; t++) {
            classrooms[i].schedule[t] = false;
        }
        classrooms[i].assigned_courses_count = 0;
    }

    // 讀取課程資訊
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &courses[i].id, &courses[i].students,
              &courses[i].start_time, &courses[i].end_time);
        courses[i].duration = courses[i].end_time - courses[i].start_time;
    }

    // 讀取選項 b
    scanf("%d", &b_option);

    // 對課程進行排序
    qsort(courses, N, sizeof(Course), compareCourses);

    // 用於 DFS 的臨時排定陣列
    int temp_assignment[MAX_N][2];

    // 開始判斷
    dfs(0, 0, 0, temp_assignment, 0);

    printf("max hours %d\n", max_total_hours);
    printf("max courses %d\n", max_total_courses);

    // 輸出詳細的課程排定列表
    if (b_option == 2) {
        qsort(best_assignment_details, best_assignment_count, sizeof(int[2]),
              compareAssignmentDetails);
        for (int i = 0; i < best_assignment_count; i++) {
            printf("%d %d\n", best_assignment_details[i][0],
                   best_assignment_details[i][1]);
        }
    }

    return 0;
}