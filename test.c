#include <stdio.h>

void print(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d, ", a[i]);
    printf("\n");
}
void insertionSort(int a[], int n) {
    int target = 0, i = 0, j = 0;
    for (i = 1; i < n; i++) {
        target = a[i];
        for (j = i; (j > 0) && (a[j - 1] > target); j--) {
            // print(a, n);
            a[j] = a[j - 1];
        }
        a[j] = target;
        print(a, n);
        // printf("\n");
    }
}
int main() {
    int a[] = {89, 78, 54, 16, 64, 3, 47};
    insertionSort(a, 7);
    return 0;
}