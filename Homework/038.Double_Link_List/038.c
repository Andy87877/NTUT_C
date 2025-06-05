#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
        int data;
        struct dnode_s* front;
        struct dnode_s* back;
} node_t;

typedef node_t* nodep_t;

nodep_t node_front = NULL;
nodep_t node_back = NULL;
int size = 0;

nodep_t create_node(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->front = NULL;
    new_node->back = NULL;
    return new_node;
}

// 1. addFront: 將資料放入串列前端
void addFront(int data) {
    nodep_t new_node = create_node(data);

    if (node_front == NULL) {
        node_front = new_node;
        node_back = new_node;
    } else {
        new_node->back = node_front;
        node_front->front = new_node;
        node_front = new_node;
    }
    size++;
}

void addBack(int data) {
    nodep_t new_node = create_node(data);
    if (node_front == NULL) {
        node_front = new_node;
        node_back = new_node;
    } else {
        new_node->front = node_back;
        node_back->back = new_node;
        node_back = new_node;
    }
    size++;
}

// 3. removeFront: 將最前端的節點刪除
void removeFront() {
    if (node_front == NULL) { // 串列為空
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = node_front;
    if (node_front == node_back) {
        node_front = NULL;
        node_back = NULL;
    } else {
        node_front = node_front->back;
        node_front->front = NULL;
    }
    free(temp);
    size--;
}

// 4. removeBack: 將最尾端的節點刪除
void removeBack() {
    if (node_front == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = node_back;
    if (node_front == node_back) {
        node_front = NULL;
        node_back = NULL;
    } else {
        node_back = node_back->front;
        node_back->back = NULL;
    }
    free(temp);
    size--;
}

// 5. empty: 將串列中所有節點刪除
void empty_list() {
    if (node_front == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t current = node_front;
    nodep_t next_node;
    while (current != NULL) {
        next_node = current->back;
        free(current);
        current = next_node;
    }
    node_front = NULL;
    node_back = NULL;
    size = 0;
}

// 6. insert n data: 在第n個節點後插入新的資料
void insert_node(int n, int data) {
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    if (n == size) {
        addBack(data);
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

// 7. remove n: 刪除第n個節點
void remove_node(int n) {
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    if (n == 1) {
        removeFront();
        return;
    }

    if (n == size) {
        removeBack();
        return;
    }

    nodep_t current = node_front;
    for (int i = 1; i < n; i++) {
        current = current->back;
    }

    current->front->back = current->back;
    current->back->front = current->front;

    free(current);
    size--;
}

// 8. print: 將串列中所有節點資料從前端到尾端依序輸出
void print_list() {
    if (node_front == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t current = node_front;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->back;
    }
}

int main() {
    int do_times = 0;
    size = 0;
    scanf("%d", &do_times);

    for (int t = 0; t < do_times; t++) {
        char type[20];
        getchar();
        scanf("%s", type);
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
            empty_list();
        }
        if (strcmp(type, "insert") == 0) {
            scanf("%d %d", &index, &data);
            insert_node(index, data);
        }
        if (strcmp(type, "remove") == 0) {
            scanf("%d", &index);
            remove_node(index);
        }
        if (strcmp(type, "print") == 0) {
            print_list();
        }
        // printf("times: %d, size: %d\n", t, size);
        // print_list_test();
    }
}