// getche() 測試
#include <stdio.h>
int main() {
    int i=0;
    char go='y';
    do {
        i++;
        printf("; Loop %d\n", i);
        printf("Continue(y/n):");
        go = getche();
    } while (go=='y');
    printf("\nTotal Loop %d\n", i);
    return 0;
}