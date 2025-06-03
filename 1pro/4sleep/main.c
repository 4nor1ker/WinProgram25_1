#include <stdio.h>
#include <windows.h>  // Sleep 함수를 사용하기 위한 헤더 (Windows 전용)

int main()
{
    //for (int i = 1; i <= 5; i++)
    //{
    //    printf("%d초 경과...\n", i);
    //    Sleep(1000);  // 1000밀리초 = 1초 동안 프로그램 일시 정지
    //}
    int i = 0;
    while (i <= 50)
    {
        printf("%d초 경과...\n", i);
        Sleep(10000);  // 1000밀리초 = 1초 동안 프로그램 일시 정지
        i = i + 10;
    }
}

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// ANSI Escape Code를 이용한 커서 이동 함수
void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x); // 커서를 (x, y) 위치로 이동 (y가 행, x가 열)
}

int main() {
    printf("아무 키나 누르면 'Pressed'가 나타납니다.\n");
    printf("키를 누르지 않으면 지워집니다.\n\n");

    while (1) {
        gotoXY(0, 5); // 커서를 5행 0열로 이동

        if (_kbhit()) {
            _getch(); // 키보드 입력을 받아오되, 화면에는 출력하지 않음
            printf("Pressed"); // 키가 눌렸을 때 출력
        }
        else {
            printf(" "); // 키가 안 눌렸을 때 기존 글자 덮어쓰기
        }

        // CPU 사용량을 줄이기 위해 약간의 지연을 줌
        // Sleep(0)을 넣지 않으면 while문이 너무 빨리 돌아서 컴퓨터가 과도한 연산을 하게 됨 (CPU 100%)
        Sleep(100); // 100ms 대기 (0.1초)
    }

    return 0;
}
