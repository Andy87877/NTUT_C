#include <stdio.h>
double getMile(int km, int m) {
    double mile = (km + m/1000.0)/1.609;
    return mile;
}
void compute(int km, int m) {
    double mile = getMile(km, m);
    int yard, mile_i = mile;
    yard = (mile-mile_i)*1760;
    printf("mile = %d, yard = %d\n", mile_i, yard);
}
int main() {
    compute(5, 500);
    return 0;
}
