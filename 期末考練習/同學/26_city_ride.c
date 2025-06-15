#if 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Sum(int* data, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++) sum += data[i];
    return sum;
}

void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }
bool next_permutation(int* a, int n) {
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i < 0) return false;

    int j = n - 1;
    while (a[j] <= a[i]) j--;
    swap(&a[i], &a[j]);

    for (int l = i + 1, r = n - 1; l < r; l++, r--)
        swap(&a[l], &a[r]);
    return true;
}
void Sort(int* a, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            if (a[i] > a[j]) swap(&a[i], &a[j]);
        }
    }
}
int main()
{
	int table[10][10] = { 0 };
	int pathData[10] = { 0 };
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &table[i][j]);

    int minPath = INT_MAX;
    int a[10] = { 0 };
    for (int i = 1; i < n; i++) a[i] = i;

    do {
        int path = 0;
        for (int i = 0; i < n-1; i++)
        {
            if (table[a[i]][a[i + 1]] == -1)
            {
                path = -1;
                break;
            }
            path += table[a[i]][a[i + 1]];
        }
        if (path == -1) continue;

        if (path < minPath)
        {
            minPath = path;
            for (int i = 0; i < n; i++) pathData[i] = a[i];
        }
    } while (next_permutation(&a[1], n - 1));


    int stopCityIndex;
    int stopBegin, stopEnd;;
    scanf("%d %d %d", &stopCityIndex, &stopBegin, &stopEnd);
    table[stopBegin-1][stopEnd-1] = -1;

    minPath = INT_MAX;
    for (int i = 0; i < n; i++) a[i] = pathData[i];
    Sort(&a[stopCityIndex], n - stopCityIndex);
    do {
        int path = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (table[a[i]][a[i + 1]] == -1)
            {
                path = -1;
                break;
            }
            path += table[a[i]][a[i + 1]];
        }
        if (path == -1) continue;

        if (path < minPath)
        {
            minPath = path;
            for (int i = 0; i < n; i++) pathData[i] = a[i];
        }
    } while (next_permutation(&a[stopCityIndex], n - stopCityIndex));


    for (int i = 0; i < n; i++) printf("%d ", pathData[i]+1);
    int sum = 0;
    for (int i = 0; i < n-1; i++) sum += table[pathData[i]][pathData[i + 1]];
    printf("\n%d", sum);
}

#endif
