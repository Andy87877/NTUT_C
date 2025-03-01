// 輸入每月網內、網外、市話、通話時間(秒)及網內、網外簡訊則數，求花費最少的資費類型。
#include <stdio.h>
#include <stdlib.h> 

int Get_money_183(int inside_time, int outside_time, int phone_time, int inside_text, int outside_text){
    // free_time
    int Free_inside_time = 500;
    int Free_outside_time = 400;
    int Free_phone_time = 300;

    int Free_inside_text = 10;
    int Free_outsize_text = 15;

    // money_rate
    int Rate_inside_time = 500;
    int Rate_outside_time = 400;
    int Rate_phone_time = 300;

    int Rate_inside_text = 10;
    int Rate_outsize_text = 15;
    
    // get_money
    double total_money = 0;
    if (inside_time > Free_inside_time){
        total_money += 
    }
}

int main(){
    int inside_time, outside_time, phone_time; // 通話時間
    int inside_text, outside_text; // 簡訊數量

    scanf("%d %d %d %d %d", &inside_time, &outside_time, &phone_time, &inside_text, &outside_text);


}