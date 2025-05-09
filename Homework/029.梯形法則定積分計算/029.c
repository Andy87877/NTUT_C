#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double f1_eval(double x, double a) {
    double val_inside_sqrt = a - x * x;
    if (val_inside_sqrt < 0) {
        if (fabs(val_inside_sqrt) <
            1e-12) {
            val_inside_sqrt = 0.0;
        } else {
            return NAN;
        }
    }
    return sqrt(val_inside_sqrt);
}

double f2_eval(double x, double a) {
    double term_a_plus_x = a + x;
    if (term_a_plus_x < 0) {
        if (fabs(term_a_plus_x) <
            1e-12) { 
            term_a_plus_x = 0.0;
        } else {
            return NAN;
        }
    }

    if (term_a_plus_x == 0) {
        return NAN;
    }

    double denominator = sqrt(term_a_plus_x);
    if (denominator == 0) {
        return NAN;
    }

    return (a * pow(x, 3) + 7 * x) / denominator;
}

double calculate_trapezoid_for_n(int n, double p_limit, double q_limit,
                                 double a_coeff,
                                 double (*func_to_integrate)(double, double)) {
    double h = (q_limit - p_limit) / n;
    double sum_fx = 0;

    double f_at_p = func_to_integrate(p_limit, a_coeff);
    double f_at_q = func_to_integrate(q_limit, a_coeff);

    if (isnan(f_at_p) || isnan(f_at_q)) {
        return NAN;
    }

    sum_fx = f_at_p + f_at_q; 

    for (int i = 1; i < n; i++) {
        double xi = p_limit + i * h;
        double f_at_xi = func_to_integrate(xi, a_coeff);

        if (isnan(f_at_xi)) {
            return NAN; 
        }
        sum_fx += (2.0 * f_at_xi);
    }

    return sum_fx * (h / 2.0);
}

void judge(int mode) {
    int a_param_int, p_param_int, q_param_int, err_decimal_places;
    scanf("%d %d %d %d", &a_param_int, &p_param_int, &q_param_int,
          &err_decimal_places);

    double a_coeff_double =
        (double)a_param_int; 
    double p_limit_double = (double)p_param_int; 
    double q_limit_double = (double)q_param_int; 

    double (*selected_function)(double, double);
    if (mode == 1) {
        selected_function = f1_eval;
    } else { 
        selected_function = f2_eval;
    }

    int iteration_count = 0;
    int n_slices = 1; 
    double T_old_approx, T_new_approx;

    double tolerance = pow(10, -err_decimal_places);

    if (err_decimal_places <= 0)
        tolerance = 1e-15; 
    if (tolerance < 1e-15)
        tolerance =
            1e-15;

    T_old_approx =
        calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                  a_coeff_double, selected_function);

    if (isnan(T_old_approx)) {
        printf("%.12f\n", NAN); 
        fflush(stdout);
        return;
    }

    while (iteration_count < 100) { 
        iteration_count++;
        n_slices *= 2; 

        T_new_approx =
            calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                      a_coeff_double, selected_function);

        if (isnan(T_new_approx)) {
            T_old_approx = T_new_approx;
            break;
        }

        if (fabs(T_new_approx - T_old_approx) < tolerance) {
            T_old_approx = T_new_approx; 
            break;                       
        }

        T_old_approx = T_new_approx; 
    }

    printf("%.12f\n", T_old_approx);
    fflush(stdout); 
}

int main() {
    int mode_selection;

    while (1) {
        if (scanf("%d", &mode_selection) != 1) {
            return 1; 
        }

        if (mode_selection == 0) {
            break; 
        }

        if (mode_selection != 1 && mode_selection != 2) {
            printf("Invalid\n");
            fflush(stdout);
            char consume_char;
            while ((consume_char = getchar()) != '\n' && consume_char != EOF);
            continue; 
        }

        judge(mode_selection);
    }

    return 0;
}