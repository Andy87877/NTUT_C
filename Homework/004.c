#include <stdio.h>
#include <stdlib.h>

void check_ERROR(int kg, int cm){
    int ERROR = 0;
    if (!((20 <= kg) && (kg <= 100))){
        ERROR = 1;
    }
    if (!((100 <= cm) && (cm <= 200))){
        ERROR = 1;
    }
    if (ERROR){
        printf("ERROR\n");
        exit(0);
    }
}

int get_BMI(int kg, int cm){
    double meter;
    meter = ((double)cm / 100);

    double BMI_float = ((double)kg / (meter*meter));

    BMI_float *= 10;
    //保留小數點後一位
    int BMI = (int)BMI_float;
    if (BMI%10 == 5){
        if (((BMI%100)/10) % 2 == 0){ //整數是奇數
            BMI += 10;
        }
    } else if (BMI%10 >= 6){
        BMI += 10;
    }

    BMI /= 10;

    return BMI;
}

int judge_BMI(int BMI){
    if (BMI > 24){
        printf("too high\n");
    }
    if (BMI < 18){
        printf("too low\n");
    }
}

int main(){
    int kg, cm;
    scanf("%d", &kg);
    scanf("%d", &cm);

    check_ERROR(kg, cm);

    int BMI = get_BMI(kg, cm);
    printf("%d\n", BMI);
    
    judge_BMI(BMI);
}