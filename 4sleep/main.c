#include <stdio.h>
#include <windows.h>  // Sleep �Լ��� ����ϱ� ���� ��� (Windows ����)

int main()
{
    //for (int i = 1; i <= 5; i++)
    //{
    //    printf("%d�� ���...\n", i);
    //    Sleep(1000);  // 1000�и��� = 1�� ���� ���α׷� �Ͻ� ����
    //}
    int i = 0;
    while (i <= 50)
    {
        printf("%d�� ���...\n", i);
        Sleep(10000);  // 1000�и��� = 1�� ���� ���α׷� �Ͻ� ����
        i = i + 10;
    }
}

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// ANSI Escape Code�� �̿��� Ŀ�� �̵� �Լ�
void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x); // Ŀ���� (x, y) ��ġ�� �̵� (y�� ��, x�� ��)
}

int main() {
    printf("�ƹ� Ű�� ������ 'Pressed'�� ��Ÿ���ϴ�.\n");
    printf("Ű�� ������ ������ �������ϴ�.\n\n");

    while (1) {
        gotoXY(0, 5); // Ŀ���� 5�� 0���� �̵�

        if (_kbhit()) {
            _getch(); // Ű���� �Է��� �޾ƿ���, ȭ�鿡�� ������� ����
            printf("Pressed"); // Ű�� ������ �� ���
        }
        else {
            printf(" "); // Ű�� �� ������ �� ���� ���� �����
        }

        // CPU ��뷮�� ���̱� ���� �ణ�� ������ ��
        // Sleep(0)�� ���� ������ while���� �ʹ� ���� ���Ƽ� ��ǻ�Ͱ� ������ ������ �ϰ� �� (CPU 100%)
        Sleep(100); // 100ms ��� (0.1��)
    }

    return 0;
}
