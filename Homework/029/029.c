#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define longd long double

longd f1(longd x, longd a) {
    longd num;
    num = sqrt(a - pow(x, 2));
    return num;
}

longd f2(longd x, longd a) {
    longd up_num, down_num, num;

    up_num = a * pow(x, 3) + 7 * x;
    down_num = sqrt(a + x);
    num = up_num / down_num;

    return num;
}

void judge(int mode) {
    // 輸入四個參數a(函數中的係數)、p(積分區間起始點)、q(積分區間終點)、err(精度要求，表示精確到小數後第error位)
    longd a, p, q, err;
    scanf("%d %d %d %d", &a, &p, &q, &err);

    longd T, h;
}

int main() {
    int mode = 0;

    while (1) {
        scanf("%d", &mode);
        if (mode == 0) break;

        judge(mode);
    }
}