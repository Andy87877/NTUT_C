#include <stdio.h>

int main(){
    int num = 100;

    while (num >= 1){
        printf("%d\n", num);
        num >>= 1;
    }
}