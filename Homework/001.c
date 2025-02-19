#include <stdio.h>
#include <math.h>

void condition_one(float a, float b, float c, float D){
    float x1, x2;
    x1 = (-b + sqrt(D)) / (2 * a);
    x2 = (-b - sqrt(D)) / (2 * a);

    printf("%.1f\n" , x1);
    if (D == 0){
        return;
    }
    printf("%.1f\n" , x2);
}

void condition_two(float a, float b, float c, float D){
    float real_number, i_number;
    real_number = (-b) / (2 * a);
    i_number =  sqrt(-D) / (2 * a);

    if (i_number < 0) i_number *= -1;

    if (real_number == -0) real_number = 0;
    
    printf("%.1f+%.1fi\n", real_number, i_number);
    printf("%.1f-%.1fi\n", real_number, i_number);
}

int main(){
    int a,b,c;
    scanf("%d", &a);
    getchar();
    scanf("%d", &b);
    getchar();
    scanf("%d", &c);
    getchar();

    // printf("%d %d %d", a, b, c);

    float Discriminant; // 判別式
    Discriminant = (b * b) - (4 * a * c);

    if (Discriminant >= 0){
        condition_one(a,b,c, Discriminant);
    } else {
        condition_two(a,b,c, Discriminant);
    }
}