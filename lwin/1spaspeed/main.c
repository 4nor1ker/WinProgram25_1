// �¾������� �ӵ� ���� + �ӵ� ���� ǥ��



#include <GLFW/glfw3.h>    // OpenGL �� GLFW ���̺귯��
#include <windows.h>       // GetAsyncKeyState �Լ� ���
#include <math.h>          // �ﰢ�Լ� ���
#include <stdio.h>         // printf �� ������ (�� ������ Ȥ�� ���� ���ܵ�)

#pragma comment(lib, "opengl32.lib")  // OpenGL ���̺귯�� ��ũ ����

#define PI 3.1415926535f   // ������ ��� ����

// ---------------------- [1] 7-segment ���� ���� -------------------------
/*
 * 0 ~ 9���� �� ������ 7-segment ǥ�� ���¸� ��Ʈ������ ������ �迭.
 * �� ��Ʈ�� a,b,c,d,e,f,g ���׸�Ʈ�� �ǹ�.
 */
const unsigned char SEGMENT_MAP[10] = {
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

// ---------------------- [2] 7-segment ���� ��� �Լ� ----------------------
/*
 * ���ڸ� 7-segment ������� OpenGL�� ����ϴ� �Լ�.
 * number: ����� ����(0~9)
 * size: ���׸�Ʈ ��ü ũ��
 */
void draw7Segment(int number, float size) {
    if (number < 0 || number > 9) return;
    unsigned char seg = SEGMENT_MAP[number];

    float x = -size / 2.0f;       // ���� ������
    float y = size / 2.0f;        // ���� ������
    float w = size;               // ���� ���� ũ��
    float h = size / 5.0f;        // ���׸�Ʈ �β�

    // �� ���׸�Ʈ�� ������ ��� (���� ���׸�Ʈ��)
    if (seg & 0b1000000) {  // a: ��� ����
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glEnd();
    }
    if (seg & 0b0100000) {  // b: ������ ��� ����
        glBegin(GL_LINES);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - w / 2.0f);
        glEnd();
    }
    if (seg & 0b0010000) {  // c: ������ �ϴ� ����
        glBegin(GL_LINES);
        glVertex2f(x + w, y - w / 2.0f);
        glVertex2f(x + w, y - w);
        glEnd();
    }
    if (seg & 0b0001000) {  // d: �ϴ� ����
        glBegin(GL_LINES);
        glVertex2f(x, y - w);
        glVertex2f(x + w, y - w);
        glEnd();
    }
    if (seg & 0b0000100) {  // e: ���� �ϴ� ����
        glBegin(GL_LINES);
        glVertex2f(x, y - w / 2.0f);
        glVertex2f(x, y - w);
        glEnd();
    }
    if (seg & 0b0000010) {  // f: ���� ��� ����
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y - w / 2.0f);
        glEnd();
    }
    if (seg & 0b0000001) {  // g: �߾� ����
        glBegin(GL_LINES);
        glVertex2f(x, y - w / 2.0f);
        glVertex2f(x + w, y - w / 2.0f);
        glEnd();
    }
}

// ---------------------- [3] �Ҽ��� ��� �Լ� ----------------------
/*
 * �Ҽ����� �� ���·� ��� �Լ�
 * x, y: ��ġ ��ǥ
 * size: ũ��
 */
void drawDot(float x, float y, float size) {
    glPointSize(size * 10.0f);   // �� ũ�� ���� (�����)
    glBegin(GL_POINTS);
    glVertex2f(x, y - size);
    glEnd();
}

// ---------------------- [4] �� �׸��� �Լ� ----------------------
/*
 * r: ������
 * seg: ���� ���� (Ŭ���� �ε巯��)
 */
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);    // ���� �߽�
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// ---------------------- [5] ���� �Լ� ----------------------
int main(void) {
    // GLFW �ʱ�ȭ
    if (!glfwInit()) return -1;

    // â ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System with Speed Indicator", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 2D ��ǥ�� ����
    glOrtho(-1, 1, -1, 1, -1, 1);

    // �¾�, ����, �� ������ �� �˵� �ݰ� ����
    const float sunRadius = 0.2f;
    const float earthRadius = 0.1f;
    const float moonRadius = 0.05f;
    const float earthOrbitRadius = 0.6f;
    const float moonOrbitRadius = 0.2f;

    // �ð� ���� �� �ӵ� ����
    float time = 0.0f;
    int timeDir = 1;              // 1: ������, -1: ������
    const float baseSpeed = 0.005f;  // �⺻ �ӵ�
    float speed = baseSpeed;        // ���� �ӵ�

    // ���� ����
    while (!glfwWindowShouldClose(window)) {
        // Ű �Է� ó��
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) timeDir = 1;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) timeDir = -1;
        if (GetAsyncKeyState('A') & 0x8000) {
            speed *= 2.0f;  // �ӵ� 2�� ����
            if (speed > 0.2f) speed = 0.2f;  // �ִ� ����
        }
        if (GetAsyncKeyState('Z') & 0x8000) {
            speed *= 0.5f;  // �ӵ� 0.5�� ����
            if (speed < 0.001f) speed = 0.001f;  // �ּ� ����
        }
        if (GetAsyncKeyState('R') & 0x8000) {
            speed = baseSpeed;  // �ӵ� �ʱ�ȭ
        }

        // �ð� ������Ʈ
        time += speed * timeDir;

        // ---------------- ȭ�� ������ ----------------
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) �¾� �׸���
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(sunRadius, 64);
        glPopMatrix();

        // (2) ���� ���� �� ����
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 1.0f);
        drawCircle(earthRadius, 32);
        glPopMatrix();

        // (3) �� ���� �� ����
        glPushMatrix();
        glRotatef(time * 100.0f, 0, 0, 1);
        glTranslatef(moonOrbitRadius, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(-time * 200.0f, 0, 0, 1);
        glColor3f(0.6f, 0.6f, 0.6f);
        drawCircle(moonRadius, 16);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

        // (4) �ӵ� ���� ���
        glPushMatrix();
        glTranslatef(-0.9f, 0.8f, 0.0f);  // ���� ��� ��ġ
        glColor3f(1.0f, 1.0f, 1.0f);

        if (speed > baseSpeed) {
            draw7Segment(2, 0.1f);  // �ӵ� 2��
        }
        else if (speed < baseSpeed) {
            draw7Segment(0, 0.05f);  // 0
            glTranslatef(0.07f, 0.0f, 0.0f);
            drawDot(0.0f, 0.0f, 0.05f);  // .
            glTranslatef(0.07f, 0.0f, 0.0f);
            draw7Segment(5, 0.05f);  // 5
        }
        else {
            draw7Segment(1, 0.1f);  // �ӵ� 1��
        }
        glPopMatrix();

        // ȭ�� ���
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ���α׷� ����
    glfwTerminate();
    return 0;
}
