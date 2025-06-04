// ������ 2�� �¾�������

#include <GLFW/glfw3.h>    // OpenGL�� â ������ ���� GLFW ���̺귯��
#include <windows.h>       // GetAsyncKeyState �Լ� ��� (������ Ű���� �Է�)
#include <math.h>          // �ﰢ�Լ� ���� (cos, sin)

#pragma comment(lib, "opengl32.lib")  // OpenGL ���̺귯�� ��ũ ����

#define PI 3.1415926535f   // ������ ���

// ������ �׸��� �Լ�
// r: ���� ������
// seg: ���� �� ����ؼ� �׸��� ���� (seg�� Ŭ���� ������ �ε巴�� ����)
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);  // �ﰢ�� ������ ������ ä���
    glVertex2f(0.0f, 0.0f);    // ���� �߽� ��ǥ
    for (int i = 0; i <= seg; ++i) {
        // 0�� ~ 360������ seg���� ������ ������ �׸���
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);  // �������� ������ ������ ��ǥ ���
    }
    glEnd();
}

int main(void) {
    // GLFW ���̺귯�� �ʱ�ȭ
    if (!glfwInit()) return -1;

    // 800x600 ũ���� â ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 2D ��ǥ�� ���� (-1 ~ 1 ����)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // �¾� ������ ����
    // �������� �¾� �������� 0.2�� ��������Ƿ� const float sunRadius = 0.2f�� ����
    const float sunRadius = 0.2f;

    // ���� ������ ����
    const float earthRadius = 0.1f;

    // �� ������ ����
    const float moonRadius = 0.05f;

    // �¾�� ���� ���� �Ÿ� (���� �ݰ�)
    // �������� 0.6 �Ÿ��� �����϶�� �����Ƿ� earthOrbitRadius = 0.6f�� ����
    const float earthOrbitRadius = 0.6f;

    // ������ �� ���� �Ÿ� (���� �ݰ�)
    const float moonOrbitRadius = 0.2f;

    // �ð� ���� (�����Ӹ��� ������ ���� ����)
    float time = 0.0f;

    // �ð� �帧 ���� (1: ������, -1: ������)
    int timeDir = 1;

    // ���� ����
    while (!glfwWindowShouldClose(window)) {
        // Ű �Է� ó��
        // ��Ű�� ������ ������(1), ��Ű�� ������ ������(-1)
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            timeDir = 1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            timeDir = -1;
        }

        // �ð� ���� (�����Ӹ��� 0.01�� ����)
        // timeDir ���� ���� ��/���������� �ð� ��ȭ
        time += 0.01f * timeDir;

        // ȭ�� �ʱ�ȭ
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) �¾� �׸���
        // �¾��� �߽�(0,0)�� �����Ǿ� ����
        // ����: �����
        // ������: sunRadius(0.2)
        // drawCircle(sunRadius, 64)���� seg=64�� ������ 64����ؼ� �ε巴�� �׸��ٴ� �ǹ�
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);  // �����
        drawCircle(sunRadius, 64);   // �¾� ������, seg=64
        glPopMatrix();

        // (2) ���� ����
        // �¾� �߽��� �������� �ݽð� �������� ȸ��
        // glRotatef�� ȸ���� �� glTranslatef�� ���� �˵� �ݰ�(0.6)��ŭ x������ �̵�
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);           // ���� ���� (�ݽð� ����)
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f); // �¾�� ���� ���� �Ÿ� 0.6

        // (3) ���� ����
        // ���� �ڽ��� �߽��� �������� �ð�������� ����
        // ����: �Ķ���
        // ������: earthRadius(0.1)
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);         // ���� ���� (�ð����)
        glColor3f(0.0f, 0.0f, 1.0f);                // �Ķ���
        drawCircle(earthRadius, 32);               // ���� ������, seg=32
        glPopMatrix();                             // ���� ���� ��ǥ�� ����

        // (4) �� ����
        // ������ �߽����� �ݽð� �������� ȸ��
        // glRotatef�� ȸ�� �� glTranslatef�� �� ���� �ݰ�(0.2)��ŭ x������ �̵�
        glPushMatrix();
        glRotatef(time * 100.0f, 0, 0, 1);          // �� ���� (�ݽð� ����)
        glTranslatef(moonOrbitRadius, 0.0f, 0.0f);  // ������ �� ���� �Ÿ� 0.2

        // (5) �� ����
        // �� �ڽ��� �߽��� �������� �ð�������� ����
        // ����: ȸ��
        // ������: moonRadius(0.05)
        glPushMatrix();
        glRotatef(-time * 200.0f, 0, 0, 1);         // �� ���� (�ð����)
        glColor3f(0.6f, 0.6f, 0.6f);                // ȸ��
        drawCircle(moonRadius, 16);                // �� ������, seg=16
        glPopMatrix();                             // �� ���� ��ǥ�� ����

        // (6) ��� ����
        glPopMatrix();  // �� ���� ��ǥ�� ����
        glPopMatrix();  // ���� ���� ��ǥ�� ����

        // ȭ�� ��� (���� ��ü)
        glfwSwapBuffers(window);
        // �̺�Ʈ ó��
        glfwPollEvents();
    }

    // ���α׷� ����
    glfwTerminate();
    return 0;
}
