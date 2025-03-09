#include <stdio.h>

// State
#define Start 1
#define Int_number 2
#define float_number 3
#define variable_string 4
#define normal_string 5

// Check_char
#define Number 10
#define Zero_Number 20
#define Negative_signed 30
#define Dot 40
#define Letter 50
#define Other 60

int Check_char_function(char char_check) {
    if (char_check == '0') {
        return Zero_Number;
    }
    if (char_check >= '1' && char_check <= '9') {
        return Number;
    }
    if (char_check == '-') {
        return Negative_signed;
    }
    if (char_check == '.') {
        return Dot;
    }
    if ((char_check >= 'a' && char_check <= 'z') ||
        (char_check >= 'A' && char_check <= 'Z')) {
        return Letter;
    }

    return Other
}

void judge(char check_string[], int index, int State) {
    int char_state = Check_char_function(check_string[index]);
    if (State == Start) {
        if (char_state == Number || char_state == Zero_Number || char_state == Negative_signed) {
            State = Int_number;
        }
        if (char_state == Dot) {
            State = normal_string;
        }
        if (char_state == )
    }
}

int main() {
    int times;
    char check_string[100];
    scanf("%d", &times);

    for (int check_times = 0; check_times < times; check_times++) {
        judge(check_string, 0);
    }
}