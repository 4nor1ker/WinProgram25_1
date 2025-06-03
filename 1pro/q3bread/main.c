// 기출문제 빵 출력 문제 (ansi코드로 알파벳 출력하고 걸린 시간 계산

#include <stdio.h>
#include <time.h>
#include <windows.h>  // Sleep 함수 사용

// ANSI Escape Code로 커서 이동 함수
// (x, y) 좌표로 커서를 이동하여 원하는 위치에 출력할 수 있게 함
// 콘솔의 좌표는 (1,1)부터 시작하기 때문에 y+1, x+1로 맞춰서 출력
void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;   // 프로그램 시작과 종료 시간 기록용 변수
    double elapsed;       // 경과 시간(초 단위)을 계산할 변수

    start = clock();      // 프로그램 시작 시간 저장

    // 알파벳 'a'부터 'j'까지 10회 반복하여 출력
    for (int i = 0; i < 10; i++) {
        moveCursor(0, i); // i번째 줄(세로 y좌표)에 출력 위치 이동

        // 알파벳 'a'(97)부터 'j'(106)까지 출력
        // 97 + i로 문자의 ASCII 코드 값을 계산하여 출력
        printf("빵이 %c개 출력되었습니다.\n", 97 + i);

        Sleep(1000);      // 1초(1000ms) 대기
    }

    end = clock();        // 프로그램 종료 시간 저장

    // 경과 시간(초) 계산
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    // 출력 완료 메시지를 화면의 (0,12) 위치에 출력
    moveCursor(0, 12);
    printf("출력 완료! 경과 시간: %.3f초\n", elapsed);

    return 0;
}
