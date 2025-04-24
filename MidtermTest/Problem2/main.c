#include <stdio.h>
#include <windows.h>

// 커서 이동 함수 (row: y, col: x)
void move_cursor(int row, int col) {
    COORD pos = { col - 1, row - 1 };  // 콘솔 좌표는 0부터 시작
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 바탕화면과 작업표시줄을 그리는 함수
void DrawBG(int width, int height) {
    int row = 1;
    while (row <= height) {
        int col = 1;
        while (col <= width) {
            move_cursor(row, col);

            // 상단 1줄 또는 하단 1줄 또는 좌우 2칸 여백
            if (row == 1 || row == height || col <= 2 || col > width - 2) {
                printf(" ");  // 여백
            }
            // 작업표시줄 (아래에서 두 번째 줄)
            else if (row == height - 1) {
                printf("\033[100m \033[0m");  // 진회색 배경
            }
            // 바탕화면 본영역
            else {
                printf("\033[44m \033[0m");  // 파란 배경
            }

            col = col + 1;
        }
        row = row + 1;
    }
}

int main() {
    int width = 80;   // 문제 조건 해상도
    int height = 25;

    // 배경 그리기
    DrawBG(width, height);

    return 0;
}
