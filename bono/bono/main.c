#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "opengl32.lib")

const int WINDOW_WIDTH = 537;
const int WINDOW_HEIGHT = 445;

#define PI 3.14159265358979323846
#define NUM_SEGMENTS 100

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Face Drawing", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // �ȼ� ��� ��ǥ�� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ��� ���
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // �� �߽� �� ������
    float cx = WINDOW_WIDTH / 2.0f;
    float cy = WINDOW_HEIGHT / 2.0f;
    float face_rx = 214.5f;   // ���� ������ (429 ����)
    float face_ry = 192.5f;   // ���� ������ (385 ����)

    // �� ������
    float eye_r = 15.5f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 1. �Ķ� �� (��׷��� Ÿ��)
        glColor3f(0.0f, 112.0f / 255.0f, 192.0f / 255.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry;
            glVertex2f(x, y);
        }
        glEnd();

        // 2. ���� �׵θ� (2�ȼ� ����)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry;
            glVertex2f(x, y);
        }
        glEnd();
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry + 1.0f;
            glVertex2f(x, y);
        }
        glEnd();
        // �Ʒ��� 1�ȼ� �̵��� �׵θ� �߰� (������)
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry + 1.0f;
            glVertex2f(x, y);
        }
        glEnd();
        // �Ʒ��� 1�ȼ� �̵��� �׵θ� �߰�
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry + 1;
            glVertex2f(x, y);
        }
        glEnd();



        // 3. ���� �� (88, 178)
        float eye_lx = 88.0f;
        float eye_ly = 178.0f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(eye_lx, eye_ly);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = eye_lx + cosf(angle) * eye_r;
            float y = eye_ly + sinf(angle) * eye_r;
            glVertex2f(x, y);
        }
        glEnd();

        // 4. ������ �� (427, 183)
        float eye_rx = 427.0f;
        float eye_ry = 183.0f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(eye_rx, eye_ry);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = eye_rx + cosf(angle) * eye_r;
            float y = eye_ry + sinf(angle) * eye_r;
            glVertex2f(x, y);
        }
        glEnd();

        // 5. �� 1 (235, 288), ��� ��׷��� Ÿ�� (���� 98, ���� 71)
        float mouth1_x = 235.0f;
        float mouth1_y = 288.0f;
        float mouth_rx = 49.0f;
        float mouth_ry = 35.5f;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(mouth1_x, mouth1_y);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = mouth1_x + cosf(angle) * mouth_rx;
            float y = mouth1_y + sinf(angle) * mouth_ry;
            glVertex2f(x, y);
        }
        glEnd();

        // 6. �� 2 (313, 289), ��� ��׷��� Ÿ�� (���� 98, ���� 71)
        float mouth2_x = 313.0f;
        float mouth2_y = 289.0f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(mouth2_x, mouth2_y);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = mouth2_x + cosf(angle) * mouth_rx;
            float y = mouth2_y + sinf(angle) * mouth_ry;
            glVertex2f(x, y);
        }
        glEnd();

        // 7. �� (275, 244), ��׷��� Ÿ�� (65x54)
        float nose_x = 275.0f;
        float nose_y = 244.0f;
        float nose_rx = 32.5f;
        float nose_ry = 27.0f;

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(nose_x, nose_y);
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = nose_x + cosf(angle) * nose_rx;
            float y = nose_y + sinf(angle) * nose_ry;
            glVertex2f(x, y);
        }
        glEnd();

        // 8. ���� (������ �� 2�ȼ�, ����/�� y��ǥ +1�� �߰� �� �׷� 2�ȼ� ȿ��)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        // ���� ����
        glVertex2f(155, 250); glVertex2f(216, 266);
        glVertex2f(155, 251); glVertex2f(216, 267);

        glVertex2f(155, 288); glVertex2f(214, 287);
        glVertex2f(155, 289); glVertex2f(214, 288);

        glVertex2f(157, 318); glVertex2f(220, 301);
        glVertex2f(157, 319); glVertex2f(220, 302);

        // ������ ����
        glVertex2f(324, 268); glVertex2f(385, 250);
        glVertex2f(324, 269); glVertex2f(385, 251);

        glVertex2f(324, 287); glVertex2f(390, 287);
        glVertex2f(324, 288); glVertex2f(390, 288);

        glVertex2f(322, 306); glVertex2f(388, 318);
        glVertex2f(322, 307); glVertex2f(388, 319);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}