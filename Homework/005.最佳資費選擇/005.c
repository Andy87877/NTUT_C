#include <stdio.h>
#include <stdlib.h> 

double TimeORtext_to_money(int now_time, int free_time, double money_rate){
    double money = 0;
    if (now_time > free_time){
        money = (now_time - free_time) * money_rate;
    }
    return money;
}

int Get_money(int Type_money, int index, int Spend_array[5]){
    // free_time (Free_inside_time, Free_outside_time, Free_phone_time, Free_inside_text, Free_outside_text)
    int Free_time_array[3][5] = {
        {500, 400, 300, 10, 15},
        {600, 500, 400, 20, 25},
        {700, 600, 500, 30, 35}
    }; 
    // money_rate (Rate_inside_time, Rate_outside_time, Rate_phone_time, Rate_inside_text, Rate_outside_text)
    double Rate_array[3][5] = {
        {0.08, 0.1393, 0.1349, 1.1287, 1.4803},
        {0.07, 0.1304, 0.1217, 1.1127, 1.2458},
        {0.06, 0.1087, 0.1018, 0.9572, 1.1243}
    };

    
    // 計算價錢
    double total_money = 0;
    for (int i = 0; i < 5; i++){
        total_money += TimeORtext_to_money(Spend_array[i], Free_time_array[index][i], Rate_array[index][i]);
        // printf("%d\n", total_money);
    }
    if (total_money <= Type_money){
        total_money = Type_money;
    }
    return total_money;
}

// 判斷最小的花費
void Judge_min_fee(int Money_array[3]){
    int min_index = 0, min_money = Money_array[0];
    for (int i = 1; i < 3; i++){
        if (min_money > Money_array[i]){
            min_money = Money_array[i];
            min_index = i;
        }
    }

    int Type_fee[3] = {183, 383, 983};
    printf("%d\n", min_money);
    printf("%d\n", Type_fee[min_index]);
}

int main(){
    // 輸入每月網內、網外、市話、通話時間(秒)及網內、網外簡訊則數，求花費最少的資費類型。
    int Spend_array[5]; // inside_time, outside_time, phone_time; (通話時間) // int inside_text, outside_text; // 簡訊數量
    scanf("%d %d %d %d %d", &Spend_array[0], &Spend_array[1], &Spend_array[2], &Spend_array[3], &Spend_array[4]);

    int Money_array[3] = {183, 383, 983};
    Money_array[0] = Get_money(183, 0, Spend_array);
    Money_array[1] = Get_money(383, 1, Spend_array);
    Money_array[2] = Get_money(983, 2, Spend_array);

    Judge_min_fee(Money_array);
}