#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
請使用以下提供的Union以及Struct進行實作

*/
typedef enum { OUT, BASE_HIT } play_type_t;

typedef union {
        int base_hit;  // 1~4: number of bases
        char out_kind; // 'F', 'S', 'G'
} play_result_t;

typedef struct {
        play_type_t type;
        play_result_t result;
} play_t;

typedef struct {
        int no;         // 擊球員的打擊次數
        play_t data[5]; // 擊球員的打擊結果
} basePlayer_t;

/**/

void Change_base(int base[], int move, int *score) {
    for (int i = 4 - move; i < 4; i++) {
        if (base[i] == 1) *score += 1;
        base[i] = 0;
    }

    if (move == 0) {
        for (int i = 0; i < 4; i++) {
            base[i] = 0;
        }
        return;
    }

    for (int i = 0; i < 4 - move; i++) {
        base[move + i] = base[i];
    }
    base[move - 1] = 1;
}

// 主函式
int main() {
    basePlayer_t player_array[9];

    // 輸入資料
    for (int i = 0; i < 9; i++) {

        // 打擊次數
        scanf("%d ", &player_array[i].no);
        for (int t = 0; t < player_array[i].no; t++) {
            char char_input[2];
            scanf("%s", &char_input);
            getchar();
            char now_result = char_input[0];
            char now_type = char_input[1]; // 狀態和結果

            if (now_type == 'O'){ // 出局
                player_array[i].data[t].type = OUT;
            } else {
                player_array[i].data[t].type = BASE_HIT;
            }

            if (player_array[i].data[t].type == OUT) { // 出局
                player_array[i].data[t].result.out_kind = now_result;
            } else { // 安打
                player_array[i].data[t].result.base_hit = now_result;
            }
        }
    }

    // 模擬
    int out_now = 0, out_end;
    int score = 0;
    scanf("%d", &out_end);

    int base[4] = {0, 0, 0, 0};

    for (int t = 0; t < 5; t++) {
        for (int i = 0; i < 9; i++) {
            // printf("%d %d %d\n", t, i, out_now);

            if (player_array[i].data[t].type == OUT) { // 出局
                out_now++;

                if (out_end == out_now) break;
                if (out_now % 3 == 0) {
                    Change_base(base, 0, &score);
                }
                continue;
            } 

            char now_base_hit = player_array[i].data[t].result.base_hit;
            int number_hit = 0;
            if (now_base_hit == )
            Change_base(base, now_base_hit, &score);
        }

        if (out_end == out_now) break;
    }

    printf("%d", score);
}