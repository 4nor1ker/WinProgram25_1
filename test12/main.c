#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    gotoxy(52, 1); printf("(    )");
    gotoxy(52, 2); printf("(   )");
    gotoxy(51, 3); printf("(   )             /\\");
    gotoxy(51, 4); printf("(  (             /  \\  /\\");
    gotoxy(52, 5); printf(")  )          /\\/\\/\\/\\  \\");
    gotoxy(19, 6); printf("________________________|  |__      /      \\/\\/\\/");
    gotoxy(18, 7); printf("/\\            ______      |  |  \\  /            \\");
    gotoxy(5, 8);  printf("/\\          //__\\          \\    /\\          \\");
    gotoxy(4, 9);  printf("/\\    /  \\ //___\\          \\  /  \\           \\");
    gotoxy(3, 10); printf("/  \\/\\/\\/\\ //_____\\          \\ |[]|          \\");
    gotoxy(2, 11); printf("/\\/\\/\\    \\//_______\\          \\|__|           \\");
    gotoxy(1, 12); printf("//       \\/xxxxxxxxxx\\                          \\");
    gotoxy(13, 13); printf("/_|_||   |_|_\\______________________________\\");
    gotoxy(15, 14); printf("|_||   |_|_-----[][]---------[][]-----|");
    gotoxy(15, 15); printf("|_||   |_|_-----[][]---------[][]-----|");
    gotoxy(15, 16); printf("|_||___|_|_---------------------------|");

    return 0;
}
