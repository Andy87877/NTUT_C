/*
015 直線方程式
給定平面上兩個點座標，求直線方程式 y = mx + b，
m = (y1 - y2) / (x1 - x2)
b = (x2 * y1 - x1 * y2) / (x2 - x1)
分數表示格式：分子/分母，例如7/3
Numerator/Denominator (upper/lower)
*/

#include <stdio.h>

// 絕對值
int abs(int x) {
    if (x < 0) return -x;
    return x;
}

// 最大公因數
int gcd(int m, int n) {
    if (n == 0) return m;

    return gcd(n, m % n);
}

// 檢查是否是負數
int check_negative(int upper, int lower) {
    if (upper * lower < 0) return 1;
    return 0;
}

// 輸出答案
void Print_answer(int m_upper, int m_lower, int negative_m, int b_upper,
                  int b_lower, int negative_b) {
    printf("y = ");
    // 輸出m
    if (m_upper != 0) {
        if (negative_m == 1) printf("-");
        if (m_lower != 1) {
            printf("%d/%d", m_upper, m_lower);
        } else if (m_upper != 1) {
            printf("%d", m_upper);
        }
        printf("x ");
    }

    // 輸出b
    if (b_upper != 0) {
        if (negative_b == 1) {
            printf("-");
        } else if (m_upper != 0) {
            printf("+");
        }
        if (m_upper != 0) {
            printf(" ");
        }
        printf("%d", b_upper);
        if (b_lower != 1) printf("/%d", b_lower);
    }

    printf("\n");
}

// 得到分子與分母
void Get_higher_and_lower(int upper, int lower, int *new_upper, int *new_lower, int *negative) {
    int gcd_m = gcd(upper, lower);
    upper /= gcd_m;
    lower /= gcd_m;
    *negative = check_negative(upper, lower);
    *new_upper = abs(upper);
    *new_lower = abs(lower);
}

// 方程式
void equation(int x1, int y1, int x2, int y2) {
    if (x1 == x2) { // 分母為0
        return;
    }

    int m_upper, m_lower, negative_m;
    Get_higher_and_lower((y1 - y2), (x1 - x2), &m_upper, &m_lower, &negative_m);
    int b_upper, b_lower, negative_b;
    Get_higher_and_lower((x2 * y1 - x1 * y2), (x2 - x1), &b_upper, &b_lower, &negative_b);

    Print_answer(m_upper, m_lower, negative_m, b_upper, b_lower, negative_b);
}

int main() {
    int times;
    scanf("%d", &times);

    for (int i = 0; i < times; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        equation(x1, y1, x2, y2);
    }
}
