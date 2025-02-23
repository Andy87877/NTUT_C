// #include <stdio.h>
// #include <math.h>

// // 判斷是否輸入錯誤
// int judge_ERROR(int set_0, int set_1, char element_1, char element_2){
//     int ERROR = 0;

//     // set
//     int check_number_ERROR(int num, const char* output){
//         if ((num < 0) || (num > 63)){
//             printf("%s ERROR\n", output);
//             return 1;
//         }
//         return 0;
//     }
    
//     ERROR += check_number_ERROR(set_0, "S0");
//     ERROR += check_number_ERROR(set_1, "S1");

//     // element
//     int check_element_ERROR(char element, const char* output){
//         int i, OK = 0;
//         char check_str[6] = "abcdef";
    
//         for (i = 0; i < 6; i++){
//             if (check_str[i] == element){
//                 OK = 1;
//                 break;
//             }
//         }
//         if (OK == 0){
//             printf("%s ERROR\n", output);
//             return 1;
//         }
//         return 0;
//     }

//     ERROR += check_element_ERROR(element_1, "e1");
//     ERROR += check_element_ERROR(element_2, "e2");

//     return ERROR;
// }

// int set_to_Array(int check_set){

// }

// int make_set2(int set_1, char element_1){
//     /*
//     判斷set1的element_1 有沒有已經存在了
//     如果已經存在了 那就不需要變動
//     不存在的話 加上2的次方(該位置)數字即可
//     */
//     int check_number = set_1, i;

//     int arr_set_1[6] = {0,0,0,0,0,0}; //0不存在 1存在

//     for (int i = 0; i < 6; i++){
//         if ((check_number % 2) == 1){
//             arr_set_1[5-i] = 1;
//         }
//         check_number >>= 1;
//     }

//     int set_2 = set_1;
//     char check_str[6] = "fedcba";

//     for (int i = 0; i < 6; i++){
//         if (check_str[i] == element_1){
//             if (arr_set_1[i] == 0){
//                 set_2 += pow(2,(5-i));
//             }
//         }
//         // printf("%d ", arr_set_1[i]);
//     }

//     return set_2;
// }

// int main(){
//     int set_0, set_1, set_2;
//     char element_1, element_2;

//     scanf("%d", &set_0);
//     scanf("%d", &set_1);
//     scanf(" %c", &element_1);
//     scanf(" %c", &element_2);


//     // 判斷是否輸入錯誤 0:沒有錯誤 其他數字:有錯誤
//     int ERROR = judge_ERROR(set_0, set_1, element_1, element_2); 
//     if (ERROR){ //不用做下去
//         return 0;
//     }

//     set_2 = make_set2(set_1, element_1);


// }

// /*
// 【輸入說明】
// 第一行，集合S0 (0 <= S0 <= 63)，
// 第二行，集合S1 (0 <= S1 <= 63)，
// 第三行，一個元素e1(e1應為a~f中的任一個)，
// 第四行，一個元素e2(e2應為a~f中的任一個)。

// ~~~~
// 【輸出說明】
// 輸出說明：
// 第一行輸出集合元素e2是否為集合S2，如果是，輸出"Y"，如果不是，則輸出"N"
// 第二行輸出集合S2是否屬於集合S0的子集合，如果是，輸出"Y"，如果不是，則輸出"N"
// 第三行輸出集合S0和集合S2的交集集合整數，
// 第四行輸出集合S0和集合S2的聯集集合整數。
// 第五行輸出集合S0和集合S2的差集集合整數。

// 當輸入完成後，若發生輸入內容不符合指定範圍時，無須顯示第一行至第五行內容，只需顯示錯誤資訊

// ~~~~
// a b c d e f
// a = 2^0 ....... f = 2^5 

// */