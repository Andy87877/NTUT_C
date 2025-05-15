#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 評分類別:
typedef enum scoreType_s { G, GPA, S } scoreType_t;
// 等第評分:
typedef enum G_s{Aplus,A,Aduce,Bplus,B,Bduce,Cplus,C,Cduce,F,X}G_t;
// GPA評分:
typedef enum
GPA_s{b4dot3,b4dot0,b3dot7,b3dot3,b3dot0,b2dot7,b2dot3,b2dot0,b1dot7,b1,b0}GPA_t;
// 百分制區間評分:
typedef enum S_s{b90to100,b85to89,b80to84,
b77to79,b73to76,b70to72,b67to69,b63to66,b60to62,b1to59,b0to0}S_t;
// 學生分數類型:
typedef union student_s{
    int score;
    G_t G;
    GPA_t GPA;
    S_t S;
}student_t;

int array_score[11] = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};
char G_rank[11][5] = {"A+", "A", "A-", "B+", "B", "B-",
                      "C+", "C", "C-", "F",  "X"};
float GPA_rank[11] = {4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1, 0};
char S_rank[11][11] = {"90-100", "85-89", "80-84", "77-79", "73-76", "70-72",
                       "67-69",  "63-66", "60-62", "1-59",  "0"};

char type_name[3][5] = {"G", "GPA", "S"};

// main
int main() {
    int type_count;
    scanf("%d", &type_count);

    // 輸入type
    // scoreType_t type_array[4];
    char type_array[4][4];
    for (int i = 0; i < type_count; i++) {
        scanf("%s", &type_array[i]);
        getchar();
    }

    // 輸入學生
    int student_count;
    scanf("%d", &student_count);

    int student_ID[10];
    // student_t student_score_t[10];
    int student_score_array[10];

    for (int j = 0; j < student_count; j++) {
        scanf("%d", &student_ID[j]);

        int now_score = 0;

        for (int i = 0; i < type_count; i++) {
            if (strcmp(type_array[i], "G") == 0) {
                char G_now[5];
                scanf("%s", &G_now);
                getchar();

                for (int k = 0; k < 11; k++) {
                    if (strcmp(G_now, G_rank[k]) == 0) {
                        now_score += array_score[k];
                        break;
                    }
                }
            }

            if (strcmp(type_array[i], "GPA") == 0) {
                float GPA_now;
                scanf("%f", &GPA_now);
                getchar();

                for (int k = 0; k < 11; k++) {
                    if (GPA_now == GPA_rank[k]) {
                        now_score += array_score[k];
                        break;
                    }
                }
            }

            if (strcmp(type_array[i], "S") == 0) {
                char S_now[11];
                scanf("%s", &S_now);
                getchar();

                for (int k = 0; k < 11; k++) {
                    if (strcmp(S_now, S_rank[k]) == 0) {
                        now_score += array_score[k];
                        break;
                    }
                }
            }
        }

        student_score_array[j] = now_score;
    }

    // 排序
    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < student_count; j++) {
            int tmp;
            if (student_score_array[i] < student_score_array[j]) {
                tmp = student_score_array[i];
                student_score_array[i] = student_score_array[j];
                student_score_array[j] = tmp;

                tmp = student_ID[i];
                student_ID[i] = student_ID[j];
                student_ID[j] = tmp;
            }
        }
    }

    // 輸出
    for (int i = 0; i < student_count; i++) {
        int score = student_score_array[i] / type_count;
        printf("%d %d\n", student_ID[i], score);
    }
}