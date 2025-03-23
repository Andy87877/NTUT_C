#include <stdio.h>

int main() {
    int A = 'A';
    char input, input_2;
    scanf("%c %c", &input, &input_2);

    int judge = input - A;
    int judge_2 = input_2 - A;

    printf("%d %d", judge, judge_2);
}