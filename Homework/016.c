#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 250

int Max(int a, int b) { return (a > b) ? a : b; }

// 輸出array
void Print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
}

// 輸出array答案，要排除前面都是零的狀況
void Print_answer(int array[], int size) {
    int All_zero = 1;
    for (int i = 0; i < size; i++) {
        if (array[i] == 0) {
            if (All_zero) continue;
        }
        All_zero = 0;
        printf("%d", array[i]);
    }
    if (All_zero) printf("0");
    printf("\n");
}

// 檢查是不是負數
int Check_negative(char origin_input[]) {
    if (origin_input[0] == '-') {
        return 1;
    }
    return 0;
}

// 得到轉換後每一位的數字
void Get_number_array(char origin_input[], int *number_array[], int negative,
                      int number_size) {
    int index_end = negative + number_size;
    for (int i = negative; i < index_end; i++) {
        int now_number = 0;
        now_number = (origin_input[i]) - '0';
        number_array[i - negative] = now_number;
    }

    // for (int i = strlen(origin_input); i < MAX_SIZE; i++) {
    //     number_array[i] = 0;
    // }
}

// 數字反轉
void Get_reverse_array(int number_array[], int *reverse_array[],
                       int number_size, int number_size_max) {
    for (int i = 0; i < number_size; i++) {
        reverse_array[i] = number_array[number_size - i - 1];
    }
}

// 得到該字串數字的大小
int Get_number_size(char origin_input[], int negative) {
    int size = 0;
    for (int i = negative; i < strlen(origin_input); i++) {
        char now_char = origin_input[i];
        if (now_char >= '0' && now_char <= '9') {
            size++;
            continue;
        }
        break;
    }
    return size;
}

// Add加法
// 先reverse加法加起來 最後再來反轉就好了
void ADD(int Add_array[], int number_array_1[], int number_array_2[],
         int number_size_1, int number_size_2) {
    int number_size = Max(number_size_1, number_size_2) + 1;
    int reverse_array[MAX_SIZE];
    int carry = 0;

    // 做加法運算
    for (int i = 0; i < number_size; i++) {
        int number1 = 0, number2 = 0, sum = 0;
        if (i < number_size_1) number1 = number_array_1[i];
        if (i < number_size_2) number2 = number_array_2[i];

        sum = number1 + number2 + carry;
        if (sum >= 10) {
            carry = 1;
            sum %= 10;
        } else {
            carry = 0;
        }

        reverse_array[i] = sum;
    }

    for (int i = number_size; i >= 0; i--) {
        Add_array[number_size - i - 1] = reverse_array[i];
    }
}

// Minus減法
void MINUS(int Minus_array[], int number_array_1[], int number_array_2[],
         int number_size_1, int number_size_2) {
    int number_size = Max(number_size_1, number_size_2) + 1;
    int reverse_array[MAX_SIZE];
    int carry = 0;

    
}

int main() {
    char origin_input_1[MAX_SIZE], origin_input_2[MAX_SIZE];
    scanf("%s", origin_input_1);
    getchar();
    scanf(" %s", origin_input_2);

    // 判斷原始輸入是不是負數 不是0 是1
    int origin_negative_1 = Check_negative(origin_input_1);
    int origin_negative_2 = Check_negative(origin_input_2);

    // array長度
    int number_size_1 = Get_number_size(origin_input_1, origin_negative_1);
    int number_size_2 = Get_number_size(origin_input_2, origin_negative_2);
    int number_size_max = Max(number_size_1, number_size_2);

    // 數字array
    int number_array_1[MAX_SIZE], number_array_2[MAX_SIZE];
    Get_number_array(origin_input_1, &number_array_1, origin_negative_1,
                     number_size_1);
    Get_number_array(origin_input_2, &number_array_2, origin_negative_2,
                     number_size_2);

    // 反轉數字array
    int reverse_array_1[MAX_SIZE], reverse_array_2[MAX_SIZE];
    Get_reverse_array(number_array_1, &reverse_array_1, number_size_1,
                      number_size_max);
    Get_reverse_array(number_array_2, &reverse_array_2, number_size_2,
                      number_size_max);

    // 加法運算
    int Add_array[MAX_SIZE];
    int Add_array_size = number_size_max + 1;

    if (origin_negative_1 == origin_negative_2) {
        if (origin_negative_1 == 1) printf("-");
        ADD(Add_array, reverse_array_1, reverse_array_2, number_size_1,
            number_size_2);
    } else {
    }
    Print_answer(Add_array, Add_array_size);

    // 減法運算
    int Minus_array[MAX_SIZE];
    if (origin_negative_1 == origin_negative_2) {
    } else {
        if (origin_negative_1 == 1) printf("-");
        ADD(Minus_array, reverse_array_1, reverse_array_2, number_size_1,
            number_size_2);
    }
    // Print_answer(Minus_array, Add_array_size);
}