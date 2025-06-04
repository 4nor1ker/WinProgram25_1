// �¾� ���� �޿� ���� ǥ�� 

#include <GLFW/glfw3.h>     // OpenGL�� â ������ ���� GLFW ���̺귯��
#include <windows.h>        // GetAsyncKeyState �Լ� ��� (������ Ű���� �Է�)
#include <math.h>           // �ﰢ�Լ� ���� (cos, sin)

#pragma comment(lib, "opengl32.lib")  // OpenGL ���̺귯�� ��ũ ����

#define PI 3.1415926535f    // ������ ���

// 7-segment ���� ��Ʈ����ũ �迭 (0~9)
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

// ȭ�鿡 ������ �׸��� �Լ�
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// 7-segment ���� �׸��� �Լ�
void draw7Segment(int number, float size) {
    if (number < 0 || number > 9) return;
    unsigned char seg = SEGMENT_MAP[number];

    float x = -size / 2.0f;
    float y = size / 2.0f;
    float w = size;
    float h = size / 5.0f;

    // a (��� ����)
    if (seg & 0b1000000) drawLine(x, y, x + w, y);
    // b (��� ����)
    if (seg & 0b0100000) drawLine(x + w, y, x + w, y - w / 2.0f);
    // c (���� ����)
    if (seg & 0b0010000) drawLine(x + w, y - w / 2.0f, x + w, y - w);
    // d (�ϴ� ����)
    if (seg & 0b0001000) drawLine(x, y - w, x + w, y - w);
    // e (���� ����)
    if (seg & 0b0000100) drawLine(x, y - w / 2.0f, x, y - w);
    // f (�»� ����)
    if (seg & 0b0000010) drawLine(x, y, x, y - w / 2.0f);
    // g (�߾� ����)
    if (seg & 0b0000001) drawLine(x, y - w / 2.0f, x + w, y - w / 2.0f);
}

// ������ �׸��� �Լ�
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System with Numbers", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glOrtho(-1, 1, -1, 1, -1, 1);

    const float sunRadius = 0.2f;
    const float earthRadius = 0.1f;
    const float moonRadius = 0.05f;

    const float earthOrbitRadius = 0.6f;
    const float moonOrbitRadius = 0.2f;

    float time = 0.0f;
    int timeDir = 1;

    while (!glfwWindowShouldClose(window)) {
        // Ű �Է� ó��
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            timeDir = 1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            timeDir = -1;
        }

        time += 0.01f * timeDir;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) �¾�
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);  // �����
        drawCircle(sunRadius, 64);   // �¾�
        glColor3f(0.0f, 0.0f, 0.0f);  // ���� ����
        draw7Segment(0, 0.1f);       // �¾翡 0 ǥ��
        glPopMatrix();

        // (2) ���� ����
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);           // ���� ����
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f);

        // (2-1) ���� ����
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);         // ���� ����
        glColor3f(0.0f, 0.0f, 1.0f);                // �Ķ���
        drawCircle(earthRadius, 32);               // ����
        glColor3f(1.0f, 1.0f, 1.0f);               // ��� ����
        draw7Segment(2, 0.05f);                    // ������ 2 ǥ��
        glPopMatrix();

        // (3) �� ����
        glPushMatrix();
        glRotatef(time * 100.0f, 0, 0, 1);          // �� ����
        glTranslatef(moonOrbitRadius, 0.0f, 0.0f);

        // (3-1) �� ����
        glPushMatrix();
        glRotatef(-time * 200.0f, 0, 0, 1);         // �� ����
        glColor3f(0.6f, 0.6f, 0.6f);                // ȸ��
        drawCircle(moonRadius, 16);                // ��
        glColor3f(1.0f, 1.0f, 0.0f);               // ����� ����
        draw7Segment(4, 0.03f);                    // �޿� 4 ǥ��
        glPopMatrix();                             // �� ���� ����

        glPopMatrix();  // �� ���� ����
        glPopMatrix();  // ���� ���� ����

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
