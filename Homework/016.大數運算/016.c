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

// array都是零
void Get_all_zero_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

// 檢查是不是負數
int Check_negative(char origin_input[]) {
    if (origin_input[0] == '-') {
        return 1;
    }
    return 0;
}

// 負變正 正變負
int Change_negative(int number) {
    if (number == 1) return 0;
    return 1;
}

// 得到轉換後每一位的數字
void Get_number_array(char origin_input[], int number_array[], int negative,
                      int number_size) {
    int index_end = negative + number_size;
    for (int i = negative; i < index_end; i++) {
        int now_number = 0;
        now_number = (origin_input[i]) - '0';
        number_array[i - negative] = now_number;
    }
}

// 數字反轉
void Get_reverse_array(int number_array[], int reverse_array[],
                       int number_size) {
    Get_all_zero_array(reverse_array, number_size);
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

// Add加法功能
// 先reverse加法加起來 最後再來反轉就好了
void ADD_function(int Add_array[], int number_array_1[], int number_array_2[],
                  int number_size_1, int number_size_2, int mod) {
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

    // 模式選擇 0:要反轉 1:不反轉
    if (mod == 0) { // 加法運算回傳
        for (int i = number_size; i >= 0; i--) {
            Add_array[number_size - i - 1] = reverse_array[i];
        }
    } else { // 除法運算
        for (int i = 0; i < number_size; i++) {
            Add_array[i] = reverse_array[i];
        }
    }
}

// 找到哪個數字比較大(方便減法運算) 適用反轉的array去判斷
int Check_who_bigger(int number_array_1[], int number_array_2[],
                     int number_size_1, int number_size_2) {
    if (number_size_1 > number_size_2) return 0;
    if (number_size_1 < number_size_2) return 1;

    for (int i = number_size_1 - 1; i >= 0; i--) {
        if (number_array_1[i] > number_array_2[i]) return 0;
        if (number_array_1[i] < number_array_2[i]) return 1;
    }
    return 2; // 相同的
}

// 開始減法運算 (上面比下面大 就不用再判斷正負了)
void Minus(int Minus_array[], int number_array_1[], int number_array_2[],
           int number_size_1, int number_size_2) {
    int number_size = number_size_1 + 1;
    int reverse_array[MAX_SIZE];
    int borrow = 0; // 借位

    for (int i = 0; i < number_size; i++) {
        int number1 = 0, number2 = 0;
        if (i < number_size_1) number1 = number_array_1[i];
        if (i < number_size_2) number2 = number_array_2[i];

        if (number1 - borrow >= number2) {
            reverse_array[i] = (number1 - borrow) - number2;
            borrow = 0;
        } else {
            reverse_array[i] = ((number1 - borrow) - number2) + 10;
            borrow = 1;
        }
    }

    for (int i = number_size - 1; i >= 0; i--) {
        Minus_array[number_size - i - 1] = reverse_array[i];
    }
}

// Minus減法功能
void MINUS_function(int Minus_array[], int number_array_1[],
                    int number_array_2[], int number_size_1, int number_size_2,
                    int negative_1, int negative_2) {
    // 判斷哪個數字比較大
    int number_bigger_index = Check_who_bigger(number_array_1, number_array_2,
                                               number_size_1, number_size_2);

    int number_size = Max(number_size_1, number_size_2) + 1;

    if (number_bigger_index == 2) { // 一樣大
        Get_all_zero_array(Minus_array, MAX_SIZE);
        return;
    }

    // 判斷是否要加負號
    // 上面的數字是負數 並且 上面的數字比下面的數字大
    if (negative_1 == 1 && number_bigger_index == 0) printf("-");
    // 下面的數字是負數 並且 下面的數字比上面的數字大
    if (negative_2 == 1 && number_bigger_index == 1) printf("-");

    // 判斷是否上下面要交換
    if (number_bigger_index == 1) { // 交換
        Minus(Minus_array, number_array_2, number_array_1, number_size_2,
              number_size_1);
    } else {
        Minus(Minus_array, number_array_1, number_array_2, number_size_1,
              number_size_2);
    }
}

// 多位*一位數的計算(乘法) 是反向的
void Mul_single_function(int mul_single_array[], int number_array_1[],
                         int number_size_1, int now_mul_number,
                         int number2_index) {
    int number1_index = 0; // 處理到的index位置
    int carry = 0;         // 進位

    Get_all_zero_array(mul_single_array, MAX_SIZE);

    for (number1_index; number1_index <= number_size_1; number1_index++) {
        int now_number = carry;

        if (number1_index != number_size_1) {
            now_number = number_array_1[number1_index] * now_mul_number + carry;
        }

        carry = now_number / 10;
        now_number = now_number % 10;

        int array_index = number1_index + number2_index;
        mul_single_array[array_index] = now_number;
    }
}

// Multiplication乘法功能
// 不用判斷正負了 前面已經處理
// 先處理一位的乘法，之後再位移一格，然後再加上處理的一格，重複直到底 就做完了
void MUL_function(int Mul_array[], int number_array_1[], int number_array_2[],
                  int number_size_1, int number_size_2, int mul_array_size) {
    int Mul_reverse_array[MAX_SIZE];
    int number2_index = 0; // 處理到的index位置

    Get_all_zero_array(Mul_reverse_array, MAX_SIZE);

    for (number2_index; number2_index < number_size_2; number2_index++) {
        int mul_single_array[MAX_SIZE];
        int now_mul_number = number_array_2[number2_index];

        // 單行的乘法
        Mul_single_function(mul_single_array, number_array_1, number_size_1,
                            now_mul_number, number2_index);

        int mul_size = number_size_1 + number2_index + 1;

        // printf("+");  Print_array(Mul_reverse_array, mul_size);
        // printf("+");  Print_array(mul_single_array, mul_size);

        ADD_function(Mul_reverse_array, mul_single_array, Mul_reverse_array,
                     mul_size, mul_size, 1);

        // printf("=");Print_array(Mul_reverse_array, mul_size + 1);
    }

    Get_all_zero_array(Mul_array, MAX_SIZE);
    for (int i = mul_array_size; i >= 0; i--) {
        Mul_array[mul_array_size - i - 1] = Mul_reverse_array[i];
    }
}

// 處理加減乘的函式
void Judge_all_function(char origin_input_1[], char origin_input_2[]) {
    // 判斷原始輸入是不是負數 不是0 是1
    int origin_negative_1 = Check_negative(origin_input_1);
    int origin_negative_2 = Check_negative(origin_input_2);

    // array長度
    int number_size_1 = Get_number_size(origin_input_1, origin_negative_1);
    int number_size_2 = Get_number_size(origin_input_2, origin_negative_2);
    int number_size_max = Max(number_size_1, number_size_2);

    // 數字array
    int number_array_1[MAX_SIZE], number_array_2[MAX_SIZE];
    Get_number_array(origin_input_1, number_array_1, origin_negative_1,
                     number_size_1);
    Get_number_array(origin_input_2, number_array_2, origin_negative_2,
                     number_size_2);

    // 反轉數字array
    int reverse_array_1[MAX_SIZE], reverse_array_2[MAX_SIZE];
    Get_reverse_array(number_array_1, reverse_array_1, number_size_1);
    Get_reverse_array(number_array_2, reverse_array_2, number_size_2);

    // 加法運算
    int Add_array[MAX_SIZE];
    int Add_array_size = number_size_max + 1;

    if (origin_negative_1 == origin_negative_2) {
        if (origin_negative_1 == 1) printf("-");
        ADD_function(Add_array, reverse_array_1, reverse_array_2, number_size_1,
                     number_size_2, 0);
    } else {
        MINUS_function(Add_array, reverse_array_1, reverse_array_2,
                       number_size_1, number_size_2, origin_negative_1,
                       origin_negative_2);
    }
    Print_answer(Add_array, Add_array_size);

    // 減法運算
    int Minus_array[MAX_SIZE];
    int Minus_array_size = Add_array_size;

    if (origin_negative_1 == origin_negative_2) {
        MINUS_function(Minus_array, reverse_array_1, reverse_array_2,
                       number_size_1, number_size_2, origin_negative_1,
                       Change_negative(origin_negative_2));
    } else {
        if (origin_negative_1 == 1) printf("-");
        ADD_function(Minus_array, reverse_array_1, reverse_array_2,
                     number_size_1, number_size_2, 0);
    }
    Print_answer(Minus_array, Minus_array_size);

    // 乘法運算
    int Mul_array[MAX_SIZE];
    int Mul_array_size = number_size_max * 2 + 5;

    // 正負 或 負正 得負
    if (origin_negative_1 != origin_negative_2) printf("-");
    MUL_function(Mul_array, reverse_array_1, reverse_array_2, number_size_1,
                 number_size_2, Mul_array_size);
    Print_answer(Mul_array, Mul_array_size);
}

int main() {
    char origin_input_1[MAX_SIZE], origin_input_2[MAX_SIZE];
    scanf("%s", origin_input_1);
    getchar();
    scanf(" %s", origin_input_2);

    Judge_all_function(origin_input_1, origin_input_2);
}