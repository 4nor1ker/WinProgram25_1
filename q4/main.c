// 제목 : 1초마다 별을 출력하며 5초 뒤에 종료되는 콘솔 타이머 프로그램

#include <stdio.h>
#include <windows.h>  // Sleep 함수 사용
#include <time.h>     // clock() 사용

// ANSI Escape Code로 커서 이동 함수
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    clock_t start, now;  // 타이머 시작과 현재 시간
    double elapsed;      // 경과 시간(초)

    start = clock();     // 타이머 시작 시간 기록

    int i = 0;           // 별 출력 개수

    while (1) {
        now = clock();  // 현재 시간 갱신
        elapsed = (double)(now - start) / CLOCKS_PER_SEC;

        if (elapsed >= 5.0) {
            // 5초 경과 시 타이머 종료
            gotoxy(1, 3);  // (1,3) 위치로 이동
            printf("타이머 종료\n");
            break;
        }

        if (i < (int)elapsed + 1) {
            // 초 단위로 별 출력
            gotoxy(i + 1, 1);  // (i+1,1) 위치로 이동
            printf("*");
            i++;
        }

        Sleep(10);  // CPU 과부하 방지
    }

    return 0;
}
