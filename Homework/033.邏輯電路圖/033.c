#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GATEVALUE(Gate) int (*GataValue)()

typedef struct _Gate {
        int input1;
        int input2;
        GATEVALUE(Gate);
} Gate;

int GateORValue(Gate *gate) {
    // (input1 or input2) & 00111
    return (gate->input1 | gate->input2);
}
int GateANDValue(Gate *gate) {
    // (input1 and input2) & 00111
    return (gate->input1 & gate->input2) & 0x07;
}
int GateNOTValue(Gate *gate) {
    // !input1 & 00111
    return (~(gate->input1)) & 0x07;
}
int GateBUFFERValue(Gate *gate) {
    // input1 & 00111
    return (gate->input1) & 0x07;
}

int GateNANDValue(Gate *gate) {
    // (input1 nand input2) & 00111
    return (~(gate->input1 & gate->input2)) & 0x07;
}

int GateNORValue(Gate *gate) {
    // (input1 nor input2) & 00111
    return (~(gate->input1 | gate->input2)) & 0x07;
}

// 創造電路與判斷
void CreateGate(Gate *obj, char type[], int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    if (strcmp(type, "N") == 0) {
        obj->GataValue = GateNOTValue;
    } else if (strcmp(type, "B") == 0) {
        obj->GataValue = GateBUFFERValue;
    } else if (strcmp(type, "A") == 0) {
        obj->GataValue = GateANDValue;
    } else if (strcmp(type, "O") == 0) {
        obj->GataValue = GateORValue;
    } else if (strcmp(type, "NA") == 0) {
        obj->GataValue = GateNANDValue;
    } else if (strcmp(type, "NO") == 0) {
        obj->GataValue = GateNORValue;
    }
}

// 輸出答案 二進制
void Print_answer(int final_anwer) {
    printf("%d", (final_anwer >> 2) % 2);
    printf("%d", (final_anwer >> 1) % 2);
    printf("%d\n", (final_anwer >> 0) % 2);
}

int main() {
    int x1, x2, x3;
    scanf("%d %d %d", &x1, &x2, &x3);

    char type_1[4], type_2[4], type_3[4], type_4[4], type_5[4];
    scanf("%s %s %s %s %s", &type_1, &type_2, &type_3, &type_4, &type_5);

    // 創造電路
    Gate judge_Gate;

    int x1_ok;
    CreateGate(&judge_Gate, type_1, x1, x1);
    x1_ok = judge_Gate.GataValue(&judge_Gate);

    int x2_ok;
    CreateGate(&judge_Gate, type_2, x2, x2);
    x2_ok = judge_Gate.GataValue(&judge_Gate);

    int x3_ok;
    CreateGate(&judge_Gate, type_3, x3, x3);
    x3_ok = judge_Gate.GataValue(&judge_Gate);

    int x1_with_x2;
    CreateGate(&judge_Gate, type_4, x1_ok, x2_ok);
    x1_with_x2 = judge_Gate.GataValue(&judge_Gate);

    int final_answer;
    CreateGate(&judge_Gate, type_5, x1_with_x2, x3_ok);
    final_answer = judge_Gate.GataValue(&judge_Gate);

    Print_answer(final_answer);
}