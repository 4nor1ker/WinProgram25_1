#include <stdio.h>
#include <windows.h>

// gotoxy �Լ� ����
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ������ â �׸��� �Լ� (���� ���� �߰� ���μ� �߰�)
void drawWindow(int x, int y, int width, int height) {
    int i;

    // ���� (�𼭸� +, �������� -)
    gotoxy(x, y);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // ������ ���� ��
    }
    printf("+");

    // �߰� ���μ� (���ʿ� �ϳ� �� �߰�, ��ġ�� y+2)
    gotoxy(x, y + 2);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // �߰� ���μ��� ���� ��
    }
    printf("+");

    // ����/������ �� (�𼭸��� +, �������� |)
    for (i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);  // ���� ���� �� ��ġ
        printf("|");  // ���� ���� ��
        gotoxy(x + width - 1, y + i);  // ������ ���� �� ��ġ
        printf("|");  // ������ ���� ��
    }

    // �Ʒ��� (�𼭸� +, �������� -)
    gotoxy(x, y + height - 1);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // �Ʒ����� ���� ��
    }
    printf("+");
}

int main() {
    // ����: (10, 3) ��ġ���� �ʺ� 20, ���� 7�� ������ â �׸���
    drawWindow(10, 3, 20, 7);
    return 0;
}
