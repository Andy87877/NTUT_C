// 唯一二元樹
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node_s {
        char data;
        struct node_s *right, *left;
} tree_t;

typedef tree_t *btree;

btree create_node(char data) {
    btree new_node = (btree)malloc(sizeof(tree_t));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

// 找root
int find_mid_index(char middle_input[], int mid_begin, int mid_end,
                   char find_name) {
    for (int i = mid_begin; i <= mid_end; i++) {
        if (find_name == middle_input[i]) {
            return i;
        }
    }
    return -1; // 有問題
}

// 前序和中序
btree front_middle_route(char front_input[], char middle_input[],
                         int front_begin, int front_end, int mid_begin,
                         int mid_end) {
    if (front_begin > front_end || mid_begin > mid_end) {
        return NULL;
    }

    char front_name = front_input[front_begin];
    int mid_index = 0; // 找到根節點的位置
    mid_index = find_mid_index(middle_input, mid_begin, mid_end, front_name);
    printf("%c %d %d\n", front_name, mid_index, front_begin);

    btree now_tree = create_node(front_name);

    // if (mid_index == -1) {
    //     return now_tree;
    // }

    int left_size = mid_index - mid_begin;

    now_tree->left =
        front_middle_route(front_input, middle_input, front_begin + 1,
                           front_begin + left_size, mid_begin, mid_index - 1);
    now_tree->right = front_middle_route(front_input, middle_input,
                                         front_begin + left_size + 1, front_end,
                                         mid_index + 1, mid_end);

    return now_tree;
}

// 後序和中序
btree back_middle_route(char back_input[], char middle_input[], int back_begin,
                        int back_end, int mid_begin, int mid_end) {
    
    char back_name = back_input[back_end];
    btree now_tree = create_node()
                        }

void Print_tree(btree tree, int size) {
    btree array[MAX_SIZE];
    int print_index = 0, now_index = 0;

    btree current = tree;
    array[now_index] = current;

    while (print_index < size) {
        current = array[print_index];
        printf("%c", current->data);
        if (current->left != NULL) {
            now_index++;
            array[now_index] = current->left;
        }
        if (current->right != NULL) {
            now_index++;
            array[now_index] = current->right;
        }

        print_index++;
    }
}

// main
int main() {
    // 前序代號：P、中序代號：I、後序代號：O
    // front, middle, back
    char type_1, type_2;
    char input_1[MAX_SIZE], input_2[MAX_SIZE];

    btree tree = NULL; // 樹的link list

    scanf(" %c", &type_1);
    scanf("%s", &input_1);
    scanf(" %c", &type_2);
    scanf("%s", &input_2);

    int len_1 = strlen(input_1), len_2 = strlen(input_2);

    if (type_1 == 'I') {
        if (type_2 == 'P') {
            tree = front_middle_route(input_2, input_1, 0, len_2, 0, len_1);
        } else {
            tree = back_middle_route(input_2, input_1, 0, len_2, 0, len_1);
        }
    } else {
        // type_2 是中序
        if (type_1 == 'P') {
            tree = front_middle_route(input_1, input_2, 0, len_1, 0, len_2);
        } else {
            tree = back_middle_route(input_1, input_2, 0, len_1, 0, len_2);
        }
    }

    Print_tree(tree, len_1);
}

/*
序
前 中左右
中 左中右
後 左右中

一定會有中序!!! 因為這樣才有中間的基準
只要建出二元樹 就找就好了

先找到前/後的 root
再來在中序找到root
(中序)切割下來 前面就是左子樹 後面就是右子樹
接著就遞迴下去 慢慢地就會建出二元樹了
最終再找即可
*/