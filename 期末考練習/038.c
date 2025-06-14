// 038. Double Link List
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s{
    int data;
    struct node_s *front;
    struct node_s *back;
} node_t;

typedef node_t * nodep_t;

nodep_t Node = NULL;

void addFront(){
    
}

int main(){
    int n;
    scanf("%d", &n);

    for (int times = 0; times < n; times++){
        char input_type[100];
        scanf("%s", &input_type);

        if (strcmp(input_type, "addFront") == 0){

        }
    }
}