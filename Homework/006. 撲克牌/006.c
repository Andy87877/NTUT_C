#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double card_to_score(char card[2]){
    if (strcmp(card, "10") == 0){
        return 10;
    }
    if (card[0] == 'A'){
        return 1;
    }
    if (card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
        return 0.5;
    }
    
    return (card[0] - '0');
}

void print_score(double score){
    if ((int)score == score){
        printf("%d\n", (int)score);
    } else {
        printf("%.1f\n", score);
    }
}

double Get_score(){
    double score = 0;
    char card[3];
    for (int i = 0; i < 3; i++){
        scanf("%s", card);
        score += card_to_score(card);
        // print_score(score);
    }
    if (score > 10.5) score = 0;

    return score;
}

void judge_Winner(double X_score, double Y_score){
    if (X_score == Y_score){
        printf("Tie");
    } else if (X_score > Y_score){
        printf("X Win");
    } else {
        printf("Y Win");
    }
}

int main(){
    double X_score, Y_score;
    X_score = Get_score();
    // printf("test\n");
    Y_score = Get_score();
    print_score(X_score);
    print_score(Y_score);
    judge_Winner(X_score, Y_score);
}