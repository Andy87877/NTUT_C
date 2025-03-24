// 一維陣列基本操作

/*
int score[4]={66,23,22,1};
int score[]={66,23,22,1};
int score[4]={0};  // 給第一個元素值
*/

#include <stdio.h>
int main() {
    int score[4];
    score[0] = 66;
    score[1] = 23;
    2 [score] = 22; // 也可以這樣寫//score[2] = 22;
    score[3] = 1;
    for (int i = 0; i <= 3; i++) printf("score[%d]=%d\n", i, score[i]);
    return 0;
}
