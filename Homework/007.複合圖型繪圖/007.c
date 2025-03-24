#include <stdio.h>
#include <stdlib.h>

void print_repeat_word(int times, char word){
    for (int i = 0; i < times; i++){
        printf("%c", word);
    }
}

void condition_1(int M){
    void print_starANDword(int times, char word){
        for (int i = 0; i < times; i++){
            printf("*%c", word);
        }
        printf("*");
    }

    char repeat_char[3] = "ABC";

    for (int i = 1; i <= M; i++){
        print_repeat_word(M-i, '#');
        print_starANDword(i-1, repeat_char[(i+1)%3]);
        print_repeat_word(M-i, '#');
        printf("\n");
    }
}

void condition_2(int M){
    
    void print_number_down(int times){
        for (int i = times; i > 0; i--){
            printf("%d", i);
        }
    }

    void print_number_up(int times){
        for (int i = 1; i <= times; i++){
            printf("%d", i);
        }
    }
    

    for (int i = 1; i <= M; i++){
        print_number_down(i);
        print_repeat_word((M-i+1)*2, '*');
        print_number_up(i);
        printf("\n");
    }
}

// 判斷輸入錯誤
void judge_ERROR(int N, int M){
    int is_ERROR = 0;
    if (!(N == 1 || N == 2)){
        is_ERROR = 1;
    }
    if (!(M >= 2 && M <= 9)){
        is_ERROR = 1;
    }

    if (is_ERROR){
        printf("error");
        exit(0);
    }
}

int main(){
    int N, M;
    scanf("%d", &N);
    scanf(" %d", &M);

    judge_ERROR(N, M);

    if (N == 1){
        condition_1(M);
    } else {
        condition_2(M);
    }
}