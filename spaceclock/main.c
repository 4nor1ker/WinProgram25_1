#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#pragma comment(lib, "Opengl32.lib")

#define PI 3.1415926535f  // ������ ��� ����

// --- ������ �ð�� 7-���׸�Ʈ ���� ---
// 0~9 ���ڿ� �����ϴ� ���� ���� (7-���׸�Ʈ)
const int SEG_MAP[10] = {
    0b1111110,  // 0
    0b0110000,  // 1
    0b1101101,  // 2
    0b1111001,  // 3
    0b0110011,  // 4
    0b1011011,  // 5
    0b1011111,  // 6
    0b1110000,  // 7
    0b1111111,  // 8
    0b1111011   // 9
};

// �� �� (x1, y1) �� (x2, y2)�� �մ� ������ �׸��� �Լ�
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Ư�� ��ġ�� ������ ���� �� �ڸ��� �׸��� �Լ�
// digit: �׸� ����, x: ���� ���� x ��ǥ, baselineY: ���׸�Ʈ ���� y ��ǥ,
// segLen: ���׸�Ʈ ����, segOff: ���׸�Ʈ ���� ������
void drawDigit(int digit, float x, float baselineY, float segLen, float segOff) {
    int segs = SEG_MAP[digit];
    glLineWidth(3.0f);
    glColor3f(0.08f, 0.16f, 0.4f);  // ���׸�Ʈ ���� ����
    // �� ��Ʈ�� ���� ��쿡 �ش� ���׸�Ʈ �׸���
    if (segs & (1 << 6)) drawLine(x, baselineY + 2 * segOff, x + segLen, baselineY + 2 * segOff);
    if (segs & (1 << 5)) drawLine(x + segLen, baselineY + 2 * segOff, x + segLen, baselineY + segOff);
    if (segs & (1 << 4)) drawLine(x + segLen, baselineY + segOff, x + segLen, baselineY);
    if (segs & (1 << 3)) drawLine(x, baselineY, x + segLen, baselineY);
    if (segs & (1 << 2)) drawLine(x, baselineY, x, baselineY + segOff);
    if (segs & (1 << 1)) drawLine(x, baselineY + segOff, x, baselineY + 2 * segOff);
    if (segs & (1 << 0)) drawLine(x, baselineY + segOff, x + segLen, baselineY + segOff);
}

// ���� ä�� �׸��� �Լ�
// cx, cy: �߽� ��ǥ, r: ������, segments: �ٰ��� �ٻ� ���� ��, red/green/blue: ����
void draw_circle(float cx, float cy, float r, int segments, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(cx + cosf(angle) * r, cy + sinf(angle) * r);
    }
    glEnd();
}

// ���� �ܰ����� �׸��� �Լ�
void draw_circle_outline(float cx, float cy, float r, int segments, float red, float green, float blue, float width) {
    glLineWidth(width);
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(cx + cosf(angle) * r, cy + sinf(angle) * r);
    }
    glEnd();
}

// �ð� ���� ǥ�� (ª��/�� ����)
// count: ���� ��, inner_radius: ���� ���� ������, outer_radius: �ٱ� �� ������
void draw_tick_marks(int count, float inner_radius, float outer_radius, float r, float g, float b, float width) {
    glLineWidth(width);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    for (int i = 0; i < count; ++i) {
        float angle = 2.0f * PI * i / count;
        glVertex2f(cosf(angle) * inner_radius, sinf(angle) * inner_radius);
        glVertex2f(cosf(angle) * outer_radius, sinf(angle) * outer_radius);
    }
    glEnd();
}

// �� ����� �׸��� �Լ� (�ﰢ�� ���̾� 2��)
void draw_star(float cx, float cy, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    for (int layer = 0; layer < 2; ++layer) {
        float rot = (layer == 1) ? PI / 3.0f : 0.0f;
        for (int j = 0; j < 3; ++j) {
            float a = 2.0f * PI * j / 3.0f + rot;
            float na = 2.0f * PI * (j + 1) / 3.0f + rot;
            glVertex2f(cx, cy);
            glVertex2f(cx + cosf(a) * radius, cy + sinf(a) * radius);
            glVertex2f(cx + cosf(na) * radius, cy + sinf(na) * radius);
        }
    }
    glEnd();
}

