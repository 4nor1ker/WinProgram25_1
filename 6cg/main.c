#include <stdio.h>

/* printf ���� ����ϴ� Escape Sequence

\n ? �� �� (Line Feed)
��� �� Ŀ���� ���� �ٷ� �̵���ŵ�ϴ�.

\t ? �� (Horizontal Tab)
��¿��� �� ������ �����մϴ�.

\r ? ĳ���� ���� (Carriage Return)
Ŀ���� ���� ���� �������� �̵���Ű���� �� �ٲ��� ���� �ʽ��ϴ�.

\b ? �齺���̽� (Backspace)
���� ������ġ�� Ŀ���� �̵��մϴ�.

\\ ? �齽���� (Backslash)
�齽���� ��ü�� ����մϴ�.

\' ? ���� ����ǥ (Single Quote)
���� ����ǥ(')�� ����մϴ�.

\" ? ū ����ǥ (Double Quote)
ū ����ǥ(")�� ����մϴ�.

\a ? ����� (Alert, Bell)
�ý��� ������� �︳�ϴ�.

\v ? ���� �� (Vertical Tab)
���� �������� �� ������ �����մϴ�.

\f ? �� �ǵ� (Form Feed)
���ο� �������� �ѱ�ϴ�.

\0 ? �� ���� (Null Character)
���ڿ��� ���� ��Ÿ���ϴ�.
*/


int main()
{
	puts("������\\");
	puts("\"������\"");
	puts("\a������\\");
	puts("������\n");
	puts("������\f");
	printf("\t���ƾƾƾ�\n");
	printf("\v���ƾƾƾ�\n");
	printf("���ƾƾƾ�\b\b��?");
	printf("\r������");

	char a = 'a';
	char n = '\n';
	char c[40] = "���ڿ����ڿ�";

	printf("\n%s", c);

	return 0;
}