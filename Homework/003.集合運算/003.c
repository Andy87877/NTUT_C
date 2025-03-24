#include <stdio.h>

// 判斷是否輸入錯誤
int judge_ERROR(int set_0, int set_1, char element_1, char element_2){
    int ERROR = 0;

    // set
    int check_number_ERROR(int num, const char* output){
        if ((num < 0) || (num > 63)){
            printf("%s ERROR\n", output);
            return 1;
        }
        return 0;
    }
    
    ERROR += check_number_ERROR(set_0, "S0");
    ERROR += check_number_ERROR(set_1, "S1");

    // element
    int check_element_ERROR(char element, const char* output){
        int i, OK = 0;
        char check_str[6] = "abcdef";
    
        for (i = 0; i < 6; i++){
            if (check_str[i] == element){
                OK = 1;
                break;
            }
        }
        if (OK == 0){
            printf("%s ERROR\n", output);
            return 1;
        }
        return 0;
    }

    ERROR += check_element_ERROR(element_1, "e1");
    ERROR += check_element_ERROR(element_2, "e2");

    return ERROR;
}

// 元素的位置
int element_index(char element){
    int index = 0;
    char check_str[6] = "fedcba";

    for (int i = 0; i < 6; i++){
        if (check_str[i] == element){
            index = i;
        }
    }
    return index;
}

// 數字轉集合元素
void set_to_Array(int arr_set[], int check_set){
    for (int i = 0; i < 6; i++) {
        arr_set[i] = 0;  // 確保初始為 0
    }
    for (int i = 0; i < 6; i++){
        if ((check_set % 2) == 1){
            arr_set[5-i] = 1;
        }
        check_set >>= 1;
    }
}

// 製作set2
int make_set2(int set_1, char index_element_1){
    /*
    判斷set1的element_1 有沒有已經存在了
    如果已經存在了 那就不需要變動
    不存在的話 加上2的次方(該位置)數字即可
    */

    int arr_set_1[6] = {0};
    set_to_Array(arr_set_1, set_1); //0不存在 1存在

    int set_2 = set_1;


    if (arr_set_1[index_element_1] == 0){
        set_2 += (1 << (5 - index_element_1));
    }

    return set_2;
}

// 輸出集合
void print_array(int arr_set[]){
    for (int i = 0; i < 6; i++){
        printf("%d ", arr_set[i]);
    }
    printf("\n");
}

// 判斷答案
void All_question(int arr_set_0[], int arr_set_2[], int index_element_2){
    void question_1(int arr_set_2[], int index_element_2){
        // 第一行輸出集合元素e2是否為集合S2，如果是，輸出"Y"，如果不是，則輸出"N"
        if (arr_set_2[index_element_2] == 1){
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    
    void question_2(int arr_set_0[], int arr_set_2[]){
        // 第二行輸出集合S2是否屬於集合S0的子集合，如果是，輸出"Y"，如果不是，則輸出"N"
        int check = 1;
        for (int i = 0; i < 6; i++){
            // 集合S2有個元素不再S0裡面
            if (arr_set_2[i] == 1 && arr_set_0[i] == 0){
                check = 0;
                break;
            }
        }
        if (check){
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    
    void question_3(int arr_set_0[], int arr_set_2[]){
        // 第三行輸出集合S0和集合S2的交集集合整數，
        int answer_number = 0;
        for (int i = 0; i < 6; i++){
            if (arr_set_2[i] == 1 && arr_set_0[i] == 1){
                answer_number += (1 << 5-i);
            }
        }
        printf("%d\n", answer_number);
    }
    
    void question_4(int arr_set_0[], int arr_set_2[]){
        // 第四行輸出集合S0和集合S2的聯集集合整數。
        int answer_number = 0;
        for (int i = 0; i < 6; i++){
            if (arr_set_2[i] == 1 || arr_set_0[i] == 1){
                answer_number += (1 << 5-i);
            }
        }
        printf("%d\n", answer_number);
    }
    
    void question_5(int arr_set_0[], int arr_set_2[]){
        // 第五行輸出集合S0和集合S2的差集集合整數。
        int answer_number = 0;
        for (int i = 0; i < 6; i++){
            if (arr_set_2[i] == 0 && arr_set_0[i] == 1){
                answer_number += (1 << 5-i);
            }
        }
        printf("%d\n", answer_number);
    }
    
    question_1(arr_set_2, index_element_2);
    question_2(arr_set_0, arr_set_2);
    question_3(arr_set_0, arr_set_2);
    question_4(arr_set_0, arr_set_2);
    question_5(arr_set_0, arr_set_2);
}

int main(){
    int set_0, set_1, set_2; // 數字
    
    // 集合元素 {f,e,d,c,b,a} --> {0,0,0,0,0,0} 0沒有 1有
    int arr_set_0[6] = {0};
    int arr_set_1[6] = {0};
    int arr_set_2[6] = {0};

    char element_1, element_2; // 元素
    int index_element_1, index_element_2; // 元素位置

    scanf("%d", &set_0);
    scanf("%d", &set_1);
    scanf(" %c", &element_1);
    scanf(" %c", &element_2);

    // 判斷是否輸入錯誤 0:沒有錯誤 其他數字:有錯誤
    int ERROR = judge_ERROR(set_0, set_1, element_1, element_2); 
    if (ERROR){ //不用做下去
        return 0;
    }

    index_element_1 = element_index(element_1);
    index_element_2 = element_index(element_2);

    set_2 = make_set2(set_1, index_element_1);

    set_to_Array(arr_set_0, set_0);
    set_to_Array(arr_set_1, set_1);
    set_to_Array(arr_set_2, set_2);

    // print_array(arr_set_0);
    // print_array(arr_set_1);
    // print_array(arr_set_2);
    
    All_question(arr_set_0, arr_set_2, index_element_2);
}

/*
【輸入說明】
第一行，集合S0 (0 <= S0 <= 63)，
第二行，集合S1 (0 <= S1 <= 63)，
第三行，一個元素e1(e1應為a~f中的任一個)，
第四行，一個元素e2(e2應為a~f中的任一個)。

~~~~
【輸出說明】
輸出說明：
第一行輸出集合元素e2是否為集合S2，如果是，輸出"Y"，如果不是，則輸出"N"
第二行輸出集合S2是否屬於集合S0的子集合，如果是，輸出"Y"，如果不是，則輸出"N"
第三行輸出集合S0和集合S2的交集集合整數，
第四行輸出集合S0和集合S2的聯集集合整數。
第五行輸出集合S0和集合S2的差集集合整數。

當輸入完成後，若發生輸入內容不符合指定範圍時，無須顯示第一行至第五行內容，只需顯示錯誤資訊

~~~~
a b c d e f
a = 2^0 ....... f = 2^5 

*/