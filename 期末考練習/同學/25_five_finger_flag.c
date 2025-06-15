

#include <stdio.h>

int Sum(int* arr, int begin, int end) {
    int temp = 0;
    for (int i = begin; i < end; i++) temp += arr[i];
    return temp;
}
void RawConvolution(int SourceTable[12][12], int ansTable[12][12]) {
    int kernel[7] = {-100, 11, 12, 13, 14, 15, -100};

    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < 6; j++) {
            // dot product
            int dot = 0;
            for (int k = 0; k < 7; k++)
                dot += kernel[k] * SourceTable[i][j + k];

            int index = Sum(kernel, 1, 6) - dot;
            if (index <= 15) ansTable[i][j + index - 10] += 1;
        }
    }
}
void InclineConvolution(int SourceTable[12][12], int ansTable[12][12]) {
    int kernel[7] = {-100, 11, 12, 13, 14, 15, -100};

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            // dot product
            int dot = 0;
            for (int k = 0; k < 7; k++)
                dot += kernel[k] * SourceTable[i + k][j + k];

            printf("%d %d %d\n", i, j, dot);

            int index = Sum(kernel, 1, 6) - dot;
            if (index <= 15) ansTable[i + index - 10][j + index - 10] += 1;
        }
    }
}

void RotateTable(int table[12][12]) {
    int temp[12][12];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++) temp[i][j] = table[j][11 - i];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++) table[i][j] = temp[i][j];
}
void ScanTable(int table[12][12]) {
    for (int i = 1; i < 11; i++)
        for (int j = 1; j < 11; j++) scanf("%d", &table[i][j]);
}
void PrintTable(int table[12][12]) {
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int dataTable[12][12] = {0}; // 儲存輸入
    int ansTable[12][12] = {0};  // 儲存結果

    ScanTable(dataTable);
    printf("\n");

    RawConvolution(dataTable, ansTable);     // 橫
    InclineConvolution(dataTable, ansTable); // 橫

    RotateTable(dataTable);
    RotateTable(ansTable);
    RawConvolution(dataTable, ansTable);     // 直
    InclineConvolution(dataTable, ansTable); // 橫

    for (int i = 0; i < 3; i++) {
        RotateTable(dataTable);
        RotateTable(ansTable);
    }

    printf("\n");
    PrintTable(ansTable);
}
