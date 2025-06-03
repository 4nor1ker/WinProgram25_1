// ���� : 1�ʸ��� ���� ����ϸ� 5�� �ڿ� ����Ǵ� �ܼ� Ÿ�̸� ���α׷�

#include <stdio.h>
#include <windows.h>  // Sleep �Լ� ���
#include <time.h>     // clock() ���

// ANSI Escape Code�� Ŀ�� �̵� �Լ�
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    clock_t start, now;  // Ÿ�̸� ���۰� ���� �ð�
    double elapsed;      // ��� �ð�(��)

    start = clock();     // Ÿ�̸� ���� �ð� ���

    int i = 0;           // �� ��� ����

    while (1) {
        now = clock();  // ���� �ð� ����
        elapsed = (double)(now - start) / CLOCKS_PER_SEC;

        if (elapsed >= 5.0) {
            // 5�� ��� �� Ÿ�̸� ����
            gotoxy(1, 3);  // (1,3) ��ġ�� �̵�
            printf("Ÿ�̸� ����\n");
            break;
        }

        if (i < (int)elapsed + 1) {
            // �� ������ �� ���
            gotoxy(i + 1, 1);  // (i+1,1) ��ġ�� �̵�
            printf("*");
            i++;
        }

        Sleep(10);  // CPU ������ ����
    }

    return 0;
}
