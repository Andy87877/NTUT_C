#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
        int coeff; // 係數
        int exp;   // 次方
        struct node_s *next;
} node_t;

typedef node_t *nodep_t;

nodep_t create(int coeff, int exp) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));

    new_node->coeff = coeff;
    new_node->exp = exp;
    new_node->next = NULL;
    return new_node;
}

void append_node_to_list(nodep_t *poly_head, nodep_t *poly_tail, int coeff,
                         int exp) {
    if (coeff == 0) {
        return;
    }
    nodep_t new_node = create(coeff, exp);
    if (*poly_head == NULL) {
        *poly_head = new_node;
        *poly_tail = new_node;
    } else {
        (*poly_tail)->next = new_node;
        *poly_tail = new_node;
    }
}

nodep_t read_poly() {
    char string_input[2048];
    if (fgets(string_input, sizeof(string_input), stdin) == NULL) {
        return NULL;
    }

    string_input[strcspn(string_input, "\n\r")] = 0;

    nodep_t head = NULL;
    nodep_t tail = NULL;

    int coeffs_buffer[512];
    int count = 0;

    char *token = strtok(string_input, " ");
    while (token != NULL) {
        if (strlen(token) > 0) {
            coeffs_buffer[count++] = atoi(token);
        }
        token = strtok(NULL, " ");
    }

    if (count == 0) return NULL;

    int current_exp = count - 1;

    for (int i = 0; i < count; i++) {
        append_node_to_list(&head, &tail, coeffs_buffer[i], current_exp);
        current_exp--;
    }
    return head;
}

void add_node_to_result(nodep_t *result_head, nodep_t *result_tail, int coeff,
                        int exp) {
    if (coeff == 0) return;
    nodep_t new_node = create(coeff, exp);
    if (*result_head == NULL) {
        *result_head = new_node;
        *result_tail = new_node;
    } else {
        (*result_tail)->next = new_node;
        *result_tail = new_node;
    }
}

// 加法
nodep_t add_poly(nodep_t poly1, nodep_t poly2) {
    nodep_t p1 = poly1;
    nodep_t p2 = poly2;
    nodep_t result_head = NULL;
    nodep_t result_tail = NULL;

    while (p1 != NULL || p2 != NULL) {
        if (p1 != NULL && p2 != NULL) {
            if (p1->exp > p2->exp) {
                add_node_to_result(&result_head, &result_tail, p1->coeff,
                                   p1->exp);
                p1 = p1->next;
            } else if (p2->exp > p1->exp) {
                add_node_to_result(&result_head, &result_tail, p2->coeff,
                                   p2->exp);
                p2 = p2->next;
            } else { // 相同的次方
                int sum_coeff = p1->coeff + p2->coeff;
                add_node_to_result(&result_head, &result_tail, sum_coeff,
                                   p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
        } else if (p1 != NULL) {
            add_node_to_result(&result_head, &result_tail, p1->coeff, p1->exp);
            p1 = p1->next;
        } else { // p2 != NULL
            add_node_to_result(&result_head, &result_tail, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }
    return result_head;
}

// 輸出答案
void print_poly(nodep_t poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    nodep_t current = poly;
    int is_first_node = 1; // 是第一個node
    int has_output = 0;    // 沒輸出

    while (current != NULL) {
        int coeff = current->coeff;
        int exp = current->exp;

        if (coeff == 0) {
            current = current->next;
            continue;
        }

        if (is_first_node) {
            if (coeff < 0) {
                printf("-");
            }
        } else {
            if (coeff > 0) {
                printf("+");
            } else {
                printf("-");
            }
        }

        int abs_coeff = (coeff > 0) ? coeff : -coeff;

        if (abs_coeff != 1 || exp == 0) {
            printf("%d", abs_coeff);
        }

        if (exp > 0) {
            printf("x");
            if (exp > 1) {
                printf("^%d", exp);
            }
        }

        is_first_node = 0;
        has_output = 1;
        current = current->next;
    }

    if (!has_output) {
        printf("0");
    }
    printf("\n");
}

int main() {
    nodep_t poly1 = read_poly();
    nodep_t poly2 = read_poly();

    nodep_t sum_poly = add_poly(poly1, poly2);

    print_poly(sum_poly);
}