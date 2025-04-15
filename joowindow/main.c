#include <stdio.h>
#include <windows.h>

// gotoxy 함수 정의
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 윈도우 창 그리기 함수 (변수 없이 중간 가로선 추가)
void drawWindow(int x, int y, int width, int height) {
    int i;

    // 윗줄 (모서리 +, 나머지는 -)
    gotoxy(x, y);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // 윗줄의 가로 선
    }
    printf("+");

    // 중간 가로선 (위쪽에 하나 더 추가, 위치는 y+2)
    gotoxy(x, y + 2);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // 중간 가로선의 가로 선
    }
    printf("+");

    // 왼쪽/오른쪽 줄 (모서리는 +, 나머지는 |)
    for (i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);  // 왼쪽 세로 선 위치
        printf("|");  // 왼쪽 세로 선
        gotoxy(x + width - 1, y + i);  // 오른쪽 세로 선 위치
        printf("|");  // 오른쪽 세로 선
    }

    // 아랫줄 (모서리 +, 나머지는 -)
    gotoxy(x, y + height - 1);
    printf("+");
    for (i = 0; i < width - 2; i++) {
        printf("-");  // 아랫줄의 가로 선
    }
    printf("+");
}

int main() {
    // 예시: (10, 3) 위치에서 너비 20, 높이 7인 윈도우 창 그리기
    drawWindow(10, 3, 20, 7);
    return 0;
}
