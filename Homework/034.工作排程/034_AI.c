#include <stdio.h>  // 輸入輸出函式
#include <stdlib.h> // 常用函式，如 abs, malloc 等 (雖然這裡不太用，但習慣性包含)

// 定義常數，用於陣列大小。根據題目 N, M, P <= 10，我們可以使用 10 或 11
// 作為上限。 這裡用 10，假設陣列索引從 0 到 9。
#define MAX_MACHINES 10
#define MAX_JOBS 10
#define MAX_OPS_PER_JOB 10 // 每個工作的最大工序數量
#define MAX_CANDIDATES \
    MAX_JOBS // 候選工序的最大數量，每個工作最多有一個候選工序

// --- 資料結構定義 ---

// 定義一個結構體來表示一個工序的機器編號和需求時間
typedef struct {
        int machine_id; // 機器編號 Kij
        int duration;   // 需求時間 Tij
} Operation;

// 定義一個結構體來表示一個候選工序的所有相關資訊，用於計算和選擇
typedef struct {
        int completion_time; // 最早完成時間 Cij
        int job_id;          // 工作編號 i
        int op_index;        // 工序在該工作中的索引 j (0-based)
        int machine_k;       // 實際執行機器編號 Kij
        int time_t;          // 實際需求時間 Tij
        int start_time;      // 最早開始時間
} Candidate;

// --- 輔助函式 ---

// 比較兩個整數並返回較大的一個
int max(int a, int b) { return (a > b) ? a : b; }

// --- 核心函式 ---

// 讀取輸入資料並初始化相關變數
void read_input(int *N_ptr, int *M_ptr,
                Operation jobs_data[MAX_JOBS][MAX_OPS_PER_JOB],
                int num_operations_per_job[MAX_JOBS],
                int *total_operations_count_ptr) {
    scanf("%d %d", N_ptr, M_ptr);

    *total_operations_count_ptr = 0; // 初始化總工序計數

    for (int i = 0; i < *M_ptr; ++i) {
        int P; // 當前工作的工序數量
        scanf("%d", &P);
        num_operations_per_job[i] = P;

        for (int j = 0; j < P; ++j) {
            int machine_id, duration;
            scanf("%d %d", &machine_id, &duration);
            jobs_data[i][j].machine_id = machine_id;
            jobs_data[i][j].duration = duration;
        }
        *total_operations_count_ptr += P; // 將當前工作的工序數加到總數中
    }
}

// 初始化排程狀態變數
void initialize_schedule_state(int N, int M,
                               int machine_available_time[MAX_MACHINES],
                               int job_last_completion_time[MAX_JOBS],
                               int current_op_idx[MAX_JOBS],
                               int job_final_completion_time[MAX_JOBS]) {
    for (int i = 0; i < N; ++i) {
        machine_available_time[i] = 0; // 所有機器初始都空閒
    }
    for (int i = 0; i < M; ++i) {
        job_last_completion_time[i] = 0;  // 所有工作初始都未開始
        current_op_idx[i] = 0;            // 所有工作從第一個工序開始
        job_final_completion_time[i] = 0; // 所有工作最終完成時間初始為0
    }
}

// 計算所有候選工序的最早完成時間，並填充到 candidates_arr 陣列中
// 返回實際的候選工序數量
int calculate_candidates(int M,
                         const Operation jobs_data[MAX_JOBS][MAX_OPS_PER_JOB],
                         const int num_operations_per_job[MAX_JOBS],
                         const int current_op_idx[MAX_JOBS],
                         const int machine_available_time[MAX_MACHINES],
                         const int job_last_completion_time[MAX_JOBS],
                         Candidate candidates_arr[MAX_CANDIDATES]) {
    int num_candidates = 0;

    for (int job_id = 0; job_id < M; ++job_id) {
        // 檢查此工作是否還有未排程的工序
        if (current_op_idx[job_id] < num_operations_per_job[job_id]) {
            int op_index = current_op_idx[job_id];
            int machine_k = jobs_data[job_id][op_index].machine_id;
            int time_t = jobs_data[job_id][op_index].duration;

            // 計算此工序的最早開始時間
            // 必須等到其指定機器空閒，且其前一道工序完成 (如果存在)
            int start_time = max(machine_available_time[machine_k],
                                 job_last_completion_time[job_id]);

            // 計算此工序的最早完成時間
            int completion_time = start_time + time_t;

            // 將此工序作為候選加入列表
            candidates_arr[num_candidates].completion_time = completion_time;
            candidates_arr[num_candidates].job_id = job_id;
            candidates_arr[num_candidates].op_index = op_index;
            candidates_arr[num_candidates].machine_k = machine_k;
            candidates_arr[num_candidates].time_t = time_t;
            candidates_arr[num_candidates].start_time = start_time;

            num_candidates++;
        }
    }
    return num_candidates;
}

