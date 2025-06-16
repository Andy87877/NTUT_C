#include <stdio.h>
#include <stdlib.h>

// #define GATEVALUE(Gate) int(*GateValue)()
typedef struct _Gate {
        int input1;
        int input2;
        int (*GateValue)(struct _Gate*);
} Gate;

int GateORValue(Gate* gate) { return gate->input1 | gate->input2; }
int GateANDValue(Gate* gate) { return gate->input1 & gate->input2; }
int GateNORValue(Gate* gate) { return ~(gate->input1 | gate->input2); }
int GateNANDValue(Gate* gate) { return ~(gate->input1 & gate->input2); }

int GateNOTValue(Gate* gate) { return ~gate->input1; }
int GateBUFFERValue(Gate* gate) { return gate->input1; }

void CreateGate(Gate** obj, char* type, int input1, int input2) {
    *obj = (Gate*)malloc(sizeof(Gate));
    (*obj)->input1 = input1;
    (*obj)->input2 = input2;

    if (type[0] == 'N') {
        if (type[1] == '\0')
            (*obj)->GateValue = GateNOTValue;
        else if (type[1] == 'A')
            (*obj)->GateValue = GateNANDValue;
        else if (type[1] == 'O')
            (*obj)->GateValue = GateNORValue;
    } else if (type[0] == 'B')
        (*obj)->GateValue = GateBUFFERValue;
    else if (type[0] == 'A')
        (*obj)->GateValue = GateANDValue;
    else if (type[0] == 'O')
        (*obj)->GateValue = GateORValue;
}

int main() {
    int x[3], y, o;
    Gate *gateX[3], *gateY = NULL, *gateO = NULL;
    scanf("%d%d%d", &x[0], &x[1], &x[2]);

    for (int i = 0; i < 3; i++) {
        char type[3];
        scanf("%s", &type);
        CreateGate(&gateX[i], type, x[i], 0);
    }
    char type[3];
    scanf("%s", type);
    CreateGate(&gateY, type, gateX[0]->GateValue(gateX[0]),
               gateX[1]->GateValue(gateX[1]));
    scanf("%s", type);
    CreateGate(&gateO, type, gateY->GateValue(gateY),
               gateX[2]->GateValue(gateX[2]));

    int result = gateO->GateValue(gateO);
    printf("%d%d%d", (result >> 2) & 1, (result >> 1) & 1, result & 1);
}
