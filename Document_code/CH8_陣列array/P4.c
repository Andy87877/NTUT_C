// �}�C���O�ЪŶ��Τj�p
#include <stdio.h>

int main() {
    double data[101];
    printf("�}�C�Ҧ��줸��%d\n", sizeof(data));
    printf("�}�C�����Ҧ��줸��%d\n", sizeof(data[0]));
    printf("�}�C�Ӽ�%d", sizeof(data) / sizeof(double));
    return 0;
}