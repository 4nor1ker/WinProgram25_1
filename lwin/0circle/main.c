// ������1 �����ϸ� (���� ���� ������ ǥ�� + �ּ� �� ����)

#include <GLFW/glfw3.h>    // OpenGL�� â ������ ���� GLFW ���̺귯��
#include <windows.h>       // GetAsyncKeyState �Լ� ���
#include <math.h>          // �ﰢ�Լ�

#pragma comment(lib, "opengl32.lib")  // OpenGL ���̺귯�� ��ũ ����

#define PI 3.1415926535f   // ������

// -------------------------
// ���� �׸��� �Լ� (��)
// -------------------------
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // �߽�
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// -------------------------
// ���� �� �׸��� �Լ�
// w: ���� ����, h: ���� ����
// -------------------------
void drawSmile(float w, float h) {
    glLineWidth(3.0f);  // �� �β� ���� (���⸦ �ٲٸ� ���� �� �β������ϴ�!)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; ++i) {
        float a = (-30.0f - 120.0f * i / 20.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * w, sinf(a) * h);
    }
    glEnd();
    glLineWidth(1.0f);  // �� �β� �ʱ�ȭ (�ٸ� ���� ���� ������)
}


// -------------------------
// ���� �� �׸��� �Լ� (���� ����)
// size: �� ���� (��� �Ϸ��� size�� Ű���ּ���!)
// �� �β��� glLineWidth�� ������ �� �ֽ��ϴ�.
// -------------------------
void drawLeftEye(float size) {
    glLineWidth(5.0f);  // �� �β� (���⸦ �ٲٸ� ���� �� �β������ϴ�!)
    glBegin(GL_LINES);
    glVertex2f(0.0f, size / 2.0f);    // ���� ��
    glVertex2f(0.0f, -size / 2.0f);   // �Ʒ��� �� (���⸦ �ٲٸ� �� ���̰� �þ�ϴ�!)
    glEnd();
    glLineWidth(1.0f);  // �� �β� �ʱ�ȭ
}

// -------------------------
// ������ �� �׸��� �Լ�
// wink: 0�̸� �Ϲ� ��, 1�̸� ��ũ ('<' ����)
// size: �� ����
// -------------------------
void drawRightEye(float size, int wink) {
    if (!wink) {
        // �Ϲ� �� (���� ��)
        glLineWidth(5.0f);  // �� �β� (���⸦ �ٲٸ� ���� �� �β������ϴ�!)
        glBegin(GL_LINES);
        glVertex2f(0.0f, size / 2.0f);   // ���� ��
        glVertex2f(0.0f, -size / 2.0f);  // �Ʒ��� �� (���⸦ �ٲٸ� �� ���̰� �þ�ϴ�!)
        glEnd();
        glLineWidth(1.0f);  // �� �β� �ʱ�ȭ
    }
    else {
        // '<' ���·� ��ũ �׸���
        glBegin(GL_LINES);
        glVertex2f(size, size);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(size, -size);
        glEnd();
    }
}

// -------------------------
// ���� �Լ�
// -------------------------
int main(void) {
    // 1) GLFW �ʱ�ȭ
    if (!glfwInit()) return -1;

    // 2) â ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Wink (Vertical Eyes)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3) 2D ��ǥ�� ���� (-1 ~ 1)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // �󱼰� �� ũ�� �Ķ����
    const float faceRadius = 0.5f;     // �� ũ��
    const float eyeSize = 0.1f;       // �� ���� (���⸦ Ű��� ���� ������ϴ�!)
    const float eyeOffsetX = 0.2f;     // ���� X��ġ
    const float eyeOffsetY = 0.2f;     // ���� Y��ġ

    int winkState = 0;  // ������ �� ����

    // 4) ���� ����
    while (!glfwWindowShouldClose(window)) {
        // (1) Ű �Է� ó�� (W Ű)
        if (GetAsyncKeyState('W') & 0x8000) winkState = 1;
        else winkState = 0;

        // (2) ȭ�� �ʱ�ȭ
        glClear(GL_COLOR_BUFFER_BIT);

        // (3) �� �׸���
        glColor3f(1.0f, 1.0f, 0.0f);  // �� ���� (�����)
        drawCircle(faceRadius, 64);

        // (4) �� & �� �׸���
        glColor3f(0.0f, 0.0f, 0.0f);  // ��/�� ���� (������)

        // ���� ��
        glPushMatrix();
        glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);  // ���� �� ��ġ �̵�
        drawLeftEye(eyeSize);                        // ���� �� �׸���
        glPopMatrix();

        // ������ ��
        glPushMatrix();
        glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);   // ������ �� ��ġ �̵�
        drawRightEye(eyeSize, winkState);            // ������ �� �׸���
        glPopMatrix();

        // ���� ��
        glPushMatrix();
        glTranslatef(0.0f, -0.1f, 0.0f);  // ��¦ �Ʒ��� �̵�
        drawSmile(0.3f, 0.2f);            // �� �׸���
        glPopMatrix();

        // (5) ȭ�� ���
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 5) ���� ó��
    glfwTerminate();
    return 0;
}
