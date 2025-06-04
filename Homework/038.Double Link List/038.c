// 038. Double Link List
//  node_front <-- 0 1 2 3 4 5 6 7 8 9 10 --> node_back
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
        int data;
        struct dnode_s* front;
        struct dnode_s* back;
} node_t;
typedef node_t* nodep_t;

//  node_front <-- 0 1 2 3 4 5 6 7 8 9 10 --> node_back

int size;
nodep_t node_front = NULL;
nodep_t node_back = NULL;

nodep_t create_node(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));

    new_node->data = data;
    new_node->front = NULL;
    new_node->back = NULL;

    return new_node;
}

void addFront(int data) { // 往前加
    nodep_t new_node = create_node(data);

    if (size == 0) {
        node_front = new_node;
        node_back = new_node;
    } else {
        new_node->back = node_front;
        node_front->front = new_node;
        node_front = new_node;
    }

    size++;
}

void addBack(int data) { // 往後加
    nodep_t new_node = create_node(data);

    if (size == 0) {
        node_front = new_node;
        node_back = new_node;
    } else {
        new_node->front = node_back;
        node_back->back = new_node;
        node_back = new_node;
    }

    size++;
}

int check_empty() { // 檢查是不是空的
    if (size == 0) {
        printf("Double link list is empty\n");
        return 1;
    }
    return 0;
}

void removeFront() { // 往前刪除
    if (check_empty()) return;

    node_front = node_front->back;
    node_front->front = NULL;

    size--;
}

void removeBack() { // 往後刪除
    if (check_empty()) return;

    node_back = node_back->front;
    node_back->back = NULL;

    size--;
}

void empty() {
    if (check_empty()) return;

    node_front = NULL;
    node_back = NULL;
    size = 0;
}

void insert_node(int data, int n) {
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    nodep_t current = node_front;
    for (int i = 1; i < n; i++) {
        current = current->back;
    }

    nodep_t new_node = create_node(data);

    new_node->back = current->back;
    new_node->front = current;

    current->back->front = new_node;
    current->back = new_node;

    size++;
}

void remove_node(int n) {
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    nodep_t current = node_front;
    for (int i = 1; i < n; i++) {
        current = current->back;
    }

    current->front->back = current->back;
    current->back->front = current->front;

    size--;
}

void print_list() {
    if (check_empty()) return;
    nodep_t current = node_front;

    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->back;
    }
}

//  node_front <-- 0 1 2 3 4 5 6 7 8 9 10 --> node_back

int main() {
    int do_times = 0;
    size = 0;
    scanf("%d", &do_times);

    for (int t = 0; t < do_times; t++) {
        char type[20];
        getchar();
        scanf("%s", &type);
        int data, index;

        if (strcmp(type, "addFront") == 0) {
            scanf("%d", &data);
            addFront(data);
        }
        if (strcmp(type, "addBack") == 0) {
            scanf("%d", &data);
            addBack(data);
        }
        if (strcmp(type, "removeFront") == 0) {
            removeFront();
        }
        if (strcmp(type, "removeBack") == 0) {
            removeBack();
        }
        if (strcmp(type, "empty") == 0) {
            empty();
        }
        if (strcmp(type, "insert") == 0) {
            scanf("%d %d", &data, &index);
            insert_node(data, index);
        }
        if (strcmp(type, "remove") == 0) {
            scanf("%d", &index);
            remove_node(index);
        }
        if (strcmp(type, "print") == 0) {
            print_list();
        }
    }
}