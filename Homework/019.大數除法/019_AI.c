#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 比較兩個大數字串 a 和 b，a > b 回傳 1，a == b 回傳 0，a < b 回傳 -1
int compare(char *a, char *b) {
    int la = strlen(a), lb = strlen(b);
    if (la > lb) return 1;
    if (la < lb) return -1;
    for (int i = 0; i < la; ++i) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

// 減法 a - b (保證 a >= b)，回傳結果字串（靜態記憶體）
void subtract(char *a, char *b, char *result) {
    int la = strlen(a), lb = strlen(b);
    int diff = la - lb;
    int carry = 0;

    for (int i = la - 1; i >= 0; i--) {
        int ai = a[i] - '0';
        int bi = (i - diff >= 0) ? b[i - diff] - '0' : 0;
        int sub = ai - bi - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result[i] = sub + '0';
    }

    result[la] = '\0';

    // 去除前導零
    int i = 0;
    while (result[i] == '0' && result[i + 1] != '\0') i++;
    if (i > 0) memmove(result, result + i, strlen(result + i) + 1);
}

// 乘法 b * d (d 為個位數字) 回傳結果字串（靜態記憶體）
void multiply(char *b, int d, char *result) {
    int lb = strlen(b);
    int carry = 0;
    for (int i = lb - 1; i >= 0; i--) {
        int prod = (b[i] - '0') * d + carry;
        result[i + 1] = prod % 10 + '0';
        carry = prod / 10;
    }
    result[0] = carry + '0';
    result[lb + 1] = '\0';

    // 去除前導零
    int i = 0;
    while (result[i] == '0' && result[i + 1] != '\0') i++;
    if (i > 0) memmove(result, result + i, strlen(result + i) + 1);
}

// 主函數：大數除法
int main() {
    char a[MAX_SIZE], b[MAX_SIZE];
    scanf("%s", a);
    scanf("%s", b);

    char quotient[MAX_SIZE] = "";
    char current[MAX_SIZE] = "";
    char temp[MAX_SIZE];
    char mul[MAX_SIZE];

    int la = strlen(a);
    int q_pos = 0;

    for (int i = 0; i < la; i++) {
        int len = strlen(current);
        current[len] = a[i];
        current[len + 1] = '\0';

        // 去除前導零
        int j = 0;
        while (current[j] == '0' && current[j + 1] != '\0') j++;
        if (j > 0) memmove(current, current + j, strlen(current + j) + 1);

        // 試商
        int digit = 0;
        for (int d = 9; d >= 0; d--) {
            multiply(b, d, mul);
            if (compare(current, mul) >= 0) {
                digit = d;
                break;
            }
        }

        quotient[q_pos++] = digit + '0';
        multiply(b, digit, mul);
        subtract(current, mul, temp);
        strcpy(current, temp);
    }

    quotient[q_pos] = '\0';

    // 去除商的前導零
    int k = 0;
    while (quotient[k] == '0' && quotient[k + 1] != '\0') k++;
    if (k > 0) memmove(quotient, quotient + k, strlen(quotient + k) + 1);

    printf("%s\n", quotient);
    printf("%s\n", current[0] ? current : "0");

    return 0;
}
