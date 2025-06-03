// ���⹮�� �� ��� ���� (ansi�ڵ�� ���ĺ� ����ϰ� �ɸ� �ð� ���

#include <stdio.h>
#include <time.h>
#include <windows.h>  // Sleep �Լ� ���

// ANSI Escape Code�� Ŀ�� �̵� �Լ�
// (x, y) ��ǥ�� Ŀ���� �̵��Ͽ� ���ϴ� ��ġ�� ����� �� �ְ� ��
// �ܼ��� ��ǥ�� (1,1)���� �����ϱ� ������ y+1, x+1�� ���缭 ���
void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;   // ���α׷� ���۰� ���� �ð� ��Ͽ� ����
    double elapsed;       // ��� �ð�(�� ����)�� ����� ����

    start = clock();      // ���α׷� ���� �ð� ����

    // ���ĺ� 'a'���� 'j'���� 10ȸ �ݺ��Ͽ� ���
    for (int i = 0; i < 10; i++) {
        moveCursor(0, i); // i��° ��(���� y��ǥ)�� ��� ��ġ �̵�

        // ���ĺ� 'a'(97)���� 'j'(106)���� ���
        // 97 + i�� ������ ASCII �ڵ� ���� ����Ͽ� ���
        printf("���� %c�� ��µǾ����ϴ�.\n", 97 + i);

        Sleep(1000);      // 1��(1000ms) ���
    }

    end = clock();        // ���α׷� ���� �ð� ����

    // ��� �ð�(��) ���
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ��� �Ϸ� �޽����� ȭ���� (0,12) ��ġ�� ���
    moveCursor(0, 12);
    printf("��� �Ϸ�! ��� �ð�: %.3f��\n", elapsed);

    return 0;
}
