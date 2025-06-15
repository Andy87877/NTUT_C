#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double F1(int a, double x) { return sqrt(a - x * x); }
double F2(int a, double x) { return (a * pow(x, 3) + 7 * x) / (sqrt(a + x)); }
double Integral(double (*F)(int, double), int a, int p, int q, int err) {
    int n = 1;
    double pre = 0;
    double now = 0;

    while (1) {
        pre = now;
        now = 0;

        double h = (q - p) * 1.0 / n;

        double sum = 0;
        for (int i = 1; i < n; i++) {
            sum += F(a, (double)(p + i * h));
        }
        now = (F(a, p) + F(a, q) + 2.0 * sum) * h / 2;
        n *= 2;

        if (fabs(now - pre) < pow(10, -err)) break;
    }
    return now;
}

int main() {
    double database[100];
    int index = 0;

    while (1) {
        int type;
        scanf("%d", &type);
        if (type == 0)
            break;
        else if (type != 1 && type != 2) {
            printf("Invalid");
            return 0;
        }

        int a, p, q, err;
        scanf("%d%d%d%d", &a, &p, &q, &err);

        if (type == 1)
            database[index++] = Integral(F1, a, p, q, err);
        else if (type == 2)
            database[index++] = Integral(F2, a, p, q, err);
    }

    for (int i = 0; i < index; i++) printf("%.12f\n", database[i]);
}