#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f1(double x, double a) { return sqrt(a - x * x); }

double f2(double x, double a) {
    return ((a * pow(x, 3) + 7 * x) / (sqrt(a + x)));
}

void judge(int mode) {
    // 輸入四個參數a(函數中的係數)、p(積分區間起始點)、q(積分區間終點)、err(精度要求，表示精確到小數後第error位)
    int A, P, Q, err;
    scanf("%d %d %d %d", &A, &P, &Q, &err);

    double a, p, q;
    a = (double)A;
    p = (double)P;
    q = (double)Q;

    double times = 0;
    int n = 1; // 切割次數
    double T_now, T_old = -1;

    while (1) {
        double h, sum_num = 0;
        h = (q - p) * 1.0 / n;

        T_now = 0;

        if (mode == 1) {
            T_now = 1.0 * f1(p, a) + 1.0 * f1(q, a);
            for (int i = 1; i < n; i++) {
                T_now += (2.0 * f1((p + i * h), a));
            }
        } else {
            T_now = 1.0 * f2(p, a) + 1.0 * f2(q, a);
            for (int i = 1; i < n; i++) {
                T_now += (2.0 * f2((p + i * h), a));
            }
        }
        T_now = T_now * (h / 2);

        // printf("%d, %.12f/%.12f\n", times, T_now, T_old);
        // 表示精確到小數後第error位
        if (abs(T_now - T_old) < pow(10, -err)) {
            break;
        }
        n *= 2;
        times++;

        T_old = T_now;
    }

    printf("%.12f\n", T_now);
}

int main() {
    int mode = 0;

    while (1) {
        scanf("%d", &mode);
        if (mode == 0) break;
        if (mode != 1 && mode != 2) {
            printf("Invalid\n");
            continue;
        }

        judge(mode);
    }
}