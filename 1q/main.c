// 예상문제

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// ANSI 색상 변경 함수 (31=빨강, 32=초록, 33=노랑)
void setTextColor(int color) {
    printf("\033[%dm", color);
}

// ANSI Escape Code로 커서 이동 함수
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    // 출력할 알파벳 배열
    char letters[] = { 'v', 'w', 'x', 'y', 'z' };

    // 게임 상태 변수
    int shown = 0;       // 출력된 알파벳 개수 (0~4)
    int current = -1;    // 현재 화면에 출력된 알파벳 인덱스 (-1이면 아직 없음)
    int correct = 0;     // 맞춘 알파벳 개수
    int wrong = 0;       // 틀린 알파벳 개수

    // 알파벳 출력 간격 체크용
    clock_t last = clock();  // 알파벳 출력 직전 시간(ms)

    system("cls");  // 콘솔 화면 초기화

    // 입력 받은 횟수(정답+오답)가 5가 될 때까지 반복
    while (correct + wrong < 5) {
        // 현재 시간에서 마지막 출력 시간을 뺀 경과 시간(ms)
        double elapsed = (clock() - last) * 1000.0 / CLOCKS_PER_SEC;

        // 1초마다 알파벳 출력
        if (shown < 5 && elapsed >= 1000) {
            current = shown;  // 현재 출력 알파벳 인덱스
            gotoxy(1, 1);     // 첫 줄로 이동
            printf("문자 입력: %c  ", letters[current]);
            shown++;          // 출력된 알파벳 수 증가
            last = clock();   // 출력 시간 초기화
        }

        // 키 입력이 있으면 처리
        if (_kbhit()) {
            char ch = getch();  // 입력 문자(ASCII 코드)

            // 2번째 줄에 입력 문자 출력
            gotoxy(1, 2);
            printf("%c ", ch);

            // 3번째 줄에 판정 출력
            gotoxy(1, 3);
            if (current >= 0 && ch == letters[current]) {
                // 입력이 현재 알파벳과 같으면 정답 처리
                setTextColor(32);  // 초록색
                printf("완벽!!!");
                correct++;
            }
            else {
                // 입력이 틀렸으면 오답 처리
                setTextColor(31);  // 빨간색
                printf("에러!!!");
                wrong++;
            }
            setTextColor(0);  // 색상 초기화
        }

        Sleep(10);  // CPU 과부하 방지용 (10ms 대기)
    }

    // 결과 출력
    gotoxy(1, 5);
    setTextColor(33);  // 노란색
    printf("=== 결과 ===");
    gotoxy(1, 6);
    printf("정답: %d", correct);
    gotoxy(1, 7);
    printf("오답: %d", wrong);
    setTextColor(0);
    printf("\n");

    return 0;
}


/*#include <stdio.h>
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
    // 🔹 알파벳 배열: 문제에 따라 문자 변경 가능
    char letters[] = { 'v', 'w', 'x', 'y', 'z' };
    
    // 🔹 상태 변수
    int shown = 0;       // 출력된 알파벳 개수
    int current = -1;    // 현재 출력 중인 알파벳 인덱스
    int correct = 0;     // 맞춘 횟수
    int wrong = 0;       // 틀린 횟수
    clock_t last = clock();  // 알파벳 출력 간격 측정

    system("cls");  // 화면 초기화

    // 🔹 메인 루프: 정답+오답 합계가 5가 될 때까지 반복
    while (correct + wrong < 5) {
        double elapsed = (clock() - last) * 1000.0 / CLOCKS_PER_SEC;

        // 🔹 알파벳 출력 (1초마다)
        if (shown < 5 && elapsed >= 1000) {
            current = shown;
            gotoxy(1, 1);
            printf("문자 입력: %c  ", letters[current]);
            shown++;
            last = clock();
        }

        // 🔹 키 입력 처리
        if (_kbhit()) {
            char ch = getch();

            // 입력 문자 출력
            gotoxy(1, 2);
            printf("%c ", ch);

            // 정답/오답 판정
            gotoxy(1, 3);
            if (current >= 0 && ch == letters[current]) {
                setTextColor(32);  // 초록색
                printf("완벽!!!");
                correct++;
            } else {
                setTextColor(31);  // 빨간색
                printf("에러!!!");
                wrong++;
            }
            setTextColor(0);  // 색상 초기화
        }

        Sleep(10);  // CPU 과부하 방지
    }

    // 🔹 결과 출력
    gotoxy(1, 5);
    setTextColor(33);
    printf("=== 결과 ===");
    gotoxy(1, 6);
    printf("정답: %d", correct);
    gotoxy(1, 7);
    printf("오답: %d", wrong);
    setTextColor(0);
    printf("\n");

    return 0;
}
*/

/*📌 이 템플릿을 시험장에서 이렇게 활용해봐!
✅ 문제 조건

알파벳 배열(letters[])만 바꿔서 원하는 알파벳으로 교체

배열 개수(5)도 상황에 맞게 변경

✅ 색상 출력

setTextColor() 함수로 색상 변경 (31=빨강, 32=초록, 33=노랑)

✅ 키 입력 처리

_kbhit() + getch() 구조 그대로 유지

비교문(ch == letters[current])에서 문제 조건에 따라 대소문자 처리 추가 가능

✅ 타이밍 처리

clock()으로 경과 시간 체크 후 1000ms(1초)마다 알파벳 출력

게임 루프(while) 구조 유지, 문제에 따라 반복 조건만 수정 가능

📝 시험장에서 활용하는 법
✅ 문제에서 “1초마다 알파벳 출력” 요구 시 → clock() 사용 부분 유지
✅ 알파벳 배열만 교체 후 바로 적용
✅ 정답/오답 판정 로직 → 그대로 사용
✅ 화면 출력(gotoxy()) → 그대로 사용

🎯 최종 팁
‘letters[]’, ‘correct + wrong < 5’, ‘clock()’ 부분만 바꾸면 웬만한 예상문제는 이 구조로 다 풀 수 있어요!

다른 문제에서도 이 구조를 참고해서 빠르게 풀 수 있어요!

Sleep(10) 꼭 추가해서 CPU 과부하 방지하기!

*/