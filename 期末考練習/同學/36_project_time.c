#include <stdio.h>

typedef struct WorkNode {
        int time;

        int nextCount;
        int nextWork[100];
} WorkNode;

int CountWorkTime(WorkNode* database, int nowWorkIndex) {
    if (database[nowWorkIndex].nextCount == 0)
        return database[nowWorkIndex].time;

    int maxTime = 0;
    for (int i = 0; i < database[nowWorkIndex].nextCount; i++) {
        int t = CountWorkTime(database, database[nowWorkIndex].nextWork[i]);
        if (maxTime < t) maxTime = t;
    }

    return maxTime + database[nowWorkIndex].time;
}
int WorkCounter() {
    int m;
    scanf("%d", &m);

    WorkNode database[100];
    for (int i = 0; i < m; i++) {
        scanf("%d", &database[i].time);
        scanf("%d", &database[i].nextCount);
        for (int j = 0; j < database[i].nextCount; j++) {
            scanf("%d", &database[i].nextWork[j]);
            database[i].nextWork[j] -= 1;
        }
    }

    int max = 0;
    for (int i = 0; i < m; i++)
        if (database[i].time > max) max = database[i].time;

    int countAns = CountWorkTime(database, 0);
    return countAns > max ? countAns : max;
}

int main() {
    int n;
    scanf("%d", &n);
    int ans[3];

    for (int i = 0; i < n; i++) {
        ans[i] = WorkCounter();
    }

    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
}