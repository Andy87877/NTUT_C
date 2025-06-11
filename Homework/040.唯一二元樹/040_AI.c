#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Link List 架構定義
typedef struct node_s {
        char data;
        struct node_s *right, *left;
} tree_t;

typedef tree_t* btree;

// 在中序遍歷字串中尋找指定字元的位置
int find_inorder_index(char* inorder, int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1; // 理論上不會發生
}

// 根據前序和中序遍歷結果建立二元樹
btree build_from_pre_in(char* preorder, char* inorder, int in_start, int in_end,
                        int* pre_index) {
    // 基本情況：如果範圍無效，則返回空樹
    if (in_start > in_end) {
        return NULL;
    }

    // 從前序遍歷中取出當前根節點
    char root_val = preorder[(*pre_index)++];

    // 建立新節點
    btree node = (btree)malloc(sizeof(tree_t));
    node->data = root_val;
    node->left = node->right = NULL;

    // 如果此節點是葉節點，直接返回
    if (in_start == in_end) {
        return node;
    }

    // 在中序遍歷中找到根節點的位置，以區分左右子樹
    int in_index = find_inorder_index(inorder, in_start, in_end, root_val);

    // 遞迴建立左子樹和右子樹
    node->left =
        build_from_pre_in(preorder, inorder, in_start, in_index - 1, pre_index);
    node->right =
        build_from_pre_in(preorder, inorder, in_index + 1, in_end, pre_index);

    return node;
}

// 根據後序和中序遍歷結果建立二元樹
btree build_from_post_in(char* postorder, char* inorder, int in_start,
                         int in_end, int* post_index) {
    // 基本情況：如果範圍無效，則返回空樹
    if (in_start > in_end) {
        return NULL;
    }

    // 從後序遍歷的尾端取出當前根節點
    char root_val = postorder[(*post_index)--];

    // 建立新節點
    btree node = (btree)malloc(sizeof(tree_t));
    node->data = root_val;
    node->left = node->right = NULL;

    // 如果此節點是葉節點，直接返回
    if (in_start == in_end) {
        return node;
    }

    // 在中序遍歷中找到根節點的位置
    int in_index = find_inorder_index(inorder, in_start, in_end, root_val);

    // 遞迴建立右子樹和左子樹 (注意：順序與 pre-in 相反)
    node->right = build_from_post_in(postorder, inorder, in_index + 1, in_end,
                                     post_index);
    node->left = build_from_post_in(postorder, inorder, in_start, in_index - 1,
                                    post_index);

    return node;
}

// 層序遍歷 (Level Order Traversal) 輸出樹的內容
void print_level_order(btree root) {
    if (!root) {
        return;
    }

    // 使用一個陣列作為佇列 (Queue)
    // 題目限制長度最多20，節點最多20個，佇列大小設為50很安全
    btree queue[50];
    int front = 0, rear = 0;

    // 將根節點放入佇列
    queue[rear++] = root;

    while (front < rear) {
        // 從佇列取出節點
        btree current = queue[front++];
        printf("%c", current->data);

        // 將左子節點放入佇列
        if (current->left) {
            queue[rear++] = current->left;
        }
        // 將右子節點放入佇列
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
}

int main() {
    char type1, type2;
    char str1[25], str2[25];
    char *preorder = NULL, *inorder = NULL, *postorder = NULL;

    // 讀取第一組輸入
    scanf(" %c", &type1);
    scanf("%s", str1);

    // 讀取第二組輸入
    scanf(" %c", &type2);
    scanf("%s", str2);

    // 根據輸入的代號，將字串指標指向正確的遍歷結果
    if (type1 == 'P') {
        preorder = str1;
        inorder = str2;
    } else if (type1 == 'O') {
        postorder = str1;
        inorder = str2;
    } else if (type1 == 'I') {
        inorder = str1;
        if (type2 == 'P') {
            preorder = str2;
        } else { // type2 == 'O'
            postorder = str2;
        }
    }

    btree root = NULL;
    int len = strlen(inorder);

    if (preorder && inorder) {
        int pre_index = 0;
        root = build_from_pre_in(preorder, inorder, 0, len - 1, &pre_index);
    } else if (postorder && inorder) {
        int post_index = len - 1;
        root = build_from_post_in(postorder, inorder, 0, len - 1, &post_index);
    }

    // 如果成功建立樹，則進行層序輸出
    if (root) {
        print_level_order(root);
        printf("\n");
    }

    // 在一個完整的程式中，應該要有釋放樹記憶體的函式，但此題不要求
    // free_tree(root);

    return 0;
}