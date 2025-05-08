#include <math.h>
#include <stdio.h>
#include <stdlib.h> // Required for NAN, defined in C99 and later

// It's assumed that 'x' should be a double for standard numerical integration.
// If 'int x' was strictly intended, the behavior would be very different and
// likely not match typical integral values.

// Corrected function definitions assuming x should be double
double f1_eval(double x, double a) {
    double val_inside_sqrt = a - x * x;
    // Handle cases where val_inside_sqrt is extremely close to 0 due to
    // floating point arithmetic
    if (val_inside_sqrt < 0) {
        if (fabs(val_inside_sqrt) <
            1e-12) { // Tolerance for being effectively zero
            val_inside_sqrt = 0.0;
        } else {
            return NAN; // Truly negative, sqrt is not a real number
        }
    }
    return sqrt(val_inside_sqrt);
}

double f2_eval(double x, double a) {
    double term_a_plus_x = a + x;
    // Handle cases for sqrt domain
    if (term_a_plus_x < 0) {
        if (fabs(term_a_plus_x) <
            1e-12) { // Tolerance for being effectively zero
            term_a_plus_x = 0.0;
        } else {
            return NAN; // Truly negative, sqrt is not a real number
        }
    }

    // Handle division by zero if term_a_plus_x is zero
    if (term_a_plus_x == 0) {
        // Numerator: a * x^3 + 7x. If x=0 and a=0, num=0. 0/0 is NaN.
        // If x!=0 and a=-x, num = -x*x^3 + 7x = -x^4+7x. If non-zero, then Inf.
        // For simplicity and safety in integration, return NaN for division by
        // zero.
        return NAN;
    }

    double denominator = sqrt(term_a_plus_x);
    // This check is somewhat redundant if term_a_plus_x == 0 is already
    // handled, but explicit check for denominator being zero is robust.
    if (denominator == 0) {
        return NAN;
    }

    return (a * pow(x, 3) + 7 * x) / denominator;
}

// Helper function to calculate the trapezoidal sum for a given n
// It uses a function pointer for f1_eval or f2_eval.
double calculate_trapezoid_for_n(int n, double p_limit, double q_limit,
                                 double a_coeff,
                                 double (*func_to_integrate)(double, double)) {
    double h = (q_limit - p_limit) / n;
    double sum_fx = 0;

    // Evaluate function at the endpoints p and q
    double f_at_p = func_to_integrate(p_limit, a_coeff);
    double f_at_q = func_to_integrate(q_limit, a_coeff);

    // If endpoints are NaN, the integral over this range is likely undefined or
    // problematic
    if (isnan(f_at_p) || isnan(f_at_q)) {
        return NAN;
    }

    sum_fx = f_at_p + f_at_q; // Start with f(x_0) + f(x_n)

    // Sum intermediate terms: 2 * (f(x_1) + f(x_2) + ... + f(x_{n-1}))
    for (int i = 1; i < n; i++) {
        double xi = p_limit + i * h;
        double f_at_xi = func_to_integrate(xi, a_coeff);

        if (isnan(f_at_xi)) {
            return NAN; // If any intermediate point is NaN, result is NaN
        }
        sum_fx += (2.0 * f_at_xi);
    }

    return sum_fx * (h / 2.0);
}

void judge(int mode) {
    int a_param_int, p_param_int, q_param_int, err_decimal_places;
    // Input parameters: a (coefficient), p (start), q (end), err (precision)
    scanf("%d %d %d %d", &a_param_int, &p_param_int, &q_param_int,
          &err_decimal_places);

    double a_coeff_double =
        (double)a_param_int; // 'a' is a double coefficient in functions
    double p_limit_double = (double)p_param_int; // Integral limits p
    double q_limit_double = (double)q_param_int; // Integral limits q

    // Select the function to integrate based on mode
    double (*selected_function)(double, double);
    if (mode == 1) {
        selected_function = f1_eval;
    } else { // mode == 2
        selected_function = f2_eval;
    }

    int iteration_count = 0;
    int n_slices = 1; // Start with n=1 subinterval
    double T_old_approx, T_new_approx;

    // Tolerance for convergence: 10^(-err_decimal_places)
    double tolerance = pow(10, -err_decimal_places);
    // Ensure tolerance is a small positive number, e.g. if err_decimal_places
    // is 0 or negative.
    if (err_decimal_places <= 0)
        tolerance = 1e-15; // Default to a high precision
    if (tolerance < 1e-15)
        tolerance =
            1e-15; // Cap minimum tolerance for double precision stability

    // Calculate initial approximation T_old (for n=1)
    T_old_approx =
        calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                  a_coeff_double, selected_function);

    if (isnan(T_old_approx)) {
        printf("%.12f\n", NAN); // Or some error message if specified
        fflush(stdout);
        return;
    }

    // Loop to refine approximation until convergence or max iterations
    while (iteration_count < 100) { // Max 100 refinement iterations
        iteration_count++;
        n_slices *= 2; // Double the number of subintervals

        T_new_approx =
            calculate_trapezoid_for_n(n_slices, p_limit_double, q_limit_double,
                                      a_coeff_double, selected_function);

        if (isnan(T_new_approx)) {
            // If new calculation results in NaN, the previous T_old_approx
            // might be the best, or it indicates an issue. For this problem,
            // we'll output the NaN.
            T_old_approx = T_new_approx; // So that NaN is printed
            break;
        }

        // Check for convergence
        if (fabs(T_new_approx - T_old_approx) < tolerance) {
            T_old_approx = T_new_approx; // Update to the latest approximation
            break;                       // Converged
        }

        T_old_approx = T_new_approx; // Update T_old for the next iteration
    }

    // Output the final result
    printf("%.12f\n", T_old_approx);
    fflush(stdout); // Ensure output is flushed
}

int main() {
    int mode_selection;

    while (1) {
        if (scanf("%d", &mode_selection) != 1) {
            // Handle potential error in reading input, e.g., EOF or non-integer
            // input
            return 1; // Exit with an error code
        }

        if (mode_selection == 0) {
            break; // Terminate program
        }

        if (mode_selection != 1 && mode_selection != 2) {
            printf("Invalid\n");
            fflush(stdout);
            // Consume the rest of the invalid input line
            char consume_char;
            while ((consume_char = getchar()) != '\n' && consume_char != EOF);
            continue; // Prompt for mode again
        }

        // Valid mode (1 or 2) selected
        judge(mode_selection);
    }

    return 0;
}