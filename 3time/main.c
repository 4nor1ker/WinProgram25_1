#include <stdio.h>
#include <time.h>

/*
    [C ��� �⺻ �ڷ��� ����]

    - int       : ������. ���� 4����Ʈ. ��: 1, -3, 42
    - long      : �� ū ������ ����. ���� 4~8����Ʈ. ��: 1000000000L
    - float     : ������ �Ǽ��� (�Ҽ���). ���� 4����Ʈ. ��: 3.14f
    - double    : ������ �Ǽ���. ���� 8����Ʈ. ��: 3.141592
    - char      : ������. 1����Ʈ. ��: 'a', 'Z'
    - void      : ��ȯ ���� ������ ��Ÿ��. ��: void �Լ�()
    - clock_t   : �ð� ������ ���� Ÿ��. ������ ����̸� <time.h>���� ���ǵ�
*/

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;       // ���۰� �� �ð� ����� ����
    double cpu_time_used;     // ��� �ð� (��) ����� ����

    start = clock();          // ���� CPU �ð��� ���� �ð����� ����

    int i = 0;
    // ���� �۾�: �ð��� ���� �ɸ��� ���� (�ð� ������ ���� ���� �۾�)
    while (i < 100000)
    {
        moveCursor(0, 0);
        printf("�������R %d\n", i);
        i = i + 1;
    }

    end = clock();            // ���� CPU �ð��� �� �ð����� ����

    // ��� �ð� ��� (ƽ �� ���� / �ʴ� ƽ ��)
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n�۾��� �ɸ� �ð�: %.3f��\n", cpu_time_used);  // ��� ���

    return 0;
}


/* 11�� printf 2��° */

/* �ڷ��� (Primitive Types)
	* ������
	int				4byte ������
	long			8byte �� ����
	long long		8byte �ſ� ������
	short			2byte ���� ����
	unsigned (������)	  �� Ű���带 �տ� ���̸� ���� ������ ���
		���� > unsigned int ��������

	* ������
	char			1byte ������
	signed			1byte ��ȣ�� �ִ� 8��Ʈ ���� (-127~128)
	unsigned		1byte ��ȣ�� ���� 8��Ʈ ���� (0~255)

	* �Ǽ���
	float			4byte �Ǽ���(floating point number)
	double			8byte ū�Ǽ�
	long double		16byte �ſ�ū���� �Ǽ�

	* Ư���ڷ��� (no type)
	void			��ȯ���� ����.
	void *			(�Ÿ���̴� ���� ����)�޸��ּҰ��� ����

	* ǥ�� �߰� �ڷ������� �������
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

//�������� ����
int sum(int count, ...)
{
	int total = 0;

	va_list	args;		//�������� ����Ʈ
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
	hp = (int)add(10, -3);//����ȯ

	/*format specifiers (���� ������) ��� (%)
	 *
	 * %d, %i	: ������ (decimal(������) / integer)
	 * %x,%X	: ������ (16���� : ��ҹ��ڸ� ����)
	 * %o		: ������ (8����)
	 * %f,%lf   : �Ǽ���
	 * %e,%E	: ������
	 * %g,%G	: ������
	 * %c		: ������
	 * %s		: ���ڿ���
	 * %p		: �ּҰ�
	 */
	printf("HP = %i\n", 7);
	printf("%c%c = %i\n", 'H', 80, 7);
	printf("���� ������ = %i\n", sum(5, 1, 2, 3, 4, 5));	//���������� ����
	printf("�̸� : %s", "������");

	float fl = 0.342;
	double dl = 0.0201;

	printf("����� �ŷ�: %f\n", fl);
	printf("����� �ŷ�: %lf\n", dl);
	printf("����� �ŷ�: %e\n", dl);
	printf("����� �ŷ�: %E\n", dl);

	int attack = 31;
	printf("����� ����: %d\n", attack);
	printf("����� ����: Ox%x\n", attack);
	printf("����� ����: Ox%X\n", attack);
	printf("����� �����ּ�: %p\n", &attack);

	void* attack_address = &attack;
	printf("����� �����ּ�: %d\n", *(int*)attack_address);

	return 0;
}