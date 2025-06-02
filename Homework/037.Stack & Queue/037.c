#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
        int data;
        struct node_s* next;
} node_t;

typedef node_t* nodep_t;

// stack 先進後出
nodep_t stack_top = NULL; // 最上面

void stack_push(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(nodep_t));
    if (new_node == NULL) return;
    new_node->data = data;
    new_node->next = stack_top;
    stack_top = new_node;
}

void stack_pop() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("%d\n", stack_top->data);
    stack_top = stack_top->next;
}

void stack_top_value() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("%d\n", stack_top->data);
}

void stack_empty() { // 全部清空
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t current = stack_top;
    nodep_t next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    stack_top = NULL;
}

void stack_print() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t current = stack_top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// queue 先進先出

void queue_push(){
	nodep_t new_node = (nodep_t)malloc(sizeof(nodep_t));
}

int main() {
    int do_times;
    scanf("%d", &do_times);

    for (int t = 0; t < do_times; t++) {
        char stack_or_queue[10];
        scanf("%s", &stack_or_queue);
        char oper[10];
        scanf("%s", &oper);

        if (strcmp(stack_or_queue, "stack") == 0) {
            // stack
            if (strcmp(oper, "push") == 0) {
                int data;
                scanf("%d", &data);
                stack_push(data);
            }
            if (strcmp(oper, "pop") == 0) {
                stack_pop();
            }
            if (strcmp(oper, "top") == 0) {
                stack_top_value();
            }
            if (strcmp(oper, "empty") == 0) {
                stack_empty();
            }
            if (strcmp(oper, "print") == 0) {
                stack_print();
            }
        } else {
            // queue
        }
    }
}