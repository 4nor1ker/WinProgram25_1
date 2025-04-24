#include <stdio.h>
#include <windows.h>

// 커서 이동 함수
void move_cursor(int row, int col) {
    COORD pos = { col - 1, row - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 배경 그리기
void DrawBG(int width, int height) {
    int row = 1;
    while (row <= height) {
        int col = 1;
        while (col <= width) {
            move_cursor(row, col);
            if (row == 1 || row == height || col <= 2 || col > width - 2) {
                printf(" ");
            }
            else if (row == height - 1) {
                printf("\033[100m \033[0m");
            }
            else {
                printf("\033[44m \033[0m");
            }
            col = col + 1;
        }
        row = row + 1;
    }
}

// 윈도우 출력 함수
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    int i, j;

    // 윗 테두리
    gotoxy(startX, startY);
    printf("\033[30m\033[4%im", color);
    printf("┌");
    i = 0;
    while (i < width - 2) {
        printf("─");
        i = i + 1;
    }
    printf("┐");

    // 두 번째 줄: 제목 + X 버튼
    gotoxy(startX, startY + 1);
    printf("│");

    // 배경 색 적용 줄 전체 초기화
    for (i = 1; i < width - 1; i++) {
        gotoxy(startX + i, startY + 1);
        printf("\033[4%im \033[0m\033[30m\033[4%im", color, color); // 공백 출력으로 배경만 칠함
    }

    // 제목 출력 (왼쪽 정렬)
    gotoxy(startX + 1, startY + 1);
    printf("\033[30m%s", title);

    // X 버튼 출력 (오른쪽 끝 - 2 위치)
    gotoxy(startX + width - 3, startY + 1);
    printf("\033[41;37mX\033[0m\033[30m\033[4%im", color);

    // 오른쪽 테두리
    gotoxy(startX + width - 1, startY + 1);
    printf("│");

    // 내부 채우기
    j = 2;
    while (j < height - 1) {
        gotoxy(startX, startY + j);
        printf("│");
        for (i = 1; i < width - 1; i++) {
            gotoxy(startX + i, startY + j);
            printf(" ");
        }
        gotoxy(startX + width - 1, startY + j);
        printf("│");
        j = j + 1;
    }

    // 아랫 테두리
    gotoxy(startX, startY + height - 1);
    printf("└");
    i = 0;
    while (i < width - 2) {
        printf("─");
        i = i + 1;
    }
    printf("┘");

    // 초기화
    printf("\033[0m");
    gotoxy(0, 25);
}

int main() {
    int width = 80;
    int height = 25;

    DrawBG(width, height);

    drawConsoleWindow(10, 5, 40, 10, "나의 멋진 윈도우", 3);  
 
    return 0;
}