// �ʽ´� ����� �׸��� �Լ�
void draw_crescent(float cx, float cy, float r, float angle_deg) {
    float rad = angle_deg * PI / 180.0f;
    // �ܰ���
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float a = 2.0f * PI * i / 100;
        float x = cosf(a) * r, y = sinf(a) * r;
        glVertex2f(cx + cosf(rad) * x - sinf(rad) * y,
            cy + sinf(rad) * x + cosf(rad) * y);
    }
    glEnd();
    // ���κ� (�������� ���ļ� �ʽ´� ǥ��)
    glColor3f(0.188f, 0.2f, 0.251f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float a = 2.0f * PI * i / 100;
        float x = cosf(a) * r * 0.8f + 0.01f, y = sinf(a) * r * 0.8f;
        glVertex2f(cx + cosf(rad) * x - sinf(rad) * y,
            cy + sinf(rad) * x + cosf(rad) * y);
    }
    glEnd();
}

// ��Ʈ ����� �׸��� �Լ�
void draw_heart_shape(float cx, float cy, float size) {
    glColor3f(0.2f, 0.6f, 0.3f);
    float rr = size * 0.4f;
    // �¿� �� �� ��
    draw_circle(cx - rr, cy, rr, 40, 0.2f, 0.6f, 0.3f);
    draw_circle(cx + rr, cy, rr, 40, 0.2f, 0.6f, 0.3f);
    // �Ʒ� �ﰢ��
    glBegin(GL_TRIANGLES);
    glVertex2f(cx - rr * 2, cy);
    glVertex2f(cx + rr * 2, cy);
    glVertex2f(cx, cy - rr * 2.8f);
    glEnd();
}

// ����ó�� ���̴� ������ ��Ʈ ��� �߰�
void draw_earth_like_circle(float cx, float cy, float r) {
    draw_circle(cx, cy, r, 360, 0.204f, 0.722f, 1.0f);
    draw_heart_shape(cx - r * 0.3f, cy + r * 0.25f, r * 0.28f);
    draw_heart_shape(cx + r * 0.3f, cy - r * 0.25f, r * 0.28f);
}

// �¾� ��� (����) �׸��� �Լ�
void draw_sun(float cx, float cy, float innerR, float outerR, int rays, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < rays; ++i) {
        float a1 = 2.0f * PI * i / rays;
        float a2 = 2.0f * PI * (i + 1) / rays;
        glVertex2f(cx + cosf(a1) * innerR, cy + sinf(a1) * innerR);
        glVertex2f(cx + cosf((a1 + a2) * 0.5f) * outerR, cy + sinf((a1 + a2) * 0.5f) * outerR);
        glVertex2f(cx + cosf(a2) * innerR, cy + sinf(a2) * innerR);
    }
    glEnd();
}

// �ð� �ٴ� �׸��� �Լ�
// tip_style: 1=ū ��, 2=���� ��, 3=�ʽ´�
void draw_hand(float cx, float cy, float angle_deg, float length,
    float r, float g, float b, float width, int tip_style) {
    float rad = angle_deg * PI / 180.0f;
    float x = cx + cosf(rad) * length;
    float y = cy + sinf(rad) * length;
    glLineWidth(width);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(x, y);
    glEnd();
    // �ٴ� �� ��Ÿ�� �׸���
    if (tip_style == 1)      draw_star(x, y, 0.039375f, 1.0f, 0.992f, 0.447f);
    else if (tip_style == 2) draw_star(x, y, 0.03f, 1.0f, 0.992f, 0.447f);
    else if (tip_style == 3) draw_crescent(x, y, 0.035f, angle_deg);
}

