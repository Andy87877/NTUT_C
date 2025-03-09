#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 檢查特殊的case
int is_special_case(char judge_str[]) {
    int len = strlen(judge_str);
    if (judge_str[0] == '.') {
        printf("Error\n");
        return 1;
    }
    if (judge_str[0] == '0') {
        if (len == 1) {
            printf("Positive integer\n");
            return 1;
        }
        if (len == 2) {
            printf("Error\n");
            return 1;
        }
        if (len >= 3 && judge_str[1] != '.') {
            printf("Error\n");
            return 1;
        }
    }
    if (judge_str[0] == '-' && strcmp("-0", judge_str) == 0) {
        printf("Error\n");
        return 1;
    }
    return 0;
}

// 判斷字串的類型
void judge(char judge_str[]) {
    int len = strlen(judge_str);
    int start_index = 0;

    // 檢查特殊的case
    if (is_special_case(judge_str)) {
        return;
    }

    int float_status = 0;
    int variable_status = 0;
    int number_status = 0;
    int negative_status = 0;

    // 跳過負數的符號
    if (judge_str[0] == '-') {
        start_index = 1;
        negative_status = 1;
    }

    // 檢查類型
    for (int i = start_index; i < len; i++) {
        char Key = judge_str[i];
        if (Key == '.') {
            if (float_status == 1 || variable_status == 1 || i == len - 1) {
                printf("Error\n");
                return;
            }
            float_status = 1;
        } else if (Key >= '0' && Key <= '9') {
            if (number_status == 0) {
                number_status = 1;
            }
        } else if ((Key >= 'a' && Key <= 'z') || (Key >= 'A' && Key <= 'Z') ||
                   Key == '_') {
            if (number_status == 1 && variable_status == 0) {
                printf("Error\n");
                return;
            }
            variable_status = 1;
        } else {
            printf("Error\n");
            return;
        }
    }

    // 輸出類型
    if (variable_status == 1) {
        printf("Identifier\n");
    } else if (float_status == 1) {
        if (negative_status == 1) {
            printf("Negative Floating\n");
        } else {
            printf("Positive Floating\n");
        }
    } else if (number_status == 1) {
        if (negative_status == 1) {
            printf("Negative Integer\n");
        } else {
            printf("Positive Integer\n");
        }
    }
}

int main() {
    while (1) {
        char judge_str[100];
        scanf("%s", judge_str);
        if (strcmp(judge_str, "#") == 0) {
            break;
        }
        printf("%s - ", judge_str);
        judge(judge_str);
    }
}