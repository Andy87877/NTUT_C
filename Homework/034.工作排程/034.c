#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_M 10
#define MAX_P 10

typedef struct {
        int mach; // 機器編號
        int time; // 執行時間
} Op;

typedef struct {
        int done; // 完成時間
        int job;  // 工作編號
        int idx;  // 工序索引
        int mach;
        int t;
        int start;
} Cand;

int my_max(int a, int b) { return a > b ? a : b; }

// 讀取輸入
void read(int *n, int *m, Op job[MAX_M][MAX_P], int plen[MAX_M], int *total) {
    scanf("%d %d", n, m);
    *total = 0;
    for (int i = 0; i < *m; ++i) {
        int p;
        scanf("%d", &p);
        plen[i] = p;
        for (int j = 0; j < p; ++j) {
            int mach, t;
            scanf("%d %d", &mach, &t);
            job[i][j].mach = mach;
            job[i][j].time = t;
        }
        *total += p;
    }
}

// 狀態初始化
void init(int n, int m, int machT[MAX_N], int jobT[MAX_M], int cur[MAX_M],
          int fin[MAX_M]) {
    for (int i = 0; i < n; ++i) machT[i] = 0;
    for (int i = 0; i < m; ++i) {
        jobT[i] = 0;
        cur[i] = 0;
        fin[i] = 0;
    }
}

// 計算候選工序
int get_cand(int m, Op job[MAX_M][MAX_P], int plen[MAX_M], int cur[MAX_M],
             int machT[MAX_N], int jobT[MAX_M], Cand cand[MAX_M]) {
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (cur[i] < plen[i]) {
            int idx = cur[i];
            int mach = job[i][idx].mach;
            int t = job[i][idx].time;
            int start = my_max(machT[mach], jobT[i]);
            int done = start + t;
            cand[cnt].done = done;
            cand[cnt].job = i;
            cand[cnt].idx = idx;
            cand[cnt].mach = mach;
            cand[cnt].t = t;
            cand[cnt].start = start;
            cnt++;
        }
    }
    return cnt;
}

// 找最佳工序
Cand pick_best(Cand cand[MAX_M], int cnt) {
    Cand best = cand[0];
    for (int i = 1; i < cnt; ++i) {
        if (cand[i].done < best.done ||
            (cand[i].done == best.done && cand[i].job < best.job)) {
            best = cand[i];
        }
    }
    return best;
}

// 更新狀態
void update(const Cand *best, int machT[MAX_N], int jobT[MAX_M], int cur[MAX_M],
            int *done_cnt, int fin[MAX_M], int plen[MAX_M]) {
    int t = best->done, j = best->job, m = best->mach;
    machT[m] = t;
    jobT[j] = t;
    cur[j]++;
    (*done_cnt)++;
    if (cur[j] == plen[j]) fin[j] = t;
}

// 計算總完成時間
long long sum_fin(int fin[MAX_M], int m) {
    long long sum = 0;
    for (int i = 0; i < m; ++i) sum += fin[i];
    return sum;
}

void solve() {
    int n, m;
    Op job[MAX_M][MAX_P];
    int plen[MAX_M], total;
    read(&n, &m, job, plen, &total);

    int machT[MAX_N], jobT[MAX_M], cur[MAX_M], fin[MAX_M];
    init(n, m, machT, jobT, cur, fin);

    int done_cnt = 0;
    while (done_cnt < total) {
        Cand cand[MAX_M];
        int cnt = get_cand(m, job, plen, cur, machT, jobT, cand);
        if (cnt == 0) break;
        Cand best = pick_best(cand, cnt);
        update(&best, machT, jobT, cur, &done_cnt, fin, plen);
    }
    printf("%lld\n", sum_fin(fin, m));
}

int main() {
    solve();
    return 0;
}