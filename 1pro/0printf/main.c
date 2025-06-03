#include <stdio.h>

/* printf 에서 사용하는 Escape Sequence

\n ? 새 줄 (Line Feed)
출력 후 커서를 다음 줄로 이동시킵니다.

\t ? 탭 (Horizontal Tab)
출력에서 탭 간격을 삽입합니다.

\r ? 캐리지 리턴 (Carriage Return)
커서를 현재 줄의 시작으로 이동시키지만 줄 바꿈은 하지 않습니다.

\b ? 백스페이스 (Backspace)
이전 문자위치로 커서를 이동합니다.

\\ ? 백슬래시 (Backslash)
백슬래시 자체를 출력합니다.

\' ? 작은 따옴표 (Single Quote)
작은 따옴표(')를 출력합니다.

\" ? 큰 따옴표 (Double Quote)
큰 따옴표(")를 출력합니다.

\a ? 경고음 (Alert, Bell)
시스템 경고음을 울립니다.

\v ? 수직 탭 (Vertical Tab)
수직 방향으로 탭 간격을 삽입합니다.

\f ? 폼 피드 (Form Feed)
새로운 페이지로 넘깁니다.

\0 ? 널 문자 (Null Character)
문자열의 끝을 나타냅니다.
*/


int main()
{
	puts("이히힛\\");
	puts("\"이히힛\"");
	puts("\a이히힛\\");
	puts("이히힛\n");
	puts("이히힛\f");
	printf("\t으아아아아\n");
	printf("\v으아아아아\n");
	printf("으아아아아\b\b응?");
	printf("\r으하하");

	char a = 'a';
	char n = '\n';
	char c[40] = "문자열문자열";

	printf("\n%s", c);

	return 0;
}


#include <stdio.h>

int main() {
    int i = 0;  // 변수 i를 0으로 초기화

    // 프로그램 안내 출력
    printf("== while문과 if-else문의 예제 ==\n");

    // while문: i가 5보다 작을 동안 반복
    while (i < 5) {
        // 현재 i 값 출력
        printf("현재 i 값: %d\n", i);

        // if-else문: i가 짝수인지 홀수인지 판별
        if (i % 2 == 0) {
            // i가 짝수이면 출력
            printf("i는 짝수입니다!\n");
        }
        else {
            // i가 홀수이면 출력
            printf("i는 홀수입니다!\n");
        }

        // i 값 증가 (다음 반복을 위해)
        i++;
    }

    // 프로그램 종료 메시지 출력
    printf("== 프로그램 종료 ==\n");

    // 프로그램 종료
    return 0;
}
