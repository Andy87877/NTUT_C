#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strtok
// #include <ctype.h> // Not strictly needed with " \n\r\t" in strtok

// Node structure for a term in the polynomial
typedef struct Term {
    int coeff;      // Coefficient
    int exp;        // Exponent
    struct Term *next;
} Term;

// Function to create a new term node
Term* create_term_node(int coeff, int exp) {
    Term *new_term = (Term*)malloc(sizeof(Term));
    if (!new_term) {
        // In a real application, handle memory allocation failure more gracefully
        // For competitive programming, often exit is acceptable.
        perror("Failed to allocate memory for term");
        exit(EXIT_FAILURE);
    }
    new_term->coeff = coeff;
    new_term->exp = exp;
    new_term->next = NULL;
    return new_term;
}

// Appends a term to the end of the polynomial list
// Used when creating polynomial from input.
void append_term_to_list(Term **poly_head, Term **poly_tail, int coeff, int exp) {
    if (coeff == 0) { // Don't store terms with zero coefficient from initial input
        return;
    }
    Term *new_term = create_term_node(coeff, exp);
    if (*poly_head == NULL) {
        *poly_head = new_term;
        *poly_tail = new_term;
    } else {
        (*poly_tail)->next = new_term;
        *poly_tail = new_term;
    }
}

// Reads a line of input and creates a polynomial linked list
Term* read_polynomial() {
    char line[2048]; // Increased buffer size for potentially long lines
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return NULL; // EOF or error
    }

    // Remove trailing newline if present, to prevent empty token if line ends with space then newline
    line[strcspn(line, "\n\r")] = 0;


    Term *head = NULL;
    Term *tail = NULL;

    // Using a temporary array to store coefficients before knowing the highest power
    int coeffs_buffer[512]; // Max number of terms expected in input line
    int count = 0;

    char *token = strtok(line, " "); // Delimiters: space. Newline handled above.
    while (token != NULL) {
        // Skip empty tokens if multiple spaces are used
        if (strlen(token) > 0) { // Basic check, or check if token is purely whitespace
             if (count < 512) {
                coeffs_buffer[count++] = atoi(token);
            } else {
                // Handle too many terms if necessary, for now assume it fits
            }
        }
        token = strtok(NULL, " ");
    }

    if (count == 0) return NULL; // Empty line or line with only spaces

    int current_exp = count - 1;
    for (int i = 0; i < count; i++) {
        append_term_to_list(&head, &tail, coeffs_buffer[i], current_exp);
        current_exp--;
    }
    return head;
}

// Helper for add_polynomials to append to the result list
void add_term_to_result(Term **result_head, Term **result_tail, int coeff, int exp) {
    if (coeff == 0) return; // CRITICAL: Do not add terms with zero coefficient to the sum

    Term *new_term = create_term_node(coeff, exp);
    if (*result_head == NULL) {
        *result_head = new_term;
        *result_tail = new_term;
    } else {
        (*result_tail)->next = new_term;
        *result_tail = new_term;
    }
}

// Adds two polynomials and returns a new polynomial representing their sum
Term* add_polynomials(Term *poly1, Term *poly2) {
    Term *p1 = poly1;
    Term *p2 = poly2;
    Term *result_head = NULL;
    Term *result_tail = NULL;

    while (p1 != NULL || p2 != NULL) {
        if (p1 != NULL && p2 != NULL) {
            if (p1->exp > p2->exp) {
                add_term_to_result(&result_head, &result_tail, p1->coeff, p1->exp);
                p1 = p1->next;
            } else if (p2->exp > p1->exp) {
                add_term_to_result(&result_head, &result_tail, p2->coeff, p2->exp);
                p2 = p2->next;
            } else { // p1->exp == p2->exp
                int sum_coeff = p1->coeff + p2->coeff;
                add_term_to_result(&result_head, &result_tail, sum_coeff, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
        } else if (p1 != NULL) {
            add_term_to_result(&result_head, &result_tail, p1->coeff, p1->exp);
            p1 = p1->next;
        } else { // p2 != NULL
            add_term_to_result(&result_head, &result_tail, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }
    return result_head;
}

// Prints the polynomial according to the specified format
void print_polynomial(Term *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    Term *current = poly;
    int is_first_term = 1;

    while (current != NULL) {
        int coeff = current->coeff;
        int exp = current->exp;

        // Print sign
        if (is_first_term) {
            if (coeff < 0) {
                printf("-");
            }
            // No '+' for the very first positive term
        } else { // Not the first term
            if (coeff > 0) {
                printf("+");
            } else { // coeff < 0
                printf("-");
            }
        }

        int abs_coeff = (coeff > 0) ? coeff : -coeff;

        // Print coefficient value (unless it's 1/-1 and not a constant term)
        if (abs_coeff != 1 || exp == 0) {
            printf("%d", abs_coeff);
        } else {
            // If abs_coeff is 1 and exp > 0, coefficient '1' is implicit.
            // Example: x^2 (coeff 1), -x^2 (coeff -1).
            // If it's the first term like "x^2", nothing is printed here for the coeff.
            // If it's "-x^2", '-' was printed.
            // This logic is correct.
        }

        // Print 'x' and exponent part
        if (exp > 0) {
            printf("x");
            if (exp > 1) {
                printf("^%d", exp);
            }
        }
        // If exp is 0, only the coefficient is printed (constant term), handled above.

        is_first_term = 0;
        current = current->next;
    }
    
    // This case should ideally be caught by poly == NULL at the start.
    // If poly was not NULL, but all its terms were 0 (which append/add_term_to_result prevents),
    // then is_first_term would remain 1.
    if (is_first_term) { 
        // This means the list was empty to begin with, or became empty
        // which shouldn't happen if poly was non-NULL unless print_polynomial
        // itself was filtering out zero-coefficient terms (which it isn't).
        // The primary check `if (poly == NULL)` covers the case where the result is 0.
        // This secondary check is more of a safeguard if print_polynomial was ever
        // called with a list that contained only zero-coefficient terms (which our design avoids).
        // For this problem, given current design, it's unlikely to be hit if poly wasn't initially NULL.
        // Let's ensure `0` is printed if poly was non-NULL but resulted in no output (e.g. input poly had only a 0 coeff term).
        // However, `append_term_to_list` filters 0-coeff terms from input,
        // and `add_term_to_result` filters 0-coeff terms from sum.
        // So `poly` passed to `print_polynomial` will not contain 0-coeff terms.
        // The only way `is_first_term` remains true is if `poly` was NULL initially.
    }

    printf("\n");
}

// Frees the memory used by a polynomial linked list
void free_polynomial(Term *poly) {
    Term *current = poly;
    Term *next_term;
    while (current != NULL) {
        next_term = current->next;
        free(current);
        current = next_term;
    }
}

int main() {
    Term *poly1 = read_polynomial();
    Term *poly2 = read_polynomial();

    Term *sum_poly = add_polynomials(poly1, poly2);

    print_polynomial(sum_poly);

    free_polynomial(poly1);
    free_polynomial(poly2);
    free_polynomial(sum_poly);

    return 0;
}