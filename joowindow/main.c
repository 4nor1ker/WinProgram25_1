#include <stdio.h>
#include <windows.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int color;
} jooWindow;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBox(jooWindow win)
{
    int i;
    printf("\033[30m\033[4%im", win.color);

    gotoxy(win.x, win.y);
    printf("+");

    i = 0;
    while (i < win.width - 2)
    {
        printf("-");
        i = i + 1;
    }
    printf("+");

    gotoxy(win.x, win.y + 2);
    printf("+");

    i = 0;
    while (i < win.width - 2)
    {
        printf("-");
        i = i + 1;
    }
    printf("+");

    i = 0;
    while (i < win.height - 2)
    {
        gotoxy(win.x, win.y + i + 1);
        printf("|");
        gotoxy(win.x + win.width - 1, win.y + i + 1);
        printf("|");
        i = i + 1;
    }

    // 아랫줄
    gotoxy(win.x, win.y + win.height - 1);
    printf("+");

    i = 0;
    while (i < win.width - 2)
    {
        printf("-");
        i = i + 1;
    }
    printf("+");

    printf("\033[0m");
    gotoxy(0, 15);
}

int main()
{
    int i = 0;
    while (i < 15)
    {
        printf("\033[42m");  
        printf("                                                                                           "); 
        printf("\033[40m\n"); 
        i = i + 1;
    }

    jooWindow a, b;
    a.x = 10;
    a.y = 3;
    a.width = 20;
    a.height = 7;
    a.color = 7;

    b.x = 15;
    b.y = 5;
    b.width = 20;
    b.height = 7;
    b.color = 4;

    drawBox(a);  // 위치(10,3), 크기 20x7 (하얀색)
    drawBox(b);  // 동일한 크기 윈도우 띄우기 (15,5) (파란색)

    return 0;
}
