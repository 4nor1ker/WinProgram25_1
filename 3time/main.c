#include <stdio.h>
#include <time.h>

/*
    [C 언어 기본 자료형 설명]

    - int       : 정수형. 보통 4바이트. 예: 1, -3, 42
    - long      : 더 큰 범위의 정수. 보통 4~8바이트. 예: 1000000000L
    - float     : 단정도 실수형 (소수점). 보통 4바이트. 예: 3.14f
    - double    : 배정도 실수형. 보통 8바이트. 예: 3.141592
    - char      : 문자형. 1바이트. 예: 'a', 'Z'
    - void      : 반환 값이 없음을 나타냄. 예: void 함수()
    - clock_t   : 시간 측정을 위한 타입. 정수형 기반이며 <time.h>에서 정의됨
*/

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;       // 시작과 끝 시간 저장용 변수
    double cpu_time_used;     // 경과 시간 (초) 저장용 변수

    start = clock();          // 현재 CPU 시간을 시작 시간으로 저장

    int i = 0;
    // 예시 작업: 시간이 조금 걸리는 루프 (시간 측정을 위한 더미 작업)
    while (i < 100000)
    {
        moveCursor(0, 0);
        printf("으히히힣 %d\n", i);
        i = i + 1;
    }

    end = clock();            // 현재 CPU 시간을 끝 시간으로 저장

    // 경과 시간 계산 (틱 수 차이 / 초당 틱 수)
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n작업에 걸린 시간: %.3f초\n", cpu_time_used);  // 결과 출력

    return 0;
}


/* 11강 printf 2번째 */

/* 자료형 (Primitive Types)
	* 정수형
	int				4byte 정수형
	long			8byte 긴 정수
	long long		8byte 매우 긴정수
	short			2byte 작은 정수
	unsigned (정수형)	  이 키워드를 앞에 붙이면 양의 정수만 사용
		예시 > unsigned int 양의정수

	* 문자형
	char			1byte 문자형
	signed			1byte 부호가 있는 8비트 정수 (-127~128)
	unsigned		1byte 부호가 없는 8비트 정수 (0~255)

	* 실수형
	float			4byte 실수형(floating point number)
	double			8byte 큰실수
	long double		16byte 매우큰범위 실수

	* 특수자료형 (no type)
	void			반환값이 없다.
	void *			(어떤타입이던 저장 가능)메모리주소값을 저장

	* 표준 추가 자료형관련 헤더파일
	stdint.h
	stdbool.h
*/
#include <stdio.h>
#include <stdarg.h>

short add(short a, short b)
{
	short c = a + b;
	return c;
}

//가변인자 예시
int sum(int count, ...)
{
	int total = 0;

	va_list	args;		//가변인자 리스트
	va_start(args, count);

	int i = 0;
	while (i < count)
	{
		total = total + va_arg(args, int);
		i = i + 1;
	}

	return total;
}

int main()
{
	int hp;
	hp = (int)add(10, -3);//형변환

	/*format specifiers (형식 지정자) 사용 (%)
	 *
	 * %d, %i	: 정수형 (decimal(십진수) / integer)
	 * %x,%X	: 정수형 (16진수 : 대소문자를 구분)
	 * %o		: 정수형 (8진수)
	 * %f,%lf   : 실수형
	 * %e,%E	: 지수형
	 * %g,%G	: 지수형
	 * %c		: 문자형
	 * %s		: 문자열형
	 * %p		: 주소값
	 */
	printf("HP = %i\n", 7);
	printf("%c%c = %i\n", 'H', 80, 7);
	printf("누적 데미지 = %i\n", sum(5, 1, 2, 3, 4, 5));	//형식지정자 예시
	printf("이름 : %s", "마법사");

	float fl = 0.342;
	double dl = 0.0201;

	printf("당신의 매력: %f\n", fl);
	printf("당신의 매력: %lf\n", dl);
	printf("당신의 매력: %e\n", dl);
	printf("당신의 매력: %E\n", dl);

	int attack = 31;
	printf("당신의 무력: %d\n", attack);
	printf("당신의 무력: Ox%x\n", attack);
	printf("당신의 무력: Ox%X\n", attack);
	printf("당신의 무력주소: %p\n", &attack);

	void* attack_address = &attack;
	printf("당신의 무력주소: %d\n", *(int*)attack_address);

	return 0;
}