#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For strcmp

// 結構定義 (題目提供)
typedef struct node_s {
        int data;
        struct node_s* next;
} node_t;
typedef node_t* nodep_t;

// Stack 全域指標
nodep_t stack_top = NULL;

// Queue 全域指標
nodep_t queue_front = NULL;
nodep_t queue_rear = NULL;

// --- Stack 相關函數 ---

void stack_push(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) {
        // 記憶體分配失敗處理
        return;
    }
    new_node->data = data;
    new_node->next = stack_top; // 新節點指向舊的頂部
    stack_top = new_node;       // 新節點成為新的頂部
}

void stack_pop() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t temp = stack_top;    // 暫存要刪除的節點
    printf("%d\n", temp->data);  // 輸出頂端資料
    stack_top = stack_top->next; // 頂部下移
    free(temp);                  // 釋放記憶體
}

void stack_top_val() { // 避免與 stack_top 變數名衝突
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("%d\n", stack_top->data); // 輸出頂端資料
}

void stack_empty() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    nodep_t current = stack_top;
    nodep_t next_node;
    while (current != NULL) {
        next_node = current->next; // 暫存下一個節點
        free(current);             // 釋放當前節點
        current = next_node;       // 移動到下一個節點
    }
    stack_top = NULL; // 清空後，將頂部指標設為NULL
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

// --- Queue 相關函數 ---

void queue_push(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) {
        // 記憶體分配失敗處理
        return;
    }
    new_node->data = data;
    new_node->next = NULL; // 新節點總是成為尾巴，所以next指向NULL

    if (queue_rear == NULL) { // 佇列是空的
        queue_front = new_node;
        queue_rear = new_node;
    } else {
        queue_rear->next = new_node; // 舊尾巴指向新節點
        queue_rear = new_node;       // 新節點成為新尾巴
    }
}

void queue_pop() {
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    nodep_t temp = queue_front;      // 暫存要刪除的節點
    printf("%d\n", temp->data);      // 輸出前端資料
    queue_front = queue_front->next; // 前端下移

    // 如果移除後佇列變空了，要將 rear 也設為 NULL
    if (queue_front == NULL) {
        queue_rear = NULL;
    }
    free(temp); // 釋放記憶體
}

void queue_front_val() { // 避免與 queue_front 變數名衝突
    if (queue_front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", queue_front->data); // 輸出前端資料
}

void queue_empty() {
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
    queue_front = NULL; // 清空後，將前後指標設為NULL
    queue_rear = NULL;
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

// --- 主程式 ---

int main() {
    int N;
    scanf("%d", &N);

    char type_str[10];      // "stack" or "queue"
    char operation_str[10]; // "push", "pop", etc.
    int data;

    for (int i = 0; i < N; i++) {
        scanf("%s %s", type_str, operation_str);

        if (strcmp(type_str, "stack") == 0) {
            if (strcmp(operation_str, "push") == 0) {
                scanf("%d", &data);
                stack_push(data);
            } else if (strcmp(operation_str, "pop") == 0) {
                stack_pop();
            } else if (strcmp(operation_str, "top") == 0) {
                stack_top_val();
            } else if (strcmp(operation_str, "empty") == 0) {
                stack_empty();
            } else if (strcmp(operation_str, "print") == 0) {
                stack_print();
            }
        } else if (strcmp(type_str, "queue") == 0) {
            if (strcmp(operation_str, "push") == 0) {
                scanf("%d", &data);
                queue_push(data);
            } else if (strcmp(operation_str, "pop") == 0) {
                queue_pop();
            } else if (strcmp(operation_str, "front") == 0) {
                queue_front_val();
            } else if (strcmp(operation_str, "empty") == 0) {
                queue_empty();
            } else if (strcmp(operation_str, "print") == 0) {
                queue_print();
            }
        }
    }

    // 程式結束前，清理殘留的記憶體 (如果有的話，雖然理論上 empty 操作會清空)
    stack_empty(); // 再次確保所有 stack 記憶體被釋放
    queue_empty(); // 再次確保所有 queue 記憶體被釋放

    return 0;
}