// 從候選列表中選擇最佳工序
// 返回最佳工序的 Candidate 結構體
Candidate find_best_candidate(const Candidate candidates_arr[MAX_CANDIDATES],
                              int num_candidates) {
    // 假設第一個候選就是目前最佳的，然後逐一比較
    Candidate best_candidate = candidates_arr[0];

    for (int i = 1; i < num_candidates; ++i) {
        // 優先比較完成時間
        if (candidates_arr[i].completion_time <
            best_candidate.completion_time) {
            best_candidate = candidates_arr[i];
        } else if (candidates_arr[i].completion_time ==
                   best_candidate.completion_time) {
            // 如果完成時間相同，則比較工作編號 (題目規則)
            if (candidates_arr[i].job_id < best_candidate.job_id) {
                best_candidate = candidates_arr[i];
            }
        }
    }
    return best_candidate;
}

// 應用排程決策，更新排程狀態
void apply_schedule_decision(
    const Candidate *best_candidate, // 指向最佳候選工序的指標
    int machine_available_time[MAX_MACHINES],
    int job_last_completion_time[MAX_JOBS], int current_op_idx[MAX_JOBS],
    int *scheduled_operations_done_ptr, // 指向已排程工序計數的指標
    int job_final_completion_time[MAX_JOBS],
    const int num_operations_per_job[MAX_JOBS]) {
    // 從指標解包資訊
    int min_completion_time = best_candidate->completion_time;
    int best_job_id = best_candidate->job_id;
    int best_machine_id = best_candidate->machine_k;

    // 更新機器可用時間
    machine_available_time[best_machine_id] = min_completion_time;

    // 更新工作最近完成工序的時間點
    job_last_completion_time[best_job_id] = min_completion_time;

    // 將該工作下一個待排程工序的索引推進一位
    current_op_idx[best_job_id]++;

    // 已排程工序數量增加
    (*scheduled_operations_done_ptr)++;

    // 檢查此工作是否已完成所有工序
    if (current_op_idx[best_job_id] == num_operations_per_job[best_job_id]) {
        job_final_completion_time[best_job_id] = min_completion_time;
    }
}

// 計算所有工作完成時間的總和
long long calculate_total_completion_time(
    const int job_final_completion_time[MAX_JOBS], int M) {
    long long total_sum = 0;
    for (int i = 0; i < M; ++i) {
        total_sum += job_final_completion_time[i];
    }
    return total_sum;
}

// 主排程函式
void schedule_jobs() {
    int N, M; // 機器數量 N, 工作數量 M

    // 靜態分配陣列，根據題目約束的最大值
    Operation jobs_data[MAX_JOBS][MAX_OPS_PER_JOB];
    int num_operations_per_job[MAX_JOBS];
    int total_operations_count;

    // 1. 讀取輸入
    read_input(&N, &M, jobs_data, num_operations_per_job,
               &total_operations_count);

    // 2. 初始化排程狀態
    int machine_available_time[MAX_MACHINES];
    int job_last_completion_time[MAX_JOBS];
    int current_op_idx[MAX_JOBS];
    int job_final_completion_time[MAX_JOBS];
    initialize_schedule_state(N, M, machine_available_time,
                              job_last_completion_time, current_op_idx,
                              job_final_completion_time);

    int scheduled_operations_done = 0; // 已排程工序計數

    // 3. 主排程循環
    while (scheduled_operations_done < total_operations_count) {
        // 3.1. 計算所有候選工序的最早完成時間
        Candidate candidates_arr[MAX_CANDIDATES];
        int num_current_candidates = calculate_candidates(
            M, jobs_data, num_operations_per_job, current_op_idx,
            machine_available_time, job_last_completion_time, candidates_arr);

        // 如果沒有候選工序 (理論上不應該發生，除非 total_operations_count 為 0)
        if (num_current_candidates == 0) {
            break;
        }

        // 3.2. 選擇最佳工序
        Candidate best_candidate =
            find_best_candidate(candidates_arr, num_current_candidates);

        // 3.3. 應用排程決策並更新狀態
        apply_schedule_decision(
            &best_candidate, machine_available_time, job_last_completion_time,
            current_op_idx, &scheduled_operations_done,
            job_final_completion_time, num_operations_per_job);
    }

    // 4. 計算並輸出總完成時間
    long long total_sum_completion_times =
        calculate_total_completion_time(job_final_completion_time, M);
    printf("%lld\n", total_sum_completion_times);
}

int main() {
    schedule_jobs(); // 呼叫主排程函式
    return 0;
}