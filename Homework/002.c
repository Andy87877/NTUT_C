#include <stdio.h>

int main(){
    int arr[4]; // 一、二、三壘的狀況 0沒人 1有人
    int score = 0, out = 0;

    arr[1] = 0; arr[2] = 0; arr[3] = 0; // 初始化

    int i;

    // 輸入和判斷
    for (i = 0; i < 5; i++){ 
        int now;
        scanf("%d", &now);

        if (now == 0){ // 出局
            out++;
            if (out == 3){ // 三人出局
                arr[1] = 0; arr[2] = 0; arr[3] = 0; // 初始化
                out = 0;
            }
        }
        
        if (now == 1){ // 一壘安打
            score += arr[3];
            arr[3] = arr[2];
            arr[2] = arr[1];
            arr[1] = 1;
        }

        if (now == 2){ // 二壘安打
            score += (arr[3] + arr[2]);
            arr[3] = arr[1];
            arr[2] = 1;
            arr[1] = 0;
        }

        if (now == 3){ // 三壘安打
            score += (arr[3] + arr[2] + arr[1]);
            arr[3] = 1;
            arr[2] = 0;
            arr[1] = 0;
        }

        if (now == 4){ // 全壘打
            score += (arr[3] + arr[2] + arr[1] + 1);
            arr[3] = 0;
            arr[2] = 0;
            arr[1] = 0;
        }
    }

    printf("%d\n", score);
    printf("%d %d %d\n", arr[1], arr[2], arr[3]);
}