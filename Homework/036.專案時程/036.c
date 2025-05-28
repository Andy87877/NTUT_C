#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 105

typedef struct {
        int spend_day;
        int wait_day;
        int wait_size;
        int wait_array[MAX_SIZE];
        int ok; // 0還沒好 1好了
} project;      // 自己的project

typedef struct {
        int wait_size;
        int wait_array[MAX_SIZE];
} wait_project; // 讓別的project等待

void judge() {
    int M;
    scanf("%d", &M);

    project array_project[MAX_SIZE];
    wait_project array_wait_project[MAX_SIZE];

    // input
    for (int i = 1; i < M + 1; i++) {
        project now_project;
        wait_project now_wait_project;

        now_project.wait_size = 0;
        now_project.ok = 0;
        now_project.wait_day = 0;

        int day;
        scanf("%d", &day);

        now_project.spend_day = day;

        int wait_size;
        scanf("%d", &wait_size);
        now_wait_project.wait_size = wait_size;

        int wait_array[MAX_SIZE];
        for (int j = 0; j < wait_size; j++) {
            scanf("%d", &wait_array[j]);
            now_wait_project.wait_array[j] = wait_array[j];
        }

        array_project[i] = now_project;
        array_wait_project[i] = now_wait_project;
    }

    // 等待的project要到 project前面
    for (int i = 1; i < M + 1; i++) {
        project now_project = array_project[i];
        wait_project now_wait_project = array_wait_project[i];

        // project的等待序列
        for (int j = 0; j < now_wait_project.wait_size; j++) {
            int wait_index = now_wait_project.wait_array[j];
            int size = array_project[wait_index].wait_size;
            array_project[wait_index].wait_size += 1;
            array_project[wait_index].wait_array[size] = i;
        }
    }

    int ok_size = 0;
    int answer_time = 0;

    while (ok_size != M) {
        for (int i = 1; i < M + 1; i++) {
            project now_project = array_project[i];
            if (now_project.ok == 1) continue;

            int ok_flag = 1;

            int wait_size = now_project.wait_size;
            int now_wait_time = 0;
            for (int j = 0; j < wait_size; j++) {
                int wait_index = now_project.wait_array[j];
                if (array_project[wait_index].ok == 0) {
                    ok_flag = 0;
                    break;
                }

                int wait_time = array_project[wait_index].spend_day +
                                array_project[wait_index].wait_day;
                if (now_wait_time < wait_time) {
                    now_wait_time = wait_time;
                }
            }

            if (ok_flag) {
                ok_size++;
                now_project.ok = 1;
                now_project.wait_day = now_wait_time;
                array_project[i] = now_project;

                if (answer_time <= now_wait_time + now_project.spend_day) {
                    answer_time = now_wait_time + now_project.spend_day;
                }
            }
        }
    }

    printf("%d\n", answer_time);
}

int main() {
    int N;
    scanf("%d", &N);

    for (int times = 0; times < N; times++) {
        judge();
    }
}