#include <stdio.h>
#include <stdlib.h> // For malloc, free, exit
#include <string.h> // For strcmp

// 雙向鍊結串列節點結構
typedef struct dnode_s {
        int data;
        struct dnode_s* front; // 指向前一個節點 (previous)
        struct dnode_s* back;  // 指向後一個節點 (next)
} node_t;

typedef node_t* nodep_t; // 節點指標的別名

// 全域變數，用於管理雙向鍊結串列的頭尾和大小
nodep_t node_front = NULL; // 串列頭部 (相當於 head)
nodep_t node_back = NULL;  // 串列尾部 (相當於 tail)
int size = 0;              // 串列當前節點數量

// 輔助函數：建立一個新的節點
nodep_t create_node(int data) {
    nodep_t new_node =
        (nodep_t)malloc(sizeof(node_t)); // 修正這裡！sizeof(node_t)
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE); // 終止程式
    }
    new_node->data = data;
    new_node->front = NULL;
    new_node->back = NULL;
    return new_node;
}

// 1. addFront: 將資料放入串列前端
void addFront(int data) {
    nodep_t new_node = create_node(data); // 使用輔助函數建立節點

    if (node_front == NULL) { // 串列為空
        node_front = new_node;
        node_back = new_node; // 第一個節點，同時是頭也是尾
    } else {
        new_node->back = node_front;  // 新節點的back指向原來的node_front
        node_front->front = new_node; // 原來node_front的front指向新節點
        node_front = new_node;        // 更新node_front為新節點
    }
    size++;
    // 題目要求不輸出，所以移除你原來的 printf
}

// 2. addBack: 將資料放入串列尾端
void addBack(int data) {
    nodep_t new_node = create_node(data);
    if (node_front == NULL) { // 串列為空
        node_front = new_node;
        node_back = new_node;
    } else {
        new_node->front = node_back; // 新節點的front指向原來的node_back
        node_back->back = new_node;  // 原來node_back的back指向新節點
        node_back = new_node;        // 更新node_back為新節點
    }
    size++;
}

// 3. removeFront: 將最前端的節點刪除
void removeFront() {
    if (node_front == NULL) { // 串列為空
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = node_front;     // 暫存要刪除的節點
    if (node_front == node_back) { // 串列中只有一個節點
        node_front = NULL;
        node_back = NULL;
    } else {
        node_front = node_front->back; // node_front指向下一個節點
        node_front->front = NULL;      // 新node_front的front設為NULL
    }
    free(temp); // 釋放記憶體
    size--;
}

// 4. removeBack: 將最尾端的節點刪除
void removeBack() {
    if (node_front == NULL) { // 串列為空
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = node_back;      // 暫存要刪除的節點
    if (node_front == node_back) { // 串列中只有一個節點
        node_front = NULL;
        node_back = NULL;
    } else {
        node_back = node_back->front; // node_back指向前一個節點
        node_back->back = NULL;       // 新node_back的back設為NULL
    }
    free(temp); // 釋放記憶體
    size--;
}

// 5. empty: 將串列中所有節點刪除
void empty_list() {           // 函數名避免與可能存在的標準庫函數衝突
    if (node_front == NULL) { // 串列為空
        printf("Double link list is empty\n");
        return;
    }
    nodep_t current = node_front;
    nodep_t next_node;
    while (current != NULL) {
        next_node = current->back; // 儲存下一個節點的地址
        free(current);             // 釋放當前節點
        current = next_node;       // 移動到下一個節點
    }
    node_front = NULL; // 重置node_front
    node_back = NULL;  // 重置node_back
    size = 0;          // 重置大小
}

// 6. insert n data: 在第n個節點後插入新的資料
void insert_node(int n, int data) {
    // 檢查n的有效性。n必須在 [1, size] 之間
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    // 特殊情況：在最後一個節點後插入 (即n等於串列長度)
    // 這等同於addBack操作
    if (n == size) {
        addBack(data);
        return;
    }

    // 找到第n個節點
    nodep_t current = node_front;
    for (int i = 1; i < n; i++) {
        current = current->back;
    }
    // current 現在指向第n個節點

    // 建立新節點
    nodep_t new_node = create_node(data);

    // 重新連結節點：將new_node插入到 current 和 current->back 之間
    new_node->back = current->back; // 新節點的back指向current的原後繼節點
    new_node->front = current;      // 新節點的front指向current

    current->back->front = new_node; // current的原後繼節點的front現在指向新節點
    current->back = new_node;        // current的back現在指向新節點

    size++;
}

// 7. remove n: 刪除第n個節點
void remove_node(int n) {
    // 檢查n的有效性。n必須在 [1, size] 之間
    if (n < 1 || n > size) {
        printf("Invalid command\n");
        return;
    }

    // 特殊情況：刪除第一個節點
    if (n == 1) {
        removeFront();
        return;
    }
    // 特殊情況：刪除最後一個節點
    if (n == size) {
        removeBack();
        return;
    }

    // 找到第n個節點
    nodep_t current = node_front;
    for (int i = 1; i < n; i++) {
        current = current->back;
    }
    // current 現在指向要刪除的第n個節點

    // 重新連結節點：將current從串列中移除
    current->front->back =
        current->back; // current前一個節點的back指向current後一個節點
    current->back->front =
        current->front; // current後一個節點的front指向current前一個節點

    free(current); // 釋放記憶體
    size--;
}

// 8. print: 將串列中所有節點資料從前端到尾端依序輸出
void print_list() {
    if (node_front == NULL) { // 串列為空
        printf("Double link list is empty\n");
        return;
    }
    nodep_t current = node_front;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->back; // 移動到下一個節點
    }
}

int main() {
    int N;
    scanf("%d", &N); // 讀取操作次數N

    char command[20]; // 用於儲存操作指令字串
    int data;         // 用於add/insert操作的資料
    int n;            // 用於insert/remove操作的位置

    for (int i = 0; i < N; i++) {
        scanf("%s", command); // 讀取指令

        if (strcmp(command, "addFront") == 0) {
            scanf("%d", &data);
            addFront(data);
        } else if (strcmp(command, "addBack") == 0) {
            scanf("%d", &data);
            addBack(data);
        } else if (strcmp(command, "removeFront") == 0) {
            removeFront();
        } else if (strcmp(command, "removeBack") == 0) {
            removeBack();
        } else if (strcmp(command, "empty") == 0) {
            empty_list();
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d %d", &n, &data);
            insert_node(n, data);
        } else if (strcmp(command, "remove") == 0) {
            scanf("%d", &n);
            remove_node(n);
        } else if (strcmp(command, "print") == 0) {
            print_list();
        }
    }

    // 程式結束時，清空串列，釋放所有記憶體
    empty_list(); // 清空時可能會輸出 "Double link list is empty" 如果已經是空的

    return 0;
}