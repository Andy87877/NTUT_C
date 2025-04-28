#include <stdio.h>
#define N 8
int isEmpty(int set) {
    if (set==0) return 1;
    else return 0;
}
int insertElement(int set, int e) {
    return (set | (1<<e));
}
int removeElement(int set, int e) {
    return (set & ~(1<<e));
}
int intersection(int set1, int set2) {
    return (set1 & set2);
}
int unionSet(int set1, int set2) {
    return (set1 | set2);
}
void print(int set) {
    printf("[");
    for (int i=0; i<N; i++) {
        if (((set>>i)&1)==1){
            printf("%d, ", i);
        }
    }
    printf("]\n");
}

void test() {
    int set1=0, set2=1, set3=2;
    printf("%d\n", isEmpty(set1));
    set1 = insertElement(set1, 6);
    set2 = insertElement(set2, 6);
    printf("set1:"); print(set1=insertElement(set1, 1));
    printf("set2:"); print(set2=insertElement(set2, 3));
    printf("set3:"); print(set3 = unionSet(set1, set2));
    printf("set3:"); print(set3 = removeElement(set3,1));
    printf("----:"); print(intersection(set1, set2));
    printf("set3:"); print(set3=insertElement(set3,1));
}

int main() {
    test();
    return 0;
}