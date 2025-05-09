#include <math.h>
#include <stdio.h>
#include <stdlib.h> // C99 及更高版本中定義 NAN 所需

// 假設 'x' 應為 double 型別，用於標準數值積分。
// 如果嚴格設定 'int x'，其行為將會非常不同，
// 且可能不符合典型的積分值。

// 修正後的函數定義，假設 x 應為 double
double f1_eval(double x, double a) {
    double val_inside_sqrt = a - x * x;
    // 處理因浮點運算導致 val_inside_sqrt 極度接近 0 的情況
    if (val_inside_sqrt < 0) {
        if (fabs(val_inside_sqrt) <
            1e-12) { // 判斷是否有效為零的容差
            val_inside_sqrt = 0.0;
        } else {
            return NAN; // 確實為負，平方根不是實數
        }
    }
    return sqrt(val_inside_sqrt);
}

double f2_eval(double x, double a) {
    double term_a_plus_x = a + x;
    // 處理平方根定義域的情況
    if (term_a_plus_x < 0) {
        if (fabs(term_a_plus_x) <
            1e-12) { // 判斷是否有效為零的容差
            term_a_plus_x = 0.0;
        } else {
            return NAN; // 確實為負，平方根不是實數
        }
    }

    // 如果 term_a_plus_x 為零，處理除以零的情況
    if (term_a_plus_x == 0) {
        // 分子：a * x^3 + 7x。如果 x=0 且 a=0，分子=0。0/0 是 NaN。
        // 如果 x!=0 且 a=-x，分子 = -x*x^3 + 7x = -x^4+7x。如果非零，則為無窮大(Inf)。
        // 為了積分的簡潔性和安全性，對於除以零的情況返回 NaN。
        return NAN;
    }

    double denominator = sqrt(term_a_plus_x);
    // 如果 term_a_plus_x == 0 的情況已處理，此檢查有些多餘，
    // 但明確檢查分母是否為零更為穩健。
    if (denominator == 0) {
        return NAN;
    }

    return (a * pow(x, 3) + 7 * x) / denominator;
}

// 輔助函數，用於計算給定 n 的梯形和
// 它使用一個函數指針指向 f1_eval 或 f2_eval。
double calculate_trapezoid_for_n(int n, double p_limit, double q_limit,
                                 double a_coeff,
                                 double (*func_to_integrate)(double, double)) {
    double h = (q_limit - p_limit) / n;
    double sum_fx = 0;

    // 在端點 p 和 q 處計算函數值
    double f_at_p = func_to_integrate(p_limit, a_coeff);
    double f_at_q = func_to_integrate(q_limit, a_coeff);

    // 如果端點值為 NaN，則此範圍內的積分很可能是未定義的或有問題的
    if (isnan(f_at_p) || isnan(f_at_q)) {
        return NAN;
    }

    sum_fx = f_at_p + f_at_q; // 從 f(x_0) + f(x_n) 開始

    // 對中間項求和：2 * (f(x_1) + f(x_2) + ... + f(x_{n-1}))
    for (int i = 1; i < n; i++) {
        double xi = p_limit + i * h;
        double f_at_xi = func_to_integrate(xi, a_coeff);

        if (isnan(f_at_xi)) {
            return NAN; // 如果任何中間點的值是 NaN，則結果為 NaN
        }
        sum_fx += (2.0 * f_at_xi);
    }

    return sum_fx * (h / 2.0);
}

void judge(int mode) {
    int a_param_int, p_param_int, q_param_int, err_decimal_places;
    // 輸入參數：a (係數)，p (積分下限)，q (積分上限)，err (精度要求的小數位數)
    scanf("%d %d %d %d", &a_param_int, &p_param_int, &q_param_int,
          &err_decimal_places);

    double a_coeff_double =
        (double)a_param_int; // 'a' 在函數中是 double 型別的係數
    double p_limit_double = (double)p_param_int; // 積分下限 p
    double q_limit_double = (double)q_param_int; // 積分上限 q

    // 根據模式選擇要積分的函數
    double (*selected_function)(double, double);
    if (mode == 1) {
        selected_function = f1_eval;
    } else { // mode == 2
        selected_function = f2_eval;
    }

    int iteration_count = 0;
    int n_slices = 1; // 從 n=1 個子區間開始
    double T_old_approx, T_new_approx;

    // 收斂容差：10^(-err_decimal_places)
    double tolerance = pow(10, -err_decimal_places);
    // 確保容差是一個小的正數，例如，如果 err_decimal_places 是 0 或負數。
    if (err_decimal_places <= 0)
        tolerance = 1e-15; // 預設為高精度
    if (tolerance < 1e-15)
        tolerance =
            1e-15; // 為確保 double 精度穩定性，將容差的最小值限制在 1e-15

    // 計算初始近似值 T_old (對應 n=1)
    T_old_approx =
        calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                  a_coeff_double, selected_function);

    if (isnan(T_old_approx)) {
        printf("%.12f\n", NAN); // 或者按規定輸出某些錯誤訊息
        fflush(stdout);
        return;
    }

    // 迴圈進行近似值細化，直到收斂或達到最大迭代次數
    while (iteration_count < 100) { // 最多 100 次細化迭代
        iteration_count++;
        n_slices *= 2; // 將子區間數量加倍

        T_new_approx =
            calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                      a_coeff_double, selected_function);

        if (isnan(T_new_approx)) {
            // 如果新的計算結果為 NaN，先前的 T_old_approx 可能是最佳值，
            // 或者表示出現問題。對於此問題，我們將輸出 NaN。
            T_old_approx = T_new_approx; // 這樣就會打印 NaN
            break;
        }

        // 檢查是否收斂
        if (fabs(T_new_approx - T_old_approx) < tolerance) {
            T_old_approx = T_new_approx; // 更新到最新的近似值
            break;                       // 已收斂
        }

        T_old_approx = T_new_approx; // 為下一次迭代更新 T_old
    }

    // 輸出最終結果
    printf("%.12f\n", T_old_approx);
    fflush(stdout); // 確保輸出緩衝區已刷新
}

int main() {
    int mode_selection;

    while (1) {
        if (scanf("%d", &mode_selection) != 1) {
            // 處理讀取輸入時的潛在錯誤，例如 EOF 或非整數輸入
            return 1; // 以錯誤碼退出
        }

        if (mode_selection == 0) {
            break; // 終止程式
        }

        if (mode_selection != 1 && mode_selection != 2) {
            printf("Invalid\n");
            fflush(stdout);
            // 消耗掉無效輸入行的剩餘部分
            char consume_char;
            while ((consume_char = getchar()) != '\n' && consume_char != EOF);
            continue; // 再次提示輸入模式
        }

        // 已選擇有效模式 (1 或 2)
        judge(mode_selection);
    }

    return 0;
}