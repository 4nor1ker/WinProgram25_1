#include <stdio.h>
#include <time.h>
#include <windows.h>  // Sleep �Լ� ����� ���� ��� (Windows ����)

#define FPS 60                        // ��ǥ ������ �� (60 FPS)
#define FRAME_TIME (1000 / FPS)      // �� �����ӿ� �ҿ�Ǿ�� �� �ð� (�и��� ����, 16.67ms ����)

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    int frameNum = 0;
    while (1) {  // ���� ����: ���� ���� ����
        clock_t frameStart = clock();  // ���� �ð� ���� (������ ���� �ð�)

        // --- ���� ���� ������Ʈ �� ������ ó�� �κ� ---
        moveCursor(0, 0);
        printf("���� ������ %d�� ó��\n", frameNum);
        frameNum = frameNum + 1;
        // ------------------------------------------------

        clock_t frameEnd = clock();  // ������ �۾� �Ϸ� �� ���� �ð� ����

        // ������ ó���� �ɸ� �ð� ��� (�и��� ������ ȯ��)
        double elapsed = (double)(frameEnd - frameStart) * 1000 / CLOCKS_PER_SEC;

        // �������� �ʹ� ���� �������� ���� �ð���ŭ ���
        if (elapsed < FRAME_TIME) {
            Sleep((DWORD)(FRAME_TIME - elapsed));  // �и��� ������ ���
        }
        // �������� ���� �ɷȴٸ� ������� �ʰ� �ٷ� ���� ������ ����
    }

    return 0;
}

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;       // ���۰� �� �ð� ����� ����
    double cpu_time_used;     // ��� �ð� (��) ����� ����

    start = clock();          // ���� CPU �ð��� ���� �ð����� ����

    int i = 0;
    // ���� �۾�: �ð��� ���� �ɸ��� ���� (�ð� ������ ���� ���� �۾�)
    while (i < 100000)
    {
        moveCursor(0, 0);
        printf("�������R %d\n", i);
        i = i + 1;
    }

    end = clock();            // ���� CPU �ð��� �� �ð����� ����

    // ��� �ð� ��� (ƽ �� ���� / �ʴ� ƽ ��)
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n�۾��� �ɸ� �ð�: %.3f��\n", cpu_time_used);  // ��� ���

    return 0;