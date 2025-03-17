#include <stdio.h>
#include <stdlib.h>
int main() {
    int *p;
    int *num = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) *(num + i) = i;
    p = num;
    p++;
    printf("%d, ", (*p)++); // p 值不會變，取1後變2
    printf("%d, ", ++(*p)); // p 值不會變，2變3，取3
    printf("%d, ", *(p++)); // p 值會變，取3，p指向下一個 2
    printf("%d, ", *p++);   // 取2，p再 +1
    printf("\n%d, %d, %d, %d", num[0], num[1], num[2], num[3]);
    free(num);
}