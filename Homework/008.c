#include <stdio.h>

void print_star(int times){
    for (int i = 0; i < times; i++){
        printf("*");
    }
    printf("\n");
}

void judge(int arr[3]){
    // sort
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    int a = arr[0], b = arr[1], c = arr[2];

    // printf
    if (a+b < c){
        printf("Not Triangle\n");
        return;
    }
    if (a == b && b == c && a == c){
        printf("Equilateral Triangle\n");
    } 
    if (a == b || b == c || a == c){
        printf("Isosceles Triangle\n");
    } 
    if (a*a + b*b < c*c){
        printf("Obtuse Triangle\n");
    } 
    if (a*a + b*b > c*c){
        printf("Acute Triangle\n");
    } 
    if (a*a + b*b == c*c) {
        printf("Right Triangle\n");
    }
}

int main(){
    int n;
    scanf("%d", &n);

    int arr[3];

    for (int i = 0; i < n; i++){
        scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
        judge(arr);
        if (i+1 != n) print_star(n);
    }
}