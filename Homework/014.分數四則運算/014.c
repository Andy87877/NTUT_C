/* numerator: 分子、denominator: 分母、 real_number: 真分數*/

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

void Get_fraction(char* fraction, int* new_numerator, int* new_denominator, int* error) {
    *error = 0;
    int len = strlen(fraction);
    int now_number = 0;
    int numerator = -1, denominator = -1, real_number = -1; // 分子 分母 真分數
    int negative = 0;
    for (int i = 0; i < len; i++) {
        char now_char = fraction[i];

        if (now_char == '/' || now_char == '(' || now_char == ')') {
            if (now_char == '/') {
                numerator = now_number;
            } else if (now_char == '(') {
                real_number = now_number;
            } else {
                denominator = now_number;
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
    if (denominator == -1) denominator = now_number;
    if (real_number != -1) {
        numerator += real_number * denominator;
    }
    if (negative) numerator *= -1;
    if (denominator == 0) {
        *error = 1;
    }

    *new_numerator = numerator;
    *new_denominator = denominator;
}

void Output_answer(int numerator, int denominator) {
    int real_number;
    if (denominator == 0) {
        printf("Error\n");
        return;
    }

    real_number = numerator / denominator;
    numerator -= real_number * denominator;

    // printf("%d %d %d\n", real_number, numerator, denominator);
    if (real_number == 0) {
        if (denominator == 1 || denominator == -1) {
            printf("%d", numerator);
        } else {
            printf("%d/%d", numerator, denominator);
        }
    } else {
        if (denominator == 1 || denominator == -1) {
            printf("%d", real_number);
        } else {
            printf("%d(%d/%d)", real_number, abs(numerator), abs(denominator));
        }
    }
    printf("\n");
}

void Compute(int numerator_1, int denominator_1, int numerator_2, int denominator_2,
             char operater) {
    int numerator_answer = 0, denominator_answer = 0;

    if (operater == '+' || operater == '-') { // 加法 減法
        // 通分
        int mul_number = denominator_1 * denominator_2;
        numerator_1 *= denominator_2;
        numerator_2 *= denominator_1;
        denominator_answer =
            mul_number; // denominator_1 = mul_number; denominator_2 = mul_number;

        if (operater == '+') {
            numerator_answer = numerator_1 + numerator_2;
        }
        if (operater == '-') {
            numerator_answer = numerator_1 - numerator_2;
        }
    }
    if (operater == '*') {
        numerator_answer = numerator_1 * numerator_2;
        denominator_answer = denominator_1 * denominator_2;
    }
    if (operater == '/') {
        numerator_answer = numerator_1 * denominator_2;
        denominator_answer = denominator_1 * numerator_2;
    }

    int real_number = 0;
    if (denominator_answer == 0) {
        printf("Error\n");
        return;
    }
    if (denominator_answer == 0) {
        printf("Error\n");
        return;
    }
    if (numerator_answer == 0) {
        printf("0\n");
        return;
    }
    // printf("Output1: %d, %d\n",numerator_answer, denominator_answer);
    int answer_gcd = gcd(abs(numerator_answer), abs(denominator_answer));
    // printf("answer_gcd: %d\n", answer_gcd);
    numerator_answer /= answer_gcd;
    denominator_answer /= answer_gcd;
    // printf("Output2: %d, %d\n",numerator, denominator);

    Output_answer(numerator_answer, denominator_answer);
}

void Input_data() {
    char fraction_1[101], fraction_2[101], operater;
    int numerator_1, denominator_1, numerator_2, denominator_2, error_1, error_2;

    fgets(fraction_1, 101, stdin);
    fraction_1[strlen(fraction_1) - 1] = '\0';
    Get_fraction(fraction_1, &numerator_1, &denominator_1, &error_1);
    // printf("%d / %d , error: %d\n", numerator_1, denominator_1, error_1);

    scanf("%c", &operater);
    getchar();

    fgets(fraction_2, 101, stdin);
    fraction_2[strlen(fraction_2) - 1] = '\0';
    Get_fraction(fraction_2, &numerator_2, &denominator_2, &error_2);
    // printf("%d / %d , error: %d\n", numerator_2, denominator_2, error_2);

    if (error_1 || error_2) {
        printf("Error\n");
        return;
    }
    // printf("Compute: %d, %d, %d, %d, %c\n", numerator_1, denominator_1, numerator_2,
    // denominator_2, operater);
    Compute(numerator_1, denominator_1, numerator_2, denominator_2, operater);
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