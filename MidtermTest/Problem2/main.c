#include <stdio.h>
#include <windows.h>

// -----------------------------
// 커서 이동 함수
// -----------------------------
void move_cursor(int row, int col) {
    COORD pos = { col - 1, row - 1 };  // 콘솔 좌표는 0부터 시작
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// -----------------------------
// 바탕화면 + 작업표시줄 그리기
// -----------------------------
void DrawBG(int width, int height) {
    int row = 1;
    while (row <= height) {
        int col = 1;
        while (col <= width) {
            move_cursor(row, col);

            if (row == 1 || row == height || col <= 2 || col > width - 2) {
                printf(" ");  // 상하좌우 여백
            }
            else if (row == height - 1) {
                printf("\033[100m \033[0m");  // 진회색 작업표시줄
            }
            else {
                printf("\033[44m \033[0m");   // 파란 배경
            }

            col = col + 1;
        }
        row = row + 1;
    }
}

// -----------------------------
// 윈도우 창 출력 함수
// -----------------------------
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    int i;

    printf("\033[30m\033[4%im", color);  // 검정 글자 + 배경

    // 윗줄
    gotoxy(startX, startY);
    printf("┌");
    for (i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┐");

    // 제목
    gotoxy(startX + 1, startY);
    printf("%s", title);

    // 닫기 버튼
    gotoxy(startX + width - 4, startY);
    printf("\033[41;37m X \033[4%im", color);  // 빨간 배경 X, 다시 원래 배경으로

    // 세로줄
    for (i = 1; i < height - 1; i++) {
        gotoxy(startX, startY + i);
        printf("│");
        gotoxy(startX + width - 1, startY + i);
        printf("│");
    }

    // 아랫줄
    gotoxy(startX, startY + height - 1);
    printf("└");
    for (i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┘");

    // 초기화 및 커서 위치 정리
    printf("\033[0m");
    gotoxy(0, startY + height + 1);
}

// -----------------------------
// main 함수
// -----------------------------
int main() {
    int width = 80;
    int height = 25;

    DrawBG(width, height);  // 배경 먼저 출력

    // 예시로 하나의 윈도우 출력 (하늘색: 6)
    drawConsoleWindow(10, 5, 30, 8, "나의 멋진 윈도우", 6);

    return 0;
}
