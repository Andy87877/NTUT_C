#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 60

// 檢查大寫或小寫
int Check_big_or_small(char check_char) {
    if (check_char >= 'A' && check_char <= 'Z') {
        return 1; // 大寫
    }
    return 0; // 小寫
}

// 輸入與判斷答案
int Judge() {
    char string[SIZE];
    string[0] = '\0';
    int k;

    scanf("%s %d", &string, &k);

    int big_times = 0, small_times = 0;
    int times_array[SIZE], index = 0;
    int is_big_check = 0;

    // 找連續大/小寫的次數
    for (int i = 0; i < strlen(string); i++) {
        char now_char = string[i];
        int is_big = Check_big_or_small(now_char);

        if (is_big_check != is_big && i != 0) {
            if (is_big_check == 1) {
                times_array[index] = big_times;
                big_times = 0;
            } else {
                times_array[index] = small_times;
                small_times = 0;
            }
            index++;
        }

        if (is_big == 1) {
            big_times++;
            is_big_check = 1;
        } else {
            small_times++;
            is_big_check = 0;
        }
    }
    // last
    if (is_big_check == 1) {
        times_array[index] = big_times;
        big_times = 0;
    } else {
        times_array[index] = small_times;
        small_times = 0;
    }
    index++;

    int size = index, answer = 0;
    int is_front_large = 0;

    if (size == 1) return 0;

    // 判斷答案
    for (int i = 0; i < size; i++) { // 開頭
        int tmp_answer = 0;
        for (int j = i; j < size; j++) { // 結尾
            // printf("%d ", times_array[j]);
            if (times_array[j] < k) break;

            tmp_answer++;
            if (times_array[j] > k && j != i) break;
        }
        // printf("\n");

        if (tmp_answer > answer && tmp_answer != 1) {
            answer = tmp_answer;
        }
    }

    answer = answer * k;

    return answer;
}

int main() {
    int times;
    scanf("%d", &times);

    for (int t = 0; t < times; t++) {
        int answer = 0;
        answer = Judge();
        printf("%d\n", answer);
    }
}