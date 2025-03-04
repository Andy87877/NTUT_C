#include <stdio.h>

int main(){
    int a,b;
    scanf("%d %d", &a, &b);
    double Area = (a*b)/2.0;

    printf("Triangle area:%.1f\n", Area);
}