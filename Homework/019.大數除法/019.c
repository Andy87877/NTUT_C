// 19. 大數除法
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

// 輸出數字陣列
void Print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
}

// 輸出陣列(前面都為0時)
void Print_nonezero_array(int array[], int size) {
    int all_zero = 1;
    for (int i = 0; i < size; i++) {
        if (array[i] == 0 && all_zero) continue;
        all_zero = 0;
        printf("%d", array[i]);
    }
    printf("\n");
}

// 所有array都為0
void All_zero_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

void Copy_array(int array_goal[], int array[], int size) {
    All_zero_array(array_goal, size);
    for (int i = 0; i < size; i++) {
        array_goal[i] = array[i];
    }
}

// 字元轉數字 return size
int str_to_num(char str[], int array[]) {
    int size = 0;
    All_zero_array(array, MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        if (str[i] < '0' || str[i] > '9') {
            break;
        }
        array[i] = str[i] - '0';
        size++;
    }
    return size;
}

// 判斷當下的除式有沒有比被除式大 如果是回傳1
int Compare_a_or_k_bigger(int now_a[], int k_number[], int a_size, int k_size) {
    if (a_size > k_size) return 1;
    for (int i = 0; i < a_size; i++) { // 判斷
        if (now_a[i] > k_number[i]) return 1;
        if (now_a[i] < k_number[i]) return 0;
    }
    return 1; // 一樣大(可以全減)
}

// 反轉數字array
void Reverse_number(int reverse_array[], int array[], int size) {
    All_zero_array(reverse_array, size);
    for (int i = 0; i < size; i++) {
        reverse_array[size - i - 1] = array[i];
    }
}

// 加法功能
void Add_function(int array_answer[], int array_1[], int array_2[], int size) {
    int sum = 0, carry = 0;
    for (int i = 0; i < size; i++) {
        sum = array_1[i] + array_2[i] + carry;
        carry = sum / 10;
        sum %= 10;
        array_answer[i] = sum;
    }
}

// 單行的乘法 回傳反轉的乘法
void Mul_single_function(int single_mul_reverse_array[], int array_reverse_1[],
                         int number_2, int size_1, int index_shift) {
    All_zero_array(single_mul_reverse_array, MAX_SIZE);

    int sum = 0, carry = 0; // 總和&進位

    for (int i = 0; i <= size_1; i++) {
        int number_1 = 0;
        if (size_1 != i) number_1 = array_reverse_1[i];

        sum = (number_1 * number_2) + carry; // 加總
        carry = sum / 10;                    // 進位
        sum %= 10;                           // 當下的數字

        single_mul_reverse_array[i + index_shift] = sum;
    }
}

// 移除前面都是0的array
void Remove_frontZero_array(int array_goal[], int array[], int size) {
    All_zero_array(array_goal, size);
    int front_index = 0;
    int front_all_zero = 1;
    for (int i = 0; i < size; i++) {
        if (front_all_zero && array[i] != 0) {
            front_index = i;
        }
        if (array[i] != 0) front_all_zero = 0;
        if (front_all_zero == 0) {
            array_goal[i - front_index] = array[i];
        }
    }
}

// 乘法功能
void Mul_function(int array_answer[], int array_1[], int array_2[], int size_1,
                  int size_2) {
    int array_reverse_answer[MAX_SIZE];
    All_zero_array(array_answer, MAX_SIZE);
    All_zero_array(array_reverse_answer, MAX_SIZE);

    int array_reverse_1[MAX_SIZE], array_reverse_2[MAX_SIZE];
    Reverse_number(array_reverse_1, array_1, size_1);
    Reverse_number(array_reverse_2, array_2, size_2);

    // 乘法運算
    for (int i = 0; i < size_2; i++) {
        // 單行乘法
        int single_mul_reverse_array[MAX_SIZE];
        int number_2 = array_reverse_2[i];
        Mul_single_function(single_mul_reverse_array, array_reverse_1, number_2,
                            size_1, i);

        Add_function(array_reverse_answer, array_reverse_answer,
                     single_mul_reverse_array, MAX_SIZE);
    }

    Reverse_number(array_answer, array_reverse_answer, MAX_SIZE);
    
}

// 尋找商數 (now_被除數 >= 除數) 一定大於等於1
int Find_q(int now_a[], int k_number[], int a_size, int k_size) {
    // printf("Find_q=======\n");
    Print_array(now_a, MAX_SIZE);
    // printf("\n");
    // 商數
    int find_q = 1;

    for (int q = 1; q <= 9; q++) {
        int tmp_q[1] = {q};
        int now_k[MAX_SIZE], tmp_k[MAX_SIZE]; // 除數 * 商數 的值
        All_zero_array(now_k, MAX_SIZE);
        All_zero_array(tmp_k, MAX_SIZE);

        // Print_array(k_number, MAX_SIZE);
        // printf("*%d\n", q);

        Mul_function(tmp_k, k_number, tmp_q, MAX_SIZE, 1);
        
        Copy_array(now_k, tmp_k, MAX_SIZE);
        Copy_array(tmp_k, now_k, MAX_SIZE);
        Remove_frontZero_array(now_k, tmp_k, MAX_SIZE);

        // printf("=\n");
        Print_array(now_k, MAX_SIZE);
        int a_bigger; // 判斷當下的除式有沒有比被除式大 如果是回傳1
        a_bigger = Compare_a_or_k_bigger(now_a, now_k, MAX_SIZE, MAX_SIZE);
        printf("%d\n", a_bigger);

        // 當下的乘法 大於 除數 * 商數 的值
        if (a_bigger != 1) {
            find_q = q+1;
            break;
        }
    }
    return find_q-1;
}

// 判斷 (a代表被除數，k代表非零除數，q代表商數)
void Judge(int a_number[], int k_number[], int a_size, int k_size) {
    int q_number[MAX_SIZE]; // 商數
    All_zero_array(q_number, MAX_SIZE);

    // 被除數
    for (int i = 0; i < a_size - k_size + 1; i++) {
        // 商數的index
        int now_a_number[MAX_SIZE]; // 判斷的被除數數字
        All_zero_array(now_a_number, MAX_SIZE);

        for (int j = i; j < a_size; j++) {
            int now_index = j - i; // now_a_number index
            now_a_number[now_index] = a_number[j];

            int a_bigger = 0;
            if (now_index + 1 >= k_size) { // 判斷的當下被除數 大於等於 除數
                a_bigger = Compare_a_or_k_bigger(now_a_number, k_number,
                                                 now_index + 1, k_size);
                int now_q = 0; // 找到的商數
                if (a_bigger) {
                    now_q = Find_q(now_a_number, k_number, a_size, k_size);
                    printf("%d\n", now_q);
                }
            }
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

    int tmp_array[MAX_SIZE];

    Judge(a_number, k_number, a_size, k_size);
}

/*
兩數相除滿足此等式: a = kq + r，
a代表被除數，k代表非零除數，
其中q為商數且必為整數，而r為餘數，且必為自然數，滿足 0 <= r < |k|
*/