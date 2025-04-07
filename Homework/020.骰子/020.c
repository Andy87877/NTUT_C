#include <stdio.h>
#include <stdlib.h>

#define DICE_amount 4

/*
array [4個骰子][上,前,右,下,後,左]
-->  4*[X,X,X,X,X,X]
1背對6 2背對5 3背對4
*/

int Max(int a, int b) {
    if (a > b) return a;
    return b;
}

void Print_all_dice(int all_dice[][6]) {
    for (int i = 0; i < DICE_amount; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d ", all_dice[i][j]);
        }
        printf("\n");
    }
}

// 背面[0上,1前,2右,3下,4後,5左]
int opposite(int index) {
    int mapping[6] = {3, 4, 5, 0, 1, 2}; // 對應索引值
    return mapping[index];
}

// 初始化骰子
void init_dice(int dice[]) {
    dice[0] = 1; // 上
    dice[1] = 4; // 前
    dice[2] = 2; // 右
    dice[3] = 6; // 下
    dice[4] = 3; // 後
    dice[5] = 5; // 左
}

void change_All_dice(int all_dice[DICE_amount][6]) {
    int operation;
    for (int dice_index = 0; dice_index < DICE_amount; dice_index++) {
        scanf("%d", &operation);
        int now_dice[6];
        for (int j = 0; j < 6; j++) {
            now_dice[j] = all_dice[dice_index][j];
        }
        // 前後左右
        // [0上,1前,2右,3下,4後,5左]
        int index_change = 0;
        if (operation == 1) index_change = 1;
        if (operation == 2) index_change = 4;
        if (operation == 3) index_change = 5;
        if (operation == 4) index_change = 2;
        now_dice[0] = all_dice[dice_index][index_change]; // 上面改變
        now_dice[index_change] = all_dice[dice_index][3]; // 改變的變底部
        now_dice[3] =
            all_dice[dice_index][opposite(index_change)]; // 底部的變改變的底部
        now_dice[opposite(index_change)] = all_dice[dice_index][0];

        for (int j = 0; j < 6; j++) {
            all_dice[dice_index][j] = now_dice[j];
        }
    }
}

// 得到分數(已經取出頂部的點數)
int Get_score(int array[]) {
    int times_index = 0;
    int point_number[DICE_amount]; // 點數的數字
    int point_times[DICE_amount];  // 點數出現的次數

    // 檢查點數與次數
    for (int i = 0; i < DICE_amount; i++) {
        int flag = 1;
        for (int j = 0; j < times_index; j++) {
            if (point_number[j] == array[i]) {
                flag = 0;
                point_times[j]++;
                break;
            }
        }
        if (flag) {
            point_times[times_index] = 1;
            point_number[times_index] = array[i];
            times_index++;
        }
    }

    if (times_index == 1) { // 點數均相同,稱一色,計18點
        return 18;
    }
    // 若四顆點數均不同;或有三顆點數相同,一顆不同,計 0點
    if (times_index == 4) {
        return 0;
    }
    if ((times_index == 2) && (point_times[0] != 2)) {
        return 0; // 有兩個不同的點 其中第一個點沒有出現兩次
    }

    // 若兩顆點數相同,另兩顆點數也相同,但兩組兩顆點數不同
    if (times_index == 2 && point_times[0] == 2) {
        return 2 * (Max(point_number[0], point_number[1]));
    }

    // 若兩顆點數相同,另兩顆點數不同,則點數計算為加總兩顆不同點數
    int score = 0;
    for (int i = 0; i < 3; i++) {
        if (point_times[i] == 1) {
            score += point_number[i];
        }
    }
    return score;
}

int main() {
    int all_dice[DICE_amount][6];

    for (int i = 0; i < DICE_amount; i++) {
        init_dice(all_dice[i]);
    }

    int n; // 次數
    scanf("%d", &n);
    for (int times = 0; times < n; times++) {
        change_All_dice(all_dice);
        // Print_all_dice(all_dice);
    }

    int top_array[DICE_amount];
    for (int i = 0; i < DICE_amount; i++) {
        top_array[i] = all_dice[i][0];
    }
    int score = Get_score(top_array);
    printf("%d", score);
}