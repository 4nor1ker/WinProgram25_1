#include <stdio.h>
#include <time.h>
#include <windows.h>  // Sleep ÇÔ¼ö »ç¿ëÀ» À§ÇÑ Çì´õ (Windows Àü¿ë)

#define FPS 60                        // ¸ñÇ¥ ÇÁ·¹ÀÓ ¼ö (60 FPS)
#define FRAME_TIME (1000 / FPS)      // ÇÑ ÇÁ·¹ÀÓ¿¡ ¼Ò¿äµÇ¾î¾ß ÇÒ ½Ã°£ (¹Ğ¸®ÃÊ ´ÜÀ§, 16.67ms Á¤µµ)

int moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

int main() {
    int frameNum = 0;
    while (1) {  // ¹«ÇÑ ·çÇÁ: °ÔÀÓ ·çÇÁ ½ÇÇà
        clock_t frameStart = clock();  // ÇöÀç ½Ã°£ ÀúÀå (ÇÁ·¹ÀÓ ½ÃÀÛ ½Ã°£)

        // --- °ÔÀÓ ·ÎÁ÷ ¾÷µ¥ÀÌÆ® ¹× ·»´õ¸µ Ã³¸® ºÎºĞ ---
        moveCursor(0, 0);
        printf("°ÔÀÓ ÇÁ·¹ÀÓ %d¹ø Ã³¸®\n", frameNum);
        frameNum = frameNum + 1;
        // ------------------------------------------------

        clock_t frameEnd = clock();  // ÇÁ·¹ÀÓ ÀÛ¾÷ ¿Ï·á ÈÄ ÇöÀç ½Ã°£ ÀúÀå

        // ÇÁ·¹ÀÓ Ã³¸®¿¡ °É¸° ½Ã°£ °è»ê (¹Ğ¸®ÃÊ ´ÜÀ§·Î È¯»ê)
        double elapsed = (double)(frameEnd - frameStart) * 1000 / CLOCKS_PER_SEC;

        // ÇÁ·¹ÀÓÀÌ ³Ê¹« »¡¸® ³¡³µÀ¸¸é ³²Àº ½Ã°£¸¸Å­ ´ë±â
        if (elapsed < FRAME_TIME) {
            Sleep((DWORD)(FRAME_TIME - elapsed));  // ¹Ğ¸®ÃÊ ´ÜÀ§·Î ´ë±â
        }
        // ÇÁ·¹ÀÓÀÌ ¿À·¡ °É·È´Ù¸é ´ë±âÇÏÁö ¾Ê°í ¹Ù·Î ´ÙÀ½ ÇÁ·¹ÀÓ ½ÃÀÛ
    }

    return 0;
}

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