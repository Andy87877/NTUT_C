/* upper: 分子、lower: 分母、 real_number: 真分數*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abs(int n) {
    if (n < 0) return n * -1;
    return n;
}

int gcd(int m, int n) {
    if (n == 0) return m;

    return gcd(n, m % n);
}

void Get_fraction(char* fraction, int* new_upper, int* new_lower, int* error) {
    *error = 0;
    int len = strlen(fraction);
    int now_number = 0;
    int upper = -1, lower = -1, real_number = -1; // 分子 分母 真分數
    int negative = 0;
    for (int i = 0; i < len; i++) {
        char now_char = fraction[i];

        if (now_char == '/' || now_char == '(' || now_char == ')') {
            if (now_char == '/') {
                upper = now_number;
            } else if (now_char == '(') {
                real_number = now_number;
            } else {
                lower = now_number;
            }
            now_number = 0;
            continue;
        }
        if (now_char == '-') {
            negative = 1;
            continue;
        }

        now_number *= 10;
        now_number += ((now_char) - '0');
    }
    if (lower == -1) lower = now_number;
    if (real_number != -1) {
        upper += real_number * lower;
    }
    if (negative) upper *= -1;
    if (lower == 0) {
        *error = 1;
    }

    *new_upper = upper;
    *new_lower = lower;
}

void Output_answer(int upper, int lower) {
    int real_number;
    if (lower == 0) {
        printf("Error\n");
        return;
    }

    real_number = upper / lower;
    upper -= real_number * lower;

    // printf("%d %d %d\n", real_number, upper, lower);
    if (real_number == 0) {
        if (lower == 1 || lower == -1) {
            printf("%d", upper);
        } else {
            printf("%d/%d", upper, lower);
        }
    } else {
        if (lower == 1 || lower == -1) {
            printf("%d", real_number);
        } else {
            printf("%d(%d/%d)", real_number, abs(upper), abs(lower));
        }
    }
    printf("\n");
}

void Compute(int upper_1, int lower_1, int upper_2, int lower_2,
             char operater) {
    int upper_answer = 0, lower_answer = 0;

    if (operater == '+' || operater == '-') { // 加法 減法
        // 通分
        int mul_number = lower_1 * lower_2;
        upper_1 *= lower_2;
        upper_2 *= lower_1;
        lower_answer =
            mul_number; // lower_1 = mul_number; lower_2 = mul_number;

        if (operater == '+') {
            upper_answer = upper_1 + upper_2;
        }
        if (operater == '-') {
            upper_answer = upper_1 - upper_2;
        }
    }
    if (operater == '*') {
        upper_answer = upper_1 * upper_2;
        lower_answer = lower_1 * lower_2;
    }
    if (operater == '/') {
        upper_answer = upper_1 * lower_2;
        lower_answer = lower_1 * upper_2;
    }

    int real_number = 0;
    if (lower_answer == 0) {
        printf("Error\n");
        return;
    }
    if (lower_answer == 0) {
        printf("Error\n");
        return;
    }
    if (upper_answer == 0) {
        printf("0\n");
        return;
    }
    // printf("Output1: %d, %d\n",upper_answer, lower_answer);
    int answer_gcd = gcd(abs(upper_answer), abs(lower_answer));
    // printf("answer_gcd: %d\n", answer_gcd);
    upper_answer /= answer_gcd;
    lower_answer /= answer_gcd;
    // printf("Output2: %d, %d\n",upper, lower);

    Output_answer(upper_answer, lower_answer);
}

void Input_data() {
    char fraction_1[101], fraction_2[101], operater;
    int upper_1, lower_1, upper_2, lower_2, error_1, error_2;

    fgets(fraction_1, 101, stdin);
    fraction_1[strlen(fraction_1) - 1] = '\0';
    Get_fraction(fraction_1, &upper_1, &lower_1, &error_1);
    // printf("%d / %d , error: %d\n", upper_1, lower_1, error_1);

    scanf("%c", &operater);
    getchar();

    fgets(fraction_2, 101, stdin);
    fraction_2[strlen(fraction_2) - 1] = '\0';
    Get_fraction(fraction_2, &upper_2, &lower_2, &error_2);
    // printf("%d / %d , error: %d\n", upper_2, lower_2, error_2);

    if (error_1 || error_2) {
        printf("Error\n");
        return;
    }
    // printf("Compute: %d, %d, %d, %d, %c\n", upper_1, lower_1, upper_2,
    // lower_2, operater);
    Compute(upper_1, lower_1, upper_2, lower_2, operater);
}

int main() {
    char check_continue = 'y';

    do {
        Input_data();
        // printf("next:\n");
        scanf("%c", &check_continue);
        getchar();
    } while (check_continue == 'y');
}