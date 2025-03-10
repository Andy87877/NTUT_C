#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 檢查特殊的case
int is_special_case(char judge_str[]) {
    int len = strlen(judge_str);
    int is_special = 0;

    if (judge_str[0] == '.') {
        is_special = 1;
    }
    if (judge_str[0] == '0') {
        if (len == 2) {
            is_special = 1;
        }
        if (len >= 3 && judge_str[1] != '.') {
            is_special = 1;
        }
    }
    if (judge_str[0] == '-' && strcmp("-0", judge_str) == 0) {
        is_special = 1;
    }
    return is_special;
}

// 判斷字串的類型
char *judge(char judge_str[]) {
    int len = strlen(judge_str);
    int start_index = 0;

    char out[1000];
    char *output = (char *)malloc(sizeof(char) * 100000);

    // 檢查特殊的case
    if (judge_str[0] == '0') {
        if (len == 1) {
            sprintf(out, " - Positive Integer\n");
            strcat(output, out);
            return output;
        }
    }

    int is_special = is_special_case(judge_str);
    if (is_special == 1) {
        sprintf(out, " - Error\n");
        strcat(output, out);
        return output;
    }

    // 狀態機
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
                sprintf(out, " - Error\n");
                strcat(output, out);
                return output;
            }
            float_status = 1;
        } else if (Key >= '0' && Key <= '9') {
            if (number_status == 0) {
                number_status = 1;
            }
        } else if ((Key >= 'A' && Key <= 'Z') || (Key == '_')) {
            if (number_status == 1 && variable_status == 0) {
                sprintf(out, " - Error\n");
                strcat(output, out);
                return output;
            }
            variable_status = 1;
        } else if ((Key <= 'z')) {
            if (Key >= 'a') {
                if (number_status == 1 && variable_status == 0) {
                    sprintf(out, " - Error\n");
                    strcat(output, out);
                    return output;
                }
                variable_status = 1;
            }
        } else {
            sprintf(out, " - Error\n");
            strcat(output, out);
            return output;
        }
    }

    // 輸出類型
    if (variable_status == 1) {
        sprintf(out, " - Identifier\n");
        strcat(output, out);
    } else if (float_status == 1) {
        if (negative_status == 1) {
            sprintf(out, " - Negative Floating\n");
            strcat(output, out);
        } else {
            sprintf(out, " - Positive Floating\n");
            strcat(output, out);
        }
    } else {
        // number_status == 1
        if (negative_status == 1) {
            sprintf(out, " - Negative Integer\n");
            strcat(output, out);
        } else {
            sprintf(out, " - Positive Integer\n");
            strcat(output, out);
        }
    }
    return output;
}

char *FMS(char *s) {
    char out[1000];
    char *output = (char *)malloc(sizeof(char) * 100000);

    char judge_str[100];
    int now_temp_index = 0;
    for (int index = 0; index < strlen(s); index++) {
        if (s[index] == ' ') {
            strcat(output, judge_str);
            strcat(output, judge(judge_str));
            memset(judge_str, '\0', sizeof(judge_str));
            now_temp_index = 0;
        } else {
            judge_str[now_temp_index] = s[index];
            now_temp_index++;
            judge_str[now_temp_index] = '\0';
        }
    }

    return output;
}