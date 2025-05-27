#include <stdio.h>
#include <stdlib.h>

// 定義Node
typedef struct node_s {
        int data;
        struct node_s *next;
} node_t;

typedef node_t *nodep_t;

// 創造節點
nodep_t create(int data) {
    nodep_t newNode;
    newNode = (nodep_t)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 輸出
void printList(nodep_t p) {
    nodep_t current = p;

    while (current != NULL) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 前面加入節點
void insertFromFront(nodep_t *p, int data) {
    nodep_t newNode = create(data);
    if ((*p) == NULL) {
        (*p) = newNode;
    } else {
        newNode->next = (*p);
        (*p) = newNode;
    }
}

// 後面加入節點
void insertFromBack(nodep_t *p, int data) {
    nodep_t current;
    nodep_t newNode = create(data);

    if ((*p) == NULL) {
        (*p) = newNode;
    } else {
        current = (*p);

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int main() {
    nodep_t Node_array = NULL;
    insertFromFront(&Node_array, 5);
    insertFromFront(&Node_array, 1);
    insertFromFront(&Node_array, 2);
    insertFromFront(&Node_array, 3);
    insertFromBack(&Node_array, 4);

    printList(Node_array);

    return 0;
}