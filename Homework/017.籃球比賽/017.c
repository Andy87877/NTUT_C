#include <stdio.h>

void Judge(int *first_or_second_Win, int *first_team_score,
           int *second_team_score) {
    for (int i = 0; i < 4; i++) { // 四節
        int score_1, score_2;
        scanf("%d %d", &score_1, &score_2);

        *first_team_score += score_1;
        *second_team_score += score_2;
    }

    if (*first_team_score > *second_team_score) {
        *first_or_second_Win = 0;
    } else {
        *first_or_second_Win = 1;
    }
}

int main() {
    int score_array[3] = {0, 0, 0}; // A B C
    int win_array[3] = {0, 0, 0};   // A B C
    int win_max_index = 0;

    int times;
    scanf("%d", &times);

    // 輸入資訊
    for (int t = 0; t < times; t++) {
        int win_team_index, first_or_second_Win;
        int first_team_score = 0, second_team_score = 0;

        // get index
        char first_team, second_team;
        int char_A = 'A';
        scanf(" %c %c ", &first_team, &second_team);

        int first_team_index = first_team - char_A;
        int second_team_index = second_team - char_A;
        // printf("%d %d\n", first_team_index, second_team_index);

        // Judge
        Judge(&first_or_second_Win, &first_team_score, &second_team_score);

        // printf("%d %d %d\n", first_or_second_Win, first_team_score, second_team_score);

        score_array[first_team_index] += first_team_score;
        score_array[second_team_index] += second_team_score;

        // Win
        if (first_or_second_Win == 0) {
            win_team_index = first_team_index;
        } else {
            win_team_index = second_team_index;
        }

        win_array[win_team_index]++;
        if (win_array[win_team_index] > win_array[win_max_index]) {
            win_max_index = win_team_index;
        }
    }

    // 輸出
    char winner = 'A' + win_max_index;
    int winner_score = score_array[win_max_index];
    printf("%c %d", winner, winner_score);
}