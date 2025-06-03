#include <stdio.h>
#include <time.h>

/*
    [C ¾ğ¾î ±âº» ÀÚ·áÇü ¼³¸í]

    - int       : Á¤¼öÇü. º¸Åë 4¹ÙÀÌÆ®. ¿¹: 1, -3, 42
    - long      : ´õ Å« ¹üÀ§ÀÇ Á¤¼ö. º¸Åë 4~8¹ÙÀÌÆ®. ¿¹: 1000000000L
    - float     : ´ÜÁ¤µµ ½Ç¼öÇü (¼Ò¼öÁ¡). º¸Åë 4¹ÙÀÌÆ®. ¿¹: 3.14f
    - double    : ¹èÁ¤µµ ½Ç¼öÇü. º¸Åë 8¹ÙÀÌÆ®. ¿¹: 3.141592
    - char      : ¹®ÀÚÇü. 1¹ÙÀÌÆ®. ¿¹: 'a', 'Z'
    - void      : ¹İÈ¯ °ªÀÌ ¾øÀ½À» ³ªÅ¸³¿. ¿¹: void ÇÔ¼ö()
    - clock_t   : ½Ã°£ ÃøÁ¤À» À§ÇÑ Å¸ÀÔ. Á¤¼öÇü ±â¹İÀÌ¸ç <time.h>¿¡¼­ Á¤ÀÇµÊ
*/

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    clock_t start, end;       // ½ÃÀÛ°ú ³¡ ½Ã°£ ÀúÀå¿ë º¯¼ö
    double cpu_time_used;     // °æ°ú ½Ã°£ (ÃÊ) ÀúÀå¿ë º¯¼ö

    start = clock();          // ÇöÀç CPU ½Ã°£À» ½ÃÀÛ ½Ã°£À¸·Î ÀúÀå

    int i = 0;
    // ¿¹½Ã ÀÛ¾÷: ½Ã°£ÀÌ Á¶±İ °É¸®´Â ·çÇÁ (½Ã°£ ÃøÁ¤À» À§ÇÑ ´õ¹Ì ÀÛ¾÷)
    while (i < 100000)
    {
        moveCursor(0, 0);
        printf("À¸È÷È÷ÆR %d\n", i);
        i = i + 1;
    }

    end = clock();            // ÇöÀç CPU ½Ã°£À» ³¡ ½Ã°£À¸·Î ÀúÀå

    // °æ°ú ½Ã°£ °è»ê (Æ½ ¼ö Â÷ÀÌ / ÃÊ´ç Æ½ ¼ö)
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nÀÛ¾÷¿¡ °É¸° ½Ã°£: %.3fÃÊ\n", cpu_time_used);  // °á°ú Ãâ·Â

    return 0;
}


/* 11°­ printf 2¹øÂ° */

/* ÀÚ·áÇü (Primitive Types)
	* Á¤¼öÇü
	int				4byte Á¤¼öÇü
	long			8byte ±ä Á¤¼ö
	long long		8byte ¸Å¿ì ±äÁ¤¼ö
	short			2byte ÀÛÀº Á¤¼ö
	unsigned (Á¤¼öÇü)	  ÀÌ Å°¿öµå¸¦ ¾Õ¿¡ ºÙÀÌ¸é ¾çÀÇ Á¤¼ö¸¸ »ç¿ë
		¿¹½Ã > unsigned int ¾çÀÇÁ¤¼ö

	* ¹®ÀÚÇü
	char			1byte ¹®ÀÚÇü
	signed			1byte ºÎÈ£°¡ ÀÖ´Â 8ºñÆ® Á¤¼ö (-127~128)
	unsigned		1byte ºÎÈ£°¡ ¾ø´Â 8ºñÆ® Á¤¼ö (0~255)

	* ½Ç¼öÇü
	float			4byte ½Ç¼öÇü(floating point number)
	double			8byte Å«½Ç¼ö
	long double		16byte ¸Å¿ìÅ«¹üÀ§ ½Ç¼ö

	* Æ¯¼öÀÚ·áÇü (no type)
	void			¹İÈ¯°ªÀÌ ¾ø´Ù.
	void *			(¾î¶²Å¸ÀÔÀÌ´ø ÀúÀå °¡´É)¸Ş¸ğ¸®ÁÖ¼Ò°ªÀ» ÀúÀå

	* Ç¥ÁØ Ãß°¡ ÀÚ·áÇü°ü·Ã Çì´õÆÄÀÏ
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

//°¡º¯ÀÎÀÚ ¿¹½Ã
int sum(int count, ...)
{
	int total = 0;

	va_list	args;		//°¡º¯ÀÎÀÚ ¸®½ºÆ®
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
	hp = (int)add(10, -3);//Çüº¯È¯

	/*format specifiers (Çü½Ä ÁöÁ¤ÀÚ) »ç¿ë (%)
	 *
	 * %d, %i	: Á¤¼öÇü (decimal(½ÊÁø¼ö) / integer)
	 * %x,%X	: Á¤¼öÇü (16Áø¼ö : ´ë¼Ò¹®ÀÚ¸¦ ±¸ºĞ)
	 * %o		: Á¤¼öÇü (8Áø¼ö)
	 * %f,%lf   : ½Ç¼öÇü
	 * %e,%E	: Áö¼öÇü
	 * %g,%G	: Áö¼öÇü
	 * %c		: ¹®ÀÚÇü
	 * %s		: ¹®ÀÚ¿­Çü
	 * %p		: ÁÖ¼Ò°ª
	 */
	printf("HP = %i\n", 7);
	printf("%c%c = %i\n", 'H', 80, 7);
	printf("´©Àû µ¥¹ÌÁö = %i\n", sum(5, 1, 2, 3, 4, 5));	//Çü½ÄÁöÁ¤ÀÚ ¿¹½Ã
	printf("ÀÌ¸§ : %s", "¸¶¹ı»ç");

	float fl = 0.342;
	double dl = 0.0201;

	printf("´ç½ÅÀÇ ¸Å·Â: %f\n", fl);
	printf("´ç½ÅÀÇ ¸Å·Â: %lf\n", dl);
	printf("´ç½ÅÀÇ ¸Å·Â: %e\n", dl);
	printf("´ç½ÅÀÇ ¸Å·Â: %E\n", dl);

	int attack = 31;
	printf("´ç½ÅÀÇ ¹«·Â: %d\n", attack);
	printf("´ç½ÅÀÇ ¹«·Â: Ox%x\n", attack);
	printf("´ç½ÅÀÇ ¹«·Â: Ox%X\n", attack);
	printf("´ç½ÅÀÇ ¹«·ÂÁÖ¼Ò: %p\n", &attack);

	void* attack_address = &attack;
	printf("´ç½ÅÀÇ ¹«·ÂÁÖ¼Ò: %d\n", *(int*)attack_address);

	return 0;
}