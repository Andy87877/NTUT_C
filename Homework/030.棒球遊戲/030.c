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

int Change_base(int base[], int move) {
    int now_score = 0;
    if (move == 0) {
        base[4] = 0;
        base[3] = 0;
        base[2] = 0;
        base[1] = 0;
    }
    if (move == 1) {
        if (base[3] == 1) now_score++;
        base[3] = base[2];
        base[2] = base[1];
        base[1] = 1;
    }
    if (move == 2) {
        if (base[3] == 1) now_score++;
        if (base[2] == 1) now_score++;
        base[3] = base[1];
        base[2] = 1;
        base[1] = 0;
    }
    if (move == 3) {
        if (base[3] == 1) now_score++;
        if (base[2] == 1) now_score++;
        if (base[1] == 1) now_score++;
        base[3] = 1;
        base[2] = 0;
        base[1] = 0;
    }
    if (move == 4) { // 全壘打
        now_score++;
        if (base[3] == 1) now_score++;
        if (base[2] == 1) now_score++;
        if (base[1] == 1) now_score++;
        base[3] = 0;
        base[2] = 0;
        base[1] = 0;
    }
    return now_score;
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

            if (now_type == 'O') { // 出局
                player_array[i].data[t].type = OUT;
            } else {
                player_array[i].data[t].type = BASE_HIT;
            }

            if (player_array[i].data[t].type == OUT) { // 出局
                player_array[i].data[t].result.out_kind = now_result;
            } else { // 安打
                int hit_base = 0;
                if (now_result == 'H') {
                    hit_base = 4;
                } else {
                    hit_base = now_result - '0';
                }
                player_array[i].data[t].result.base_hit = hit_base;
            }
        }
    }

    // 模擬
    int out_now = 0, out_end;
    int score = 0;
    scanf("%d", &out_end);

    int base[5] = {0, 0, 0, 0, 0}; // 0 1 2 3 本壘

    for (int t = 0; t < 5; t++) {
        for (int i = 0; i < 9; i++) {
            // printf("%d %d %d\n", t, i, out_now);

            if (player_array[i].data[t].type == OUT) { // 出局
                out_now++;

                if (out_end == out_now) break;
                if (out_now % 3 == 0) {
                    score += Change_base(base, 0);
                }
                continue;
            }

            int now_base_hit = player_array[i].data[t].result.base_hit;
            score += Change_base(base, now_base_hit);
        }

        if (out_end == out_now) break;
    }

    printf("%d", score);
}