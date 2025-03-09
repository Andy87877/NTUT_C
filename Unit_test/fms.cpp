#include <stdio.h>
// fms.cpp
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
    start,
    build_id,
    build_num,
    build_invalid,
    identifier,
    number,
    invalid,
    stop
} state_t;
state_t getNextState(state_t current_state, char ch) {
    if (current_state == start) {
        if (ch == ' ')
            return start;
        else if (isalpha(ch))
            return build_id;
        else if (isdigit(ch))
            return build_num;
        else if (ch == '#')
            return stop;
    }
    if (current_state == build_id) {
        if (isalpha(ch) || isdigit(ch) || (ch == '_'))
            return build_id;
        else if (ch == ' ')
            return identifier;
    }
    if (current_state == build_num) {
        if (isdigit(ch))
            return build_num;
        else if (ch == ' ')
            return number;
    }
    return stop;
}
char *FMS(char *s) {
    // fms.cpp
    char out[80];
    char *output = (char *)malloc(sizeof(char) * 500);
    char input_char;
    int index = 0;
    state_t current_state;
    current_state = start;
    strcpy(output, "");
    do {
        if (current_state == identifier) {
            current_state = start;
            sprintf(out, " - identifier\n");
            strcat(output, out);
        } else if (current_state == number) {
            current_state = start;
            sprintf(out, " - number\n");
            strcat(output, out);
        }
        // scanf("%c", &input_char);
        input_char = s[index++];
        if ((input_char != ' ') && (input_char != '#')) {
            sprintf(out, "%c", input_char);
            strcat(output, out);
        }
        current_state = getNextState(current_state, input_char);
    } while (current_state != stop);
    return output;
}