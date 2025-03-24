// M進位先轉成十進位再轉成N進位
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char* string, int len) {
    for (int i = len; i >= 0; i--) {
        printf("%c", string[i]);
    }
}

// 轉成一般數字
int char_to_number(char check_char) {
    if ('0' <= check_char && check_char <= '9') {
        return (check_char - '0');
    }
    return (check_char - 'A') + 10;
}

// M進制轉十進制
int baseM_to_base10(int M, char base_M[]) {
    int base_10 = 0; // 十進制
    int Power_M = 1; // M次方

    for (int index = strlen(base_M) - 1; index >= 0; index--) {
        char check_char = base_M[index];
        // printf("Power: %d, base_num: %d", Power_M,
        // char_to_number(check_char));
        base_10 += Power_M * (char_to_number(check_char));
        // printf(" base_10: %d\n", base_10);

        Power_M *= M; // M次方
    }
    return base_10;
}

// 數字轉字元
char number_to_char(int number) {
    if (0 <= number && number <= 9) {
        return (number + '0');
    }
    return (number - 10) + 'A';
}

// 十進制轉N進制
void base10_to_baseN(int N, int base_10) {
    char base_N[100]; // N進制的數字 (沒有反轉)
    int strlen = 0;   // N進制字串長度

    while (base_10 >= N) {
        int remainder = base_10 % N; // 取餘數
        base_N[strlen] = number_to_char(remainder);

        base_10 /= N; // 整除

        strlen++;
    }

    base_N[strlen] = number_to_char(base_10);

    reverse_string(base_N, strlen);
}

int main() {
    int M, N;                      // 進制
    char base_M[100], base_N[100]; // 進制轉換的數字
    int base_10 = 0;               // 十進制數字

    scanf("%d", &M);
    scanf("%s", base_M);
    scanf("%d", &N);

    // M進制轉十進制
    base_10 = baseM_to_base10(M, base_M);
    // printf("%d", base_10);

    // 十進制轉N進制
    base10_to_baseN(N, base_10);
}