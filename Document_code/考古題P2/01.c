#include <stdio.h>

void f11(char *s) {
    while (*s != '\0') {
        if (*s >= 'a' && *s <= 'z')
            *s -= 32; // 小寫轉大寫
        else if (*s >= 'A' && *s <= 'Z')
            *s += 32; // 大寫轉小寫
        else if ((*s - '0') % 2)
            *s += 1;
        else
            *s -= 1;
        s++;
    }
}
void f12(char *s, char *s1, int size) {
    for (int i = 0; i < size; i++) *(s++) = *(s1++);
}
void f1() {
    char str[3][15] = {"48763", "ProGamer", "Baboon"};
    f12(str[2], "SeeYa", 15);
    for (int i = 0; i < 3; i++) f11(str[i]);
    for (int i = 0; i < 3; i++) printf("%s\n", str[i]);
}

int main(){
    f1();
}