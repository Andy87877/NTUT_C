// 狀態轉換圖 (Exercise – 判斷整數、浮點數、字串)

#include <stdio.h>
#define START 0
#define IH 1  // integer head
#define IB 2  // integer body
#define ID 3 // integer defined
#define FI 4 // floating integer part
#define FP 5 // floating point
#define FF 6 // floating decimal
#define FD 7 // floating defined
#define STRING 8
#define NEG 9 // negative
// 計算小數點的值
double getfValue(char key, int fPoint) {
    int num = (key - '0');
    double r = num;
    for (int i = 0; i < fPoint; i++) r = r / 10;
    return r;
}

int getState(int state, char key) { // 狀態轉換圖
    if (state == START && key == '0')
        return FI;
    else if (state == START && key >= '1' && key <= '9')
        return IH;
    else if (state == START && key >= '-')
        return NEG;
    else if (state == NEG && key == '0')
        return FI;
    else if (state == NEG && key >= '1' && key <= '9')
        return IH;
    else if (state == FI && key == '.')
        return FP;
    else if (state == IH && key == '.')
        return FP;
    else if (state == IB && key == '.')
        return FP;
    else if (state == FP && key >= '0' && key <= '9')
        return FF;
    else if (state == FF && key >= '0' && key <= '9')
        return FF;
    else if (state == FF && key == '\n')
        return FD;
    else if (state == IH && key >= '0' && key <= '9')
        return IB;
    else if (state == IB && key >= '0' && key <= '9')
        return IB;
    else if (state == IB && key == '\n')
        return ID;
    else
        return STRING;
}

int checkInput() {
    char key;
    int state = START, neg = 1;
    int iPart = 0, fPoint = 0;
    float fPart = 0;
    printf(">");
    while (1) {
        key = getchar();
        state = getState(state, key);
        if (state == STRING) { // 非整數、浮點數
            printf("string");
            break;
        } else if (state == FD) { // 浮點數
            if (neg == -1) printf("negative ");
            printf("float:%f\n", (iPart + fPart) * neg);
            break;
        } else if (state == ID) { // 整數
            if (neg == -1) printf("negative ");
            printf("integer: %d\n", iPart * neg);
            break;
        } else if (state == NEG)
            neg = -1;
        else if (state == IH)
            iPart = key - '0';
        // 計算整數的值
        else if (state == IB)
            iPart = iPart * 10 + key - '0';
        else if (state == FF) {
            // 小數點多一位
            fPoint++;
            // 計算小數點的值
            fPart = fPart + getfValue(key, fPoint);
        }
    }
    return state;
}

int main() {
    while (1) {
        if (checkInput() == STRING) break;
    }
    return 0;
}