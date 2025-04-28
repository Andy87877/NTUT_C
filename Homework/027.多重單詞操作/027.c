#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 // 定義常數 SIZE，作為陣列大小使用

// 檢查現在的單字 now_string 是否符合要取代的 P_word
int Check_replace_str(char now_string[], char P_word[], int size) {
    // 如果完全相同，直接回傳 1
    if (strcmp(now_string, P_word) == 0) {
        return 1;
    }

    // 如果長度不符合（now_string 少一個字元），則無法符合條件
    if (strlen(now_string) - 1 != strlen(P_word)) {
        return 0;
    }

    // 逐字比較，如果不相同則回傳 0
    for (int i = 0; i < strlen(P_word); i++) {
        if (now_string[i] != P_word[i]) {
            return 0;
        }
    }

    // 最後一個字元如果是標點符號，且前面符合，則回傳 1
    char check_array[6] = ".,!?;:";
    for (int j = 0; j < 6; j++) {
        if (now_string[strlen(now_string) - 1] == check_array[j]) {
            return 1;
        }
    }

    // 否則回傳 0
    return 0;
}

// 把原始字串 original_string 切成單字存在 string_vector 中
// 並且找出哪些單字需要取代，記錄在 replace_index_vector
void Get_str_vector(char string_vector[][SIZE], char original_string[],
                    int replace_index_vector[], char P_word[],
                    int* now_vector_index, int* replace_index) {
    *now_vector_index = 0; // 初始化目前單字數量
    *replace_index = 0;    // 初始化取代單字數量

    replace_index_vector[0] = -1; // 先設第一個為 -1（標記用）

    int now_string_index = 0;                    // 當前累積單字的索引
    char now_string[SIZE];                       // 暫存目前累積的單字
    int original_size = strlen(original_string); // 原始字串長度
    now_string[0] = '\0';                        // 初始化

    // 遍歷整個原始字串
    for (int i = 0; i < original_size; i++) {
        char now_char = original_string[i];
        if (now_char == ' ' || now_char == '\0' || now_char == '\n') {
            // 遇到空白或結尾時，把目前的單字存到 string_vector
            strcpy(string_vector[*now_vector_index], now_string);

            // 檢查這個單字需不需要取代
            int check = 0;
            check = Check_replace_str(now_string, P_word, now_string_index);
            if (check == 1) {
                replace_index_vector[*replace_index] = *now_vector_index;
                replace_index_vector[*replace_index + 1] = -1; // 確保後面是 -1
                (*replace_index)++;
            }

            // 重置 now_string
            now_string[0] = '\0';
            (*now_vector_index)++;
            now_string_index = 0;
        } else {
            // 不是空白就把字元加到 now_string
            now_string[now_string_index] = now_char;
            now_string[now_string_index + 1] = '\0'; // 記得加上結尾字元
            now_string_index++;
        }
    }
}

// 第一行輸出：把要取代的單字換成 Q_word
void Answer_1(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            // 如果是要取代的單字
            printf("%s", Q_word);

            // 如果原單字最後有標點，要補上標點
            char check_array[6] = ".,!?;:";

            for (int j = 0; j < 6; j++) {
                if (now_string[str_size - 1] == check_array[j]) {
                    printf("%c", check_array[j]);
                    break;
                }
            }

            now_replace_index++;
        } else {
            // 不是取代的單字，原樣輸出
            printf("%s", now_string);
        }

        if (i != vector_size - 1) {
            printf(" "); // 單字間加空白
        }
    }

    printf("\n");
}

// 第二行輸出：在找到的單字【前面】插入 Q_word
void Answer_2(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            // 找到要插入的地方，先印 Q_word
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

// 第三行輸出：在找到的單字【後面】插入 Q_word
void Answer_3(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, char Q_word[]) {
    int now_replace_index = 0;
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        printf("%s", now_string);

        if (replace_index_vector[now_replace_index] == i) {
            // 找到要插入的地方，印 Q_word
            printf(" %s", Q_word);
            now_replace_index++;
        }

        if (i != vector_size - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

// 第四行輸出：把要取代的單字直接【刪除】
void Answer_4(char string_vector[][SIZE], int replace_index_vector[],
              int vector_size, int replace_size) {
    int now_replace_index = 0;
    int isnot_first_words = 0; // 用來避免開頭空白
    for (int i = 0; i < vector_size; i++) {
        char now_string[SIZE];
        strcpy(now_string, string_vector[i]);
        int str_size = strlen(now_string);

        if (replace_index_vector[now_replace_index] == i) {
            // 是要刪除的單字，跳過
            now_replace_index++;
            continue;
        }

        if (isnot_first_words == 1) {
            printf(" ");
        }
        printf("%s", now_string);
        isnot_first_words = 1; // 之後都要加空白
    }

    printf("\n");
}

// 第五行輸出：整個字串單字【順序反轉】
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
    char original_string[SIZE]; // 原始字串
    char P_word[SIZE],
        Q_word[SIZE]; // P_word 是要找的單字，Q_word 是要取代的新單字

    char string_vector[SIZE][SIZE]; // 切出來的單字陣列
    int replace_index_vector[SIZE]; // 需要處理的單字索引位置

    int vector_size = 0;  // 單字數量
    int replace_size = 0; // 需要取代單字的數量

    // 輸入原始字串
    fgets(original_string, SIZE, stdin);

    // 輸入 P 和 Q
    scanf("%s", &P_word);
    scanf("%s", &Q_word);

    // 處理字串分割和記錄位置
    Get_str_vector(string_vector, original_string, replace_index_vector, P_word,
                   &vector_size, &replace_size);

    // 輸出各種要求的結果
    Answer_1(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_2(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_3(string_vector, replace_index_vector, vector_size, Q_word);
    Answer_4(string_vector, replace_index_vector, vector_size, replace_size);
    Answer_5(string_vector, vector_size);
}
