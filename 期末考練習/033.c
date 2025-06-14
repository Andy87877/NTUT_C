#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Not_gate(int x) { return abs(7 - x); }

int Gate(char type[2], int f1, int f2) {
    if (strcmp(type, "A") == 0) {
        return ((f1 & f2) & 0x07);
    }
    if (strcmp(type, "O") == 0) {
        return ((f1 | f2) & 0x07);
    }
    if (strcmp(type, "NA") == 0) {
        return (((unsigned int)~(f1 & f2)) & 0x07);
    }
    if (strcmp(type, "NO") == 0) {
        return (((unsigned int)~(f1 | f2)) & 0x07);
    }

    return 0;
}

void Print_answer(int x) {
    int array[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        if (x % 2 == 1) array[2 - i] = 1;
        x /= 2;
    }

    for (int i = 0; i < 3; i++) {
        printf("%d", array[i]);
    }
}

int main() {
    int x1, x2, x3;
    int Y_output, Answer_output;

    char type_x1[4], type_x2[4], type_x3[4];
    char type_y[4], type_ans[4];

    scanf("%d %d %d", &x1, &x2, &x3);
    scanf("%s %s %s %s %s", type_x1, type_x2, type_x3, type_y, type_ans);

    if (strcmp(type_x1, "N") == 0) {
        x1 = Not_gate(x1);
    }
    if (strcmp(type_x2, "N") == 0) {
        x2 = Not_gate(x2);
    }
    if (strcmp(type_x3, "N") == 0) {
        x3 = Not_gate(x3);
    }

    printf("%d %d %d\n", x1, x2, x3);

    Y_output = Gate(type_y, x1, x2);
    Answer_output = Gate(type_ans, Y_output, x3);

    printf("%d %d\n", Y_output, Answer_output);

    Print_answer(Answer_output);
}