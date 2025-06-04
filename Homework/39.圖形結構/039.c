#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14

#define ShapeText(TYPE) char name[10];
double (*perimeter)(struct TYPE*);
double (*area)(struct TYPE*);

typedef struct shape_s {
        ShapeText(shape_s);
} shape_t;

typedef struct circle_s {
        ShapeText(circle_s);
        double radius;
} circle_t;

double now_perimeter, now_area;
double total_perometer = 0, total_area = 0;

void judge_circle() {
    int radius;
    scanf("%d", &radius);

    now_perimeter = radius * 2 * PI;
    now_area = radius * radius * PI;

    printf("%.2f %.2f\n", now_perimeter, now_area);
    total_perometer += now_perimeter;
    total_area += now_area;
}

void judge_rectangle() {
    int length, width;
    scanf("%d %d", &length, &width);

    now_perimeter = 2 * (length + width);
    now_area = length * width;

    printf("%.2f %.2f\n", now_perimeter, now_area);
    total_perometer += now_perimeter;
    total_area += now_area;
}

void judge_square() {
    int edge;
    scanf("%d", &edge);

    now_perimeter = edge * 4;
    now_area = edge * edge;

    printf("%.2f %.2f\n", now_perimeter, now_area);
    total_perometer += now_perimeter;
    total_area += now_area;
}

void judge_triangle() {
    int edge[3];
    scanf("%d %d %d", &edge[0], &edge[1], &edge[2]);

    double s;
    now_perimeter = edge[0] + edge[1] + edge[2];
    s = now_perimeter / 2;
    now_area = sqrt(s * (s - edge[0]) * (s - edge[1]) * (s - edge[2]));

    printf("%.2f %.2f\n", now_perimeter, now_area);
    total_perometer += now_perimeter;
    total_area += now_area;
}

void judge_all() {
    char c_type;
    getchar();
    scanf("%c", &c_type);

    if (c_type == 'C') judge_circle();
    if (c_type == 'R') judge_rectangle();
    if (c_type == 'S') judge_square();
    if (c_type == 'T') judge_triangle();
}

int main() {
    int do_times;
    scanf("%d", &do_times);

    for (int time = 0; time < do_times; time++) {
        judge_all();
    }

    printf("%.2f %.2f\n", total_perometer, total_area);
}