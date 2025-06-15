#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int main() {
    char input_str[MAX_SIZE];
    gets(input_str);
    int input_size = strlen(input_str);

    char P_word[MAX_SIZE], Q_word[MAX_SIZE];
    scanf("%s", P_word);
    scanf("%s", Q_word);


    char array_all_str[MAX_SIZE][MAX_SIZE];
    int array_index = 0;

    char tmp_str[MAX_SIZE];
    memset(tmp_str, '\0', sizeof(tmp_str));
    int tmp_index = 0;

    for (int i = 0; i < input_size + 1; i++) {
        char check_char = input_str[i];
        if (check_char == ' ' || check_char == '\0') {
            char now_str[MAX_SIZE];
            strcpy(now_str, tmp_str);
            memset(tmp_str, '\0', sizeof(tmp_str));
            tmp_index = 0;

            strcpy(array_all_str[array_index++], now_str);
            continue;
        }

        tmp_str[tmp_index++] = check_char;

        // printf("%c", input_str[i]);
    }

    // find P_index;
    int P_index[MAX_SIZE];
    for (int i = 0; i < array_index; i++) {
        char now_str[MAX_SIZE]; 
        printf("%s\n", array_all_str[i]);
    }
}