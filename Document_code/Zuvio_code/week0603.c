#include <stdio.h>
int main(){
    int m = 3;
    char array[] = "485617692712253";

    for (int i = 0; i < sizeof(array)-3; i++){
        if (array[i] == array[i+1] || array[i] == array[i+2] || array[i+1] == array[i+2]){
            continue;
        }

        printf("%c %c %c\n", array[i], array[i+1], array[i+2]);
    }
}