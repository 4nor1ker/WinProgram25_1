#include <windows.h>
#include <stdio.h>

int main()
{
    char letter = 'O';               // 출력할 문자
    POINT mousePos;                  // 마우스 위치 (스크린 기준)
    int isDragging = 0;              // 드래그 중인지 여부
    int letterX = 10;                // O의 X 위치
    int letterY = 5;                 // O의 Y 위치

    while (1)
    {
        // 빠른 편집 모드 끄기 (이거 안하면 클릭 했을 때 콘솔 결과 화면이 사라지는 버그 있음
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS);

        system("cls");

        // 안내문 출력
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
        printf("현재 알파벳 위치: (%d, %d)\n", letterX, letterY);

        // 마우스 위치 얻기
        GetCursorPos(&mousePos);
        ScreenToClient(GetConsoleWindow(), &mousePos);  // ← 콘솔 기준 좌표로 변환

        // 마우스 커서 위치 (콘솔 단위)
        int cursorX = mousePos.x / 8;
        int cursorY = mousePos.y / 16;

        // 현재 마우스 위치 출력
        printf("현재 마우스 위치: (%d, %d)\n", cursorX, cursorY);

        // 드래그 시작 조건: 클릭 + 커서가 O 위에 있을 때
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !isDragging)
        {
            if (cursorX == letterX && cursorY == letterY) {
                isDragging = 1;
            }
        }

        // 드래그 중일 때: O의 위치를 마우스 위치로 업데이트
        if (isDragging)
        {
            letterX = cursorX;
            letterY = cursorY;
            printf("드래그 중...\n");
        }
        else {
            printf("드래그 아님\n");
        }

        // 마우스 버튼 떼면 드래그 종료
        if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
        {
            isDragging = 0;
        }

        // O 출력
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // ESC 누르면 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            printf("\n프로그램 종료\n");
            break;
        }

        Sleep(100);
    }

    return 0;
}
