#include <stdio.h>
#include <stdlib.h>

void number_for_inc(int begin, int end) {
    for (int t = begin; t <= end; t++) {
        printf("%d", t);
    }
}

void number_for_dec(int begin, int end) {
    for (int t = begin; t >= end; t--) {
        printf("%d", t);
    }
}

void print_char(int times, char ch) {
    for (int t = 0; t < times; t++) {
        printf("%c", ch);
    }
}

void Function_1(int N) {
    for (int i = 0; i < N; i++) {
        number_for_inc(1, i + 1);
        printf("\n");
    }
    for (int i = N; i > 0; i--) {
        number_for_dec(i, 1);
        printf("\n");
    }
}

void Function_2(int N) {
    for (int i = 0; i < N - 1; i++) {
        print_char(N - i - 1, '_');
        number_for_dec(i + 1, 1);

        number_for_inc(2, i + 1);
        print_char(N - i - 1, '_');

        printf("\n");
    }

    for (int i = N - 1; i >= 0; i--) {
        print_char(N - i - 1, '_');
        number_for_dec(i + 1, 1);

        number_for_inc(2, i + 1);
        print_char(N - i - 1, '_');

        printf("\n");
    }
}

void Function_3(int N) {
    for (int i = 1; i <= N; i++) {
        number_for_inc(1, i);
        number_for_dec(i - 1, 1);
        print_char((N - i) * 2, '_');

        printf("\n");
    }
}

void Function_4(int N) {
    for (int i = 0; i < N; i++) {
        print_char(i, '_');
        if (i % 2 == 0) {
            number_for_inc(1, N);
        } else {
            number_for_dec(N, 1);
        }
        print_char(N - i - 1, '_');
        printf("\n");
    }
}

int main() {
    int picture_number;
    scanf("%d", &picture_number);

    int N;
    scanf("%d", &N);

    if (picture_number == 1) {
        Function_1(N);
    }
    if (picture_number == 2) {
        Function_2(N);
    }
    if (picture_number == 3) {
        Function_3(N);
    }
    if (picture_number == 4) {
        Function_4(N);
    }
}