#include <stdio.h>
#include <string.h>

int C(int M) {
    int answer = 0;

    while (M >= 2) {
        answer += 1;
        if (M % 2 == 0) {
            M /= 2;
        } else {
            M = (M + 1) / 2;
        }
    }

    return answer;
}

int Bin_to_Dec(char Binary[]) {
    int Decimal = 0;
    for (int i = 0; i < 8; i++) {
        Decimal = Decimal * 2 + (Binary[i] - '0');
    }
    return Decimal;
}

void Dec_to_Binary_output(int Dec) {
    int Temp_number = Dec;
    char Binary_output[4];
    for (int i = 3; i >= 0; i--) {
        if (Temp_number % 2 == 0) {
            Binary_output[i] = '0';
        } else {
            Binary_output[i] = '1';
        }
        Temp_number /= 2;
    }

    // printf
    for (int i = 0; i < 4; i++) {
        printf("%c", Binary_output[i]);
    }
    printf("\n");
    return;
}

void judge(char Memory[]) {
    int reward_count = 0;
    reward_count = C(Bin_to_Dec(Memory));
    // printf("%d\n", reward_count);

    Dec_to_Binary_output(reward_count);
}

int main() {
    char Memory[8];

    while (1 == 1) {
        scanf("%s", Memory);
        if (strcmp(Memory, "-1") == 0) {
            break;
        }
        judge(Memory);
    }
}