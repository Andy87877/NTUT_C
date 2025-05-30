#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
        int number; // 數字
        int exp;    // 次方
        struct node_s *next;
} node_t;

typedef node_t *nodep_t;

// newNOde
nodep_t newNode(int number, int exp) {
    nodep_t new_node = (nodep_t)malloc(sizeof(nodep_t));

    new_node->number = number;
    new_node->exp = exp;
    new_node->next = NULL;
    return new_node;
}

// 讀取方程式
nodep_t read_poly() {
    char input_line[1000];
    fgets(input_line, 1000, stdin);

    input_line[strcspn(input_line, "\n\r")] = 0;

    nodep_t head = NULL;
    nodep_t tail = NULL;

    int number_array[1000];
    int index;

    // 讀取數字
    char *token = strtok(input_line, " ");
    while (token != NULL) {
        if (strlen(token) > 0) {
            int now_number = atoi(token);
            number_array[index++] = now_number;
        }

        // token = str
    }
}

int main() {
    nodep_t poly_1 = read_poly();
    nodep_t poly_2 = read_poly();

    nodep_t answer_poly = add_poly(poly_1, poly_2);

    printf(answer_poly);
}