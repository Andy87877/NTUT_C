// 19. 大數除法
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

// 輸出數字陣列
void Print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 字元轉數字 return size
int str_to_num(char str[], int array[]) {
    int size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (str[i] < '0' || str[i] > '9') {
            break;
        }
        array[i] = str[i] - '0';
        size++;
    }
    for (int i = size; i < MAX_SIZE; i++) {
        array[i] = 0;
    }
    return size;
}

// 判斷 (a代表被除數，k代表非零除數，q代表商數)
void Judge(int a_number[], int k_number[], int a_size, int k_size) {
    int q_number[MAX_SIZE]; // 商數
    for (int i = 0; i < a_size; i++) {
        for (int j = i; j < a_size; j++) {
            if ()
        }
    }
}

int main() {
    // 被除數, 非零除數
    char a_str[MAX_SIZE], k_str[MAX_SIZE];      // 輸入的字元
    int a_number[MAX_SIZE], k_number[MAX_SIZE]; // 轉換成數字
    int a_size = 0, k_size = 0;

    scanf("%s %s", &a_str, &k_str);

    a_size = str_to_num(a_str, a_number);
    k_size = str_to_num(k_str, k_number);

    printf("%d %d\n", a_size, k_size);

    Judge(a_number, k_number, a_size, k_size);
}

/*
兩數相除滿足此等式: a = kq + r，
a代表被除數，k代表非零除數，
其中q為商數且必為整數，而r為餘數，且必為自然數，滿足 0 <= r < |k|
*/