int main() {
    // GLFW �ʱ�ȭ �� â ����
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Clock with Custom & Digital", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // ���� �� ��ǥ�� ����
    glClearColor(1, 1, 1, 1);
    glOrtho(-1.333f, 1.333f, -1, 1, -1, 1);

    // �⺻ ���� �ʱ�ȭ
    float outerR = 0.8f;           // �ð� �ܰ� ������
    float segLen = 0.05f, segOff = 0.05f, gap = segLen * 0.5f;
    float digitalY = outerR * 0.6f; // ������ �ð� Y ��ġ
    float baselineY = digitalY - segOff;

    // ������ ���� ��ġ ���� �� ũ��
    float cell = segLen * 1.5f;
    float xHT = -cell * 1.5f;  // ��(hour) ���� �ڸ� X
    float xHO = -cell * 0.5f;  // ��(hour) ���� �ڸ� X
    float xMT = cell * 0.5f;   // ��(minute) ���� �ڸ� X
    float xMO = cell * 1.5f;   // ��(minute) ���� �ڸ� X
    float xColon = 0.0f;       // �ݷ� X
    float sqSize = 0.01f;      // �ݷ� �� ũ��

    // �¾� ���� �� ũ��
    const float sunInner = 0.055f;
    const float sunOuter = 0.075f;
    const int   sunRays = 12;
    const float sunR = 1.0f, sunG = 0.2f, sunB = 0.4f;

    while (!glfwWindowShouldClose(window)) {
        // ���� �ð� �б�
        time_t raw = time(NULL);
        struct tm* t = localtime(&raw);
        int hour = t->tm_hour, minute = t->tm_min, second = t->tm_sec;

        // �ٴ� ���� ��� (12�� ���� 90��)
        float secA = 90.0f - 6.0f * second;
        float minA = 90.0f - 6.0f * (minute + second / 60.0f);
        float hourA = 90.0f - 30.0f * ((hour % 12) + minute / 60.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        // �ð� ���̽� �׸���: ��� ��, �ܰ���, ����, ���� ��� ���
        draw_circle(0, 0, outerR, 360, 0.188f, 0.2f, 0.251f);
        draw_circle_outline(0, 0, outerR, 360, 0.843f, 0.902f, 1.0f, 24.0f);
        draw_tick_marks(60, 0.76f, outerR, 0.7f, 0.7f, 0.75f, 1.0f);
        draw_tick_marks(12, 0.7f, outerR, 0.7f, 0.7f, 0.75f, 2.5f);
        draw_earth_like_circle(0.4f, 0, 0.2f);

        // ��ħ, ��ħ, ��ħ �׸���
        draw_hand(0, 0, hourA, 0.4f, 1.0f, 0.992f, 0.447f, 6.0f, 1);
        draw_hand(0, 0, minA, 0.6f, 1.0f, 0.992f, 0.447f, 4.0f, 2);
        draw_hand(0.4f, 0, secA, 0.23f, 1, 1, 1, 2.5f, 3);

        // �ٴ� �߽ɿ� �¾� ��� �߰�
        draw_sun(0, 0, sunInner, sunOuter, sunRays, sunR, sunG, sunB);
        draw_circle(0, 0, sunInner * 0.75f, 40, sunR, sunG, sunB);

        // ������ �ð� ��� �簢�� �׸���
        glColor3f(1, 1, 1);
        float rectL = -(xMO + segLen + gap);
        float rectR = (xMO + segLen + gap);
        float rectB = baselineY - gap;
        float rectT = baselineY + 2 * segOff + gap;
        glBegin(GL_QUADS);
        glVertex2f(rectL, rectB);
        glVertex2f(rectR, rectB);
        glVertex2f(rectR, rectT);
        glVertex2f(rectL, rectT);
        glEnd();
        // ������ �׵θ� �׸���
        glColor3f(0.08f, 0.16f, 0.4f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(rectL, rectB);
        glVertex2f(rectR, rectB);
        glVertex2f(rectR, rectT);
        glVertex2f(rectL, rectT);
        glEnd();

        // ������ ���� �� �ݷ� �׸���
        float dxL = -gap * 2.8f, dxR = -gap * 0.8f;
        drawDigit(hour / 10, xHT + dxL, baselineY, segLen, segOff);
        drawDigit(hour % 10, xHO + dxL, baselineY, segLen, segOff);
        // �ݷ� �� �� ��
        {
            float dotR = sqSize * 0.8f;
            draw_circle(xColon + dxR, baselineY + segOff * 1.5f, dotR, 40, 0.08f, 0.16f, 0.4f);
            draw_circle(xColon + dxR, baselineY + segOff * 0.5f, dotR, 40, 0.08f, 0.16f, 0.4f);
        }
        drawDigit(minute / 10, xMT + dxR, baselineY, segLen, segOff);
        drawDigit(minute % 10, xMO + dxR, baselineY, segLen, segOff);

        // ���� ��ȯ �� �̺�Ʈ ó��
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW ����
    glfwTerminate();
    return 0;
}