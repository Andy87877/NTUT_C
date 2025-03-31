#include <stdio.h>
#include <stdlib.h>

#define DICE_amount 4

/*
array [4個骰子][上,前,右,下,後,左]
-->  4*[X,X,X,X,X,X]
1背對6 2背對5 3背對4
*/

// 1背對6 2背對5 3背對4
int oppsite(int index) { return abs(index - 5); }

void Print_all_dice(int *all_dice[]){
    for (int i = 0; i < DICE_amount; i++){
        for (int j = 0; j < 6; j++){
            printf("%d ", all_dice[i][j]);
        }
        printf("\n");
    }
}
// 初始化骰子
void init_dice(int dice[]) {
    // up front right down back left
    dice[0] = 1;
    dice[1] = 4;
    dice[2] = 3;
    dice[3] = oppsite(dice[0]);
    dice[4] = oppsite(dice[1]);
    dice[5] = oppsite(dice[2]);

    for (int i = 0; i < 5; i++){
        printf("%d ", dice[i]);
    }
    printf("\n");
}

void change_dice(int operation, int dice[]) {
    int now_dice[6];
    for (int i = 0; i < 6; i++) {
        printf(dice[i]);
        now_dice[i] = dice[i];
    }
    printf("change");

    // 前後左右
    // [0上,1前,2右,3下,4後,5左]
    int index_change = 0;
    if (operation == 1) index_change = 1;
    if (operation == 2) index_change = 4;
    if (operation == 3) index_change = 5;
    if (operation == 4) index_change = 2;
    now_dice[0] = dice[index_change]; // 上面改變
    now_dice[index_change] = dice[3]; // 改變的變底部

    now_dice[3] = oppsite(oppsite(now_dice[0]));
    now_dice[4] = oppsite(oppsite(now_dice[1]));
    now_dice[5] = oppsite(oppsite(now_dice[2]));

    for (int i = 0; i < 6; i++) {
        dice[i] = now_dice[i];
    }
}

void change_All_dice(int all_dice[]) {
    int operation;
    for (int i = 0; i < DICE_amount; i++) {
        scanf("%d", &operation);
        change_dice(operation, all_dice[i]);
    }
}

int main() {
    int all_dice[DICE_amount][6];

    for (int i = 0; i < DICE_amount; i++) {
        init_dice(all_dice[i]);
    }

    int n; // 次數
    scanf("%d", &n);
    Print_all_dice(all_dice);
    for (int times = 0; times < n; times++) {
        change_All_dice(all_dice);
        Print_all_dice(all_dice);
    }
}
