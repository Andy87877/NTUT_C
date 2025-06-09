#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
        int number; // 教室標號
        int volume; // 教室容量
} Class_struct;

typedef struct {
        int number;     // 課程標號
        int amount;     // 人數
        int start_time; // 開始時間
        int end_time;   // 結束時間
} Course_struct;

Class_struct class_array[MAX_SIZE];
Course_struct course_array[MAX_SIZE];
int class_amount, course_amount;

// b=0表示不考慮人數限制
void No_amount_limit() {}

int main() {
    scanf("%d %d", &class_amount, &course_amount);

    for (int m = 0; m < class_amount; m++) {
        scanf("%d %d", &class_array[m].number, &class_array[m].volume);
    }

    for (int n = 0; n < course_amount; n++) {
        scanf("%d %d %d %d", &course_array[n].number, &course_array[n].amount,
              &course_array[n].start_time, &course_array[n].end_time);
    }

    // input_type 最後一行，正整數b
    // b=0表示不考慮人數限制，b=1，表示要考慮人數限制。b=2，表示要考慮人數限制，且要輸出課程編號與教室編號。
    int b;
    scanf("%d", &b);
}

/*
輸出說明
1.計算安排到的所有課程，輸出能使用最高總時數。
2.計算安排到的所有課程，輸出能使用的最多課程數。若b=2，輸出課程編號與教室。
3. 若一個教室有多個課程，課程取編號數小的優先輸出。
*/