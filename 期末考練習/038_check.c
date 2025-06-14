#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
        int data;
        struct node_s *front;
        struct node_s *back;
} node_t;

typedef node_t *nodep_t;

nodep_t head = NULL;
nodep_t tail = NULL;
int size = 0;

nodep_t create_node(int data) {
    nodep_t new_node;
    new_node = (nodep_t)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }
    new_node->data = data;
    new_node->front = NULL;
    new_node->back = NULL;
    return new_node;
}

void addFront(int data) {
    nodep_t now_node = create_node(data);

    if (size == 0) {
        head = now_node;
        tail = now_node;
    } else {
        now_node->back = head;
        head->front = now_node;
        head = now_node;
    }
    size++; // Move size++ outside the if-else block
}

void addBack(int data) {
    nodep_t now_node = create_node(data);

    if (size == 0) {
        head = now_node;
        tail = now_node;
    } else {
        now_node->front = tail;
        tail->back = now_node;
        tail = now_node;
    }
    size++; // Move size++ outside the if-else block
}

int check_empty() {
    if (size == 0) {
        printf("Double link list is empty\n");
        return 1;
    }
    return 0;
}

void removeFront() {
    if (check_empty() == 1) {
        return;
    }

    nodep_t temp = head; // Store the node to be freed

    if (size == 1) { // Special case: only one node
        head = NULL;
        tail = NULL;
    } else {
        head = head->back;
        head->front = NULL;
    }
    free(temp); // Free the old head
    size--;
}

void removeBack() {
    if (check_empty() == 1) {
        return;
    }

    nodep_t temp = tail; // Store the node to be freed

    if (size == 1) { // Special case: only one node
        head = NULL;
        tail = NULL;
    } else {
        tail = tail->front;
        tail->back = NULL;
    }
    free(temp); // Free the old tail
    size--;
}

void empty() {
    nodep_t current = head;
    while (current != NULL) {
        nodep_t next = current->back; // Store next before freeing current
        free(current);
        current = next;
    }
    head = NULL;
    tail = NULL;
    size = 0;
}

// head (front 0 1 2 3 4 5 6 back ) tail

void insert(int n, int data) {
    if (n <= 0 || n > size) { // n can be size + 1 to add at back
        printf("Invalid command\n");
        return;
    }

    if (n == size) { // Insert at the end
        addBack(data);
        return;
    }

    nodep_t new_node = create_node(data);
    nodep_t current = head;

    // Traverse to the node *before* the insertion point
    for (int i = 0; i < n - 1; i++) {
        current = current->back;
    }

    // Now 'current' points to the (n-1)th node
    // new_node will be inserted between 'current' and 'current->back'
    new_node->back = current->back;
    new_node->front = current;
    current->back->front =
        new_node; // Connect the next node's front to new_node
    current->back = new_node;

    size++;
}

void remove_node(int n) {
    if (check_empty() == 1) {
        return;
    }

    if (n <= 0 || n > size) {
        printf("Invalid command\n");
        return;
    }

    if (n == 1) {
        removeFront();
        return;
    }
    if (n == size) { // Remove the last node
        removeBack();
        return;
    }

    nodep_t node_to_delete = head;
    // Traverse to the node to be deleted
    for (int i = 1; i < n; i++) {
        node_to_delete = node_to_delete->back;
    }

    // Adjust pointers of surrounding nodes
    node_to_delete->front->back = node_to_delete->back;
    node_to_delete->back->front = node_to_delete->front;

    free(node_to_delete);
    size--;
}

void print_list_forward() { // Renamed to avoid conflict with print keyword
    if (check_empty() == 1) {
        return;
    }
    nodep_t current = head;

    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->back;
    }
}

void print_all() { // Renamed to print_list_summary for clarity
    nodep_t current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->back;
    }
    printf("\n"); // Use printf for new line
}

int main() {
    int total_times;
    scanf("%d", &total_times);

    for (int times = 0; times < total_times; times++) {
        char input_type[100];
        int data, n;
        scanf("%s", input_type);

        if (strcmp(input_type, "addFront") == 0) {
            scanf("%d", &data);
            addFront(data);
        } else if (strcmp(input_type, "addBack") ==
                   0) { // Use else if for efficiency
            scanf("%d", &data);
            addBack(data);
        } else if (strcmp(input_type, "removeFront") == 0) {
            removeFront();
        } else if (strcmp(input_type, "removeBack") == 0) {
            removeBack();
        } else if (strcmp(input_type, "empty") == 0) {
            empty();
        } else if (strcmp(input_type, "insert") == 0) {
            scanf("%d %d", &n, &data);
            insert(n, data);
        } else if (strcmp(input_type, "remove") == 0) {
            scanf("%d", &n);
            remove_node(n);
        } else if (strcmp(input_type, "print") == 0) {
            print_list_forward(); // Call the renamed print function
        }

        print_all(); // Print the current state of the list after each operation
    }

    // Clean up memory before exiting
    empty();

    return 0;
}