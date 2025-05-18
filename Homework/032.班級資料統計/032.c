#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_s {
        char name[50];
        int score;
} student_t;

// 輸入
void input(student_t student[], int n) {
    char name[50];
    int score;

    scanf("%s", &name);
    scanf("%d", &score);

    strcpy(student[n].name, name);
    student[n].score = score;
}

// 找最高的分數
void getHigh(student_t s[], int n, char name[], int *highScore) {
    *highScore = s[0].score;
    strcpy(name, s[0].name);

    for (int i = 1; i < n; i++) {
        if (*highScore < s[i].score) {
            *highScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// 找最低的分數
void getLow(student_t s[], int n, char name[], int *lowScore) {
    *lowScore = s[0].score;
    strcpy(name, s[0].name);

    for (int i = 1; i < n; i++) {
        if (*lowScore > s[i].score) {
            *lowScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// 找平均
int getAverage(student_t s[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += s[i].score;
    }
    return sum / n;
}

// 找中位數
int getMedian(student_t s[], int n) {
    // sort

    char tmp_name[50];
    int tmp_score;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i].score > s[j].score) {
                tmp_score = s[i].score;
                s[i].score = s[j].score;
                s[j].score = tmp_score;

                strcpy(tmp_name, s[i].name);
                strcpy(s[i].name, s[j].name);
                strcpy(s[j].name, tmp_name);
            }
        }
    }

    // 找中位數
    int mid, mid_index;
    if (n % 2 == 1) {
        mid_index = n / 2;
        mid = s[mid_index].score;
    } else {
        mid_index = n / 2;
        mid = s[mid_index - 1].score + s[mid_index].score;
        mid /= 2;
    }
    return mid;
}

int main() {
    int n;
    scanf("%d", &n);
    student_t student[20];

    for (int i = 0; i < n; i++) {
        input(student, i);
    }

    char high_name[50];
    int highScore;
    getHigh(student, n, high_name, &highScore);
    printf("%s %d\n", high_name, highScore);

    char low_name[50];
    int lowScore;
    getLow(student, n, low_name, &lowScore);
    printf("%s %d\n", low_name, lowScore);

    int average_score;
    average_score = getAverage(student, n);
    printf("%d\n", average_score);

    int mid_score;
    mid_score = getMedian(student, n);
    printf("%d\n", mid_score);
}