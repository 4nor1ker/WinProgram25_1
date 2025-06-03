// 예상문제 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>       // 표준 입출력 라이브러리 (printf 등 사용)
#include <conio.h>       // 콘솔에서 키 입력(_kbhit, getch) 처리
#include <windows.h>     // Sleep() 함수, system("cls") 함수 사용
#include <time.h>        // 시간 측정을 위한 clock() 함수 사용

// ANSI 색상 변경 함수
// 터미널에서 텍스트 색상을 변경하기 위한 함수
void setTextColor(int color) {
    printf("\033[%dm", color);
}

// ANSI Escape Code로 콘솔 커서 이동 함수
// (x, y) 좌표로 커서를 이동시켜서 원하는 위치에 출력하도록 함
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    // 알파벳 배열: 출력할 알파벳들
    char letters[] = { 'v', 'w', 'x', 'y', 'z' };

    int score = 0;     // 정답 맞춘 횟수
    int fail = 0;      // 오답 횟수
    int index = 0;     // 현재 출력할 알파벳 인덱스

    // 프로그램 시작 시간 저장
    clock_t lastTime = clock();

    // 콘솔 화면 초기화 (화면을 깨끗하게 지움)
    system("cls");

    // 알파벳 5개를 모두 출력할 때까지 반복
    while (index < 5) {
        // 현재 시간에서 마지막 출력 시간까지 경과한 시간(ms) 계산
        double elapsed = (clock() - lastTime) * 1000.0 / CLOCKS_PER_SEC;

        // 1초마다 알파벳 출력
        if (elapsed >= 1000) {
            // 커서를 (1,1)로 이동
            gotoxy(1, 1);

            // 현재 알파벳 출력
            printf("문자 입력: %c  ", letters[index]);

            // 기준 시간(lastTime)을 현재 시각으로 갱신
            lastTime = clock();
        }

        // 키 입력이 있는지 확인 (_kbhit()는 키가 눌렸는지 여부 반환)
        if (_kbhit()) {
            // 키보드에서 입력 문자 읽기
            char input = getch();

            // (1,2) 위치에 사용자가 입력한 문자 출력
            gotoxy(1, 2);
            printf("입력: %c ", input);

            // (1,3) 위치에 정답/오답 여부 출력
            gotoxy(1, 3);
            if (input == letters[index]) {
                // 입력이 현재 알파벳과 일치하면 정답 처리
                setTextColor(32);  // 초록색
                printf("정답!");
                score++;
            }
            else {
                // 입력이 다르면 오답 처리
                setTextColor(31);  // 빨간색
                printf("오답!");
                fail++;
            }

            // 색상 초기화 (원래 색으로 되돌리기)
            setTextColor(0);

            // 다음 알파벳으로 넘어가기
            index++;

            // 기준 시간(lastTime)을 현재 시각으로 갱신
            // (바로 다음 알파벳 출력까지의 타이머 초기화)
            lastTime = clock();
        }

        // CPU 사용률을 낮추기 위해 10ms 정도 잠깐 쉬기
        Sleep(10);
    }

    // 게임 종료 후 결과 출력
    gotoxy(1, 5);
    setTextColor(33);  // 노란색
    printf("=== 결과 ===");

    gotoxy(1, 6);
    printf("정답: %d", score);

    gotoxy(1, 7);
    printf("오답: %d", fail);

    // 색상 초기화
    setTextColor(0);

    printf("\n");

    return 0;
}


/*
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// ===== 함수 선언 =====
void setTextColor(int color) {
    printf("\033[%dm", color);
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// ===== 메인 함수 =====
int main() {
    // 알파벳 배열: 문제에 따라 문자 변경 가능
    char letters[] = { 'v', 'w', 'x', 'y', 'z' };

    // 상태 변수
    int score = 0;     // 맞춘 횟수
    int fail = 0;      // 틀린 횟수
    int index = 0;     // 현재 알파벳 인덱스

    clock_t lastTime = clock();  // 알파벳 출력 간격 측정

    system("cls");  // 화면 초기화

    // 메인 루프: 알파벳 5개 출력 후 종료
    while (index < 5) {
        double elapsed = (clock() - lastTime) * 1000.0 / CLOCKS_PER_SEC;

        // 알파벳 출력 (1초마다)
        if (elapsed >= 1000) {
            gotoxy(1, 1);
            printf("문자 입력: %c  ", letters[index]);
            lastTime = clock();
        }

        // 키 입력 처리
        if (_kbhit()) {
            char input = getch();

            // 입력 문자 출력
            gotoxy(1, 2);
            printf("입력: %c ", input);

            // 정답/오답 판정
            gotoxy(1, 3);
            if (input == letters[index]) {
                setTextColor(32);  // 초록색
                printf("정답!");
                score++;
            } else {
                setTextColor(31);  // 빨간색
                printf("오답!");
                fail++;
            }
            setTextColor(0);  // 색상 초기화

            index++;  // 다음 알파벳으로 넘어감
            lastTime = clock();  // 출력 시간 초기화
        }

        Sleep(10);  // CPU 과부하 방지
    }

    // 결과 출력
    gotoxy(1, 5);
    setTextColor(33);
    printf("=== 결과 ===");
    gotoxy(1, 6);
    printf("정답: %d", score);
    gotoxy(1, 7);
    printf("오답: %d", fail);
    setTextColor(0);
    printf("\n");

    return 0;
}
*/

/* 이 템플릿을 시험장에서 이렇게 활용해봐!
문제 조건
- 알파벳 배열(letters[])만 바꿔서 원하는 알파벳으로 교체
- 배열 크기(5)도 상황에 맞게 수정

색상 출력
- setTextColor() 함수로 색상 변경 (31=빨강, 32=초록, 33=노랑)

키 입력 처리
- _kbhit() + getch() 구조 그대로 유지
- 비교문(input == letters[index])에서 문제 조건에 따라 대소문자 처리 추가 가능

타이밍 처리
- clock()으로 경과 시간 체크 후 1000ms(1초)마다 알파벳 출력
- Sleep(10) 꼭 추가해서 CPU 과부하 방지하기

루프 조건
- index < 5 → 5개 알파벳 출력 후 종료(배열 크기에 따라 변경 가능)

시험장에서 활용하는 법
- 문제에서 “1초마다 알파벳 출력” 요구 시 → clock() 부분 유지
- 알파벳 배열만 교체 후 바로 사용
- 정답/오답 판정 로직 → 그대로 사용
- gotoxy()로 화면 출력 → 그대로 사용

최종 팁
- letters[], index < 5, clock() 부분만 바꾸면 웬만한 예상문제는 이 구조로 다 풀 수 있다
- Sleep(10) 꼭 추가해서 CPU 과부하 방지하기
*/
