#include <stdio.h>
#include <time.h>
long g(int n) {
    if (n<1) return 1;
    else return (g(n-1)+g(n-2)+g(n-3));
}
int main() {
    struct timespec st = {0, 0};
    struct timespec et = {0, 0};
    clock_gettime(CLOCK_REALTIME, &st);
    g(10); 
    clock_gettime(CLOCK_REALTIME, &et);
    printf("%ld ms\n",(et.tv_sec-st.tv_sec)*1000+(et.tv_nsec-st.tv_nsec)/1000000); //毫秒
    return 0;
}