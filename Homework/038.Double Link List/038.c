// 038. Double Link List
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

nodep_t node_front = NULL;
nodep_t node_back = NULL;
int size = 0;

void addFront(int data) { // 往前加
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) return;

    new_node->data = data;

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
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) return;

    new_node->data = data;

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

void removeFront() { // 往前刪
    if (size == 0) {
        printf("Double link list is empty\n");
        return;
    }

    node_front = node_front->back;
    node_front->front = NULL;

    size--;
}

void removeBack() { // 往後刪
    if (size == 0) {
        printf("Double link list is empty\n");
        return;
    }

    node_back = node_back->front;
    node_back->back = NULL;

    size--;
}

void empty() { // 刪除所有節點
    if (size == 0) {
        printf("Double link list is empty\n");
        return;
    }

    nodep_t current = node_front;

    while (current != NULL) {
        nodep_t temp = current;
        free(temp);
        current = current->back;
    }
    free(current);

    node_front = NULL;
    node_back = NULL;
    size = 0;
}

void print_list() { // 輸出節點
    if (size == 0) {
        printf("Double link list is empty\n");
        return;
    }

    nodep_t current = node_front;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->back;
    }
    printf("\n\n");
}

int main() {
    int do_times;
    scanf("%d", &do_times);

    for (int t = 0; t < do_times; t++) {
        char type[10];
        scanf("%s", &type);
        int data;

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
        if (strcmp(type, "insert") == 0) {
        }
        if (strcmp(type, "remove") == 0) {
        }
        if (strcmp(type, "print") == 0) {
            print_list();
        }

        printf("size=%d\n", size);
        print_list();
    }
}