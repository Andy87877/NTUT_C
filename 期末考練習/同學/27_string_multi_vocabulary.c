#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vocabulary {
        char data[10];
        char comma;
} vocabulary;

void StrToVoca(char* str, vocabulary* voca) {
    voca->comma = '\0';

    int index = 0;
    while (str[index] != '\0') {
        if (str[index] == '.' || str[index] == ',' || str[index] == '!' ||
            str[index] == '?' || str[index] == ';' || str[index] == ':') {
            voca->comma = str[index];
            break;
        }

        if (str[index] == ' ' || str[index] == '\n') break;

        voca->data[index] = str[index];
        index++;
    }
    voca->data[index] = '\0';
}

int main() {
    vocabulary vocas[100];

    char line[200], p[10] = {0}, q[10] = {0};
    fgets(line, 200, stdin);
    scanf("%s %s", p, q);

    int count = 0;
    char* token = strtok(line, " \n");
    while (token != NULL) {
        StrToVoca(token, &vocas[count++]);
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(vocas[i].data, p) == 0)
            printf("%s%c ", q, vocas[i].comma);
        else
            printf("%s%c ", vocas[i].data, vocas[i].comma);
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(vocas[i].data, p) == 0) printf("%s ", q);
        printf("%s%c ", vocas[i].data, vocas[i].comma);
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(vocas[i].data, p) == 0)
            printf("%s%c %s ", vocas[i].data, vocas[i].comma, q);
        else
            printf("%s%c ", vocas[i].data, vocas[i].comma);
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(vocas[i].data, p) == 0)
            continue;
        else
            printf("%s%c ", vocas[i].data, vocas[i].comma);
    }
    printf("\n");
    for (int i = count - 1; i >= 0; i--) {
        printf("%s%c ", vocas[i].data, vocas[i].comma);
    }
    printf("\n");
}
