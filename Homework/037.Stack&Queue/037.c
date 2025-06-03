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

nodep_t queue_front = NULL; // 前面 (最先放和拿)
nodep_t queue_back = NULL;  // 後面

void queue_push(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(nodep_t));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = NULL;

    if (queue_back == NULL) { // 空的
        queue_front = new_node;
        queue_back = new_node;
    } else {
        queue_back->next = new_node;
        queue_back = new_node;
    }
}

void queue_pop() {
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", queue_front->data);
    queue_front = queue_front->next;

    if (queue_front == NULL) { // 變空的了
        queue_back = NULL;
    }
}

void queue_front_value() {
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", queue_front->data);
}

void queue_empty() { // queue清空
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t current = queue_front;
    nodep_t next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    queue_front = NULL;
    queue_back = NULL;
}

void queue_print() {
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t current = queue_front;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// main
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
            if (strcmp(oper, "push") == 0) {
                int data;
                scanf("%d", &data);
                queue_push(data);
            }
            if (strcmp(oper, "pop") == 0) {
                queue_pop();
            }
            if (strcmp(oper, "front") == 0) {
                queue_front_value();
            }
            if (strcmp(oper, "empty") == 0) {
                queue_empty();
            }
            if (strcmp(oper, "print") == 0) {
                queue_print();
            }
        }
    }
}