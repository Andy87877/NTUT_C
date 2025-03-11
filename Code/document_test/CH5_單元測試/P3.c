#include <stdio.h>
// main.c
#include <assert.h>
#include <math.h>
double computeBMI(int kg, int height) {
    double BMI = 0.0, M = height / 100.0;
    if (kg <= 0 || height <= 0) return -1;
    BMI = round(100 * kg / (M * M)) / 100; // 四捨五入取兩位小數
    return BMI;
}
int main() {
    int kg = 52, height = 155;
    double expectedResult = 21.64f;
    double result = computeBMI(kg, height);
    printf("do it\n");
    assert(fabs(result - expectedResult) < 0.0001);
    printf("Hi~~~~~~~~~\n");
    assert(fabs(result - expectedResult) < 0.000000000000000001);
    printf("Hello~~~~~~~~~\n");
    return 0;
}