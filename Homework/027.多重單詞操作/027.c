#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

int Check_replace_str(char now_string[], char P_word[], int size) {
    if (strcmp(now_string, P_word) == 0) {
        return 1;
    }

    if (strlen(now_string) - 1 != strlen(P_word)) {
        return 0;
    }

    for (int i = 0; i < strlen(P_word); i++) {
        if (now_string[i] != P_word[i]) {
            return 0;
        }
    }

    char check_array[6] = ".,!?;:";
    for (int j = 0; j < 6; j++) {
        if (now_string[strlen(now_string) - 1] == check_array[j]) {
            return 1;
        }
    }

    return 0;
}

void Get_str_vector(char string_vector[][SIZE], char original_string[],
                    int replace_index_vector[], char P_word[],
                    int* now_vector_index, int* replace_index) {
    *now_vector_index = 0;
    *replace_index = 0;

    replace_index_vector[0] = -1;

    int now_string_index = 0;

    char now_string[SIZE];
    int original_size = strlen(original_string);
    now_string[0] = '\0';

    for (int i = 0; i < original_size; i++) {
        char now_char = original_string[i];
        if (now_char == ' ' || now_char == '\0' || now_char == '\n') {
            strcpy(string_vector[*now_vector_index], now_string);

            int check = 0;
            check = Check_replace_str(now_string, P_word, now_string_index);
            if (check == 1) {
                replace_index_vector[*replace_index] = *now_vector_index;
                replace_index_vector[*replace_index + 1] = -1;
                (*replace_index)++;
            }

            now_string[0] = '\0';
            (*now_vector_index)++;
            now_string_index = 0;
        } else {
            now_string[now_string_index] = now_char;
            now_string[now_string_index + 1] = '\0';
            now_string_index++;
        }
    }
}

// 第一行輸出單詞取代後的結果。
void Answer_1(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            printf("%s", Q_word);

            char check_array[6] = ".,!?;:";

            for (int j = 0; j < 6; j++) {
                if (now_string[str_size - 1] == check_array[j]) {
                    printf("%c", check_array[j]);
                    break;
                }
            }

            now_replace_index++;
        } else {
            printf("%s", now_string);
        }

        if (i != vector_size - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

// 第二行輸出單詞前插入後的結果。
void Answer_2(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            printf("%s ", Q_word);

            now_replace_index++;
        }
        printf("%s", now_string);

        if (i != vector_size - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

// 第三行輸出單詞後插入後的結果。
void Answer_3(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        printf("%s", now_string);

        if (replace_index_vector[now_replace_index] == i) {
            printf(" %s", Q_word);

            now_replace_index++;
        }

        if (i != vector_size - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

// 第四行輸出單詞刪除後的結果。
void Answer_4(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, int replace_size) {
    int now_replace_index = 0;
    int isnot_first_words = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            now_replace_index++;
            continue;
        }

        if (isnot_first_words == 1) {
            printf(" ");
        }
        printf("%s", now_string);
        isnot_first_words = 1;
    }

    printf("\n");
}

// 第五行輸出單詞順序反轉後的結果。
void Answer_5(char string_vector[][SIZE], int vector_size) {
    int now_replace_index = 0;
    for (int i = vector_size - 1; i >= 0; i--) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);

        printf("%s", now_string);

        if (i != 0) {
            printf(" ");
        }
    }

    printf("\n");
}

int main() {
    char original_string[SIZE];      // 原始字串
    char P_word[SIZE], Q_word[SIZE]; // P Q 被取代和取代的字

    char string_vector[SIZE][SIZE]; // 字串vector
    int replace_index_vector[SIZE]; // 取代單詞的位置

    int vector_size = 0;
    int replace_size = 0;

    fgets(original_string, SIZE, stdin);

    scanf("%s", &P_word);
    scanf("%s", &Q_word);

    Get_str_vector(string_vector, original_string, replace_index_vector, P_word,
                   &vector_size, &replace_size);

    // 輸出各行需要的答案
    Answer_1(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_2(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_3(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_4(string_vector, replace_index_vector, vector_size, replace_size);
    Answer_5(string_vector, vector_size);
}