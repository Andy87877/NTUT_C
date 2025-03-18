/*
015 直線方程式
給定平面上兩個點座標，求直線方程式 y = mx + b，
m = (y1 - y2) / (x1 - x2)
b = (x2 * y1 - x1 * y2) / (x2 - x1)
分數表示格式：分子/分母，例如7/3
Numerator/Denominator (upper/lower)
*/

#include <stdio.h>

int abs(int x){
    if (x < 0) return -x;
    return x;
}

void equation(int x1, int y1, int x2, int y2){
    if (x1 == x2){ // 分母為0
        return;
    }

    int m_upper = (y1 - y2);
    int m_lower = (x1 - x2);

    int b_upper
    int b = (x2 * y1 - x1 * y2) / (x2 - x1);


}

int main(){
    int times;
    scanf("%d", &times);

    for (int i = 0; i < times; i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        equation(x1, y1, x2, y2);
    }
}
