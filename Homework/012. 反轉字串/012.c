#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 判斷字串是否符合規定 (2.字串的開頭與結尾只能是英文字母（a-z, A-Z）或底線 (‘_’)，否則輸出 Error 並立即結束程式。)
void Judge_char_Error(char check_char) {
    // printf("%c\n", check_char);
    if ((check_char == '_') || (check_char >= 'a' && check_char <= 'z') ||
        (check_char >= 'A' && check_char <= 'Z')) {
        return;
    }

    printf("Error\n");
    exit(0); // 強制結束
}

// 判斷字元是否符合規定
void Judge_string_Error(char *string) {
    int len = strlen(string);
    Judge_char_Error(string[0]);
    Judge_char_Error(string[len - 1]);
}

// 反轉字串(輸出)
void Reverse_string(char *string) {
    int len = strlen(string);
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", string[i]);
    }
    printf("\n");
}

// 不計空白字元的最長原始字串
void Longest_string(char *string1, char *string2) {
    int string1_len = strlen(string1);
    int string2_len = strlen(string2);
    for (int i = 0; i < strlen(string1); i++) {
        if (string1[i] == ' ') {
            string1_len--;
        }
    }
    for (int i = 0; i < strlen(string2); i++) {
        if (string2[i] == ' ') {
            string2_len--;
        }
    }

    if (string1_len >= string2_len) {
        printf("%s\n", string1);
    } else {
        printf("%s\n", string2);
    }
}

int main() {
    char string_1[100], string_2[100];
    fgets(string_1, sizeof(string_1), stdin);
    fgets(string_2, sizeof(string_2), stdin);
    string_1[strlen(string_1) - 1] = '\0';
    string_2[strlen(string_2) - 1] = '\0';


    // 判斷字元是否符合規定
    Judge_string_Error(string_1);
    Judge_string_Error(string_2);

    // 反轉字串
    Reverse_string(string_1);
    Reverse_string(string_2);

    // 不計空白字元的最長原始字串
    Longest_string(string_1, string_2);
}