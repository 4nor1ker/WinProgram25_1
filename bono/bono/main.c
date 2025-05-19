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

    // 픽셀 기반 좌표계 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 배경 흰색
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // 얼굴 중심 및 반지름
    float cx = WINDOW_WIDTH / 2.0f;
    float cy = WINDOW_HEIGHT / 2.0f;
    float face_rx = 214.5f;   // 가로 반지름 (429 지름)
    float face_ry = 192.5f;   // 세로 반지름 (385 지름)

    // 눈 반지름
    float eye_r = 15.5f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 1. 파란 얼굴 (찌그러진 타원)
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

        // 2. 검정 테두리 (2픽셀 라인)
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
        // 아래로 1픽셀 이동한 테두리 추가 (수정됨)
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry + 1.0f;
            glVertex2f(x, y);
        }
        glEnd();
        // 아래로 1픽셀 이동한 테두리 추가
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = 2 * PI * i / NUM_SEGMENTS;
            float x = cx + cosf(angle) * face_rx;
            float y = cy + sinf(angle) * face_ry + 1;
            glVertex2f(x, y);
        }
        glEnd();



        // 3. 왼쪽 눈 (88, 178)
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

        // 4. 오른쪽 눈 (427, 183)
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

        // 5. 입 1 (235, 288), 흰색 찌그러진 타원 (가로 98, 세로 71)
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

        // 6. 입 2 (313, 289), 흰색 찌그러진 타원 (가로 98, 세로 71)
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

        // 7. 코 (275, 244), 찌그러진 타원 (65x54)
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

        // 8. 수염 (검정색 선 2픽셀, 시작/끝 y좌표 +1로 추가 선 그려 2픽셀 효과)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        // 왼쪽 수염
        glVertex2f(155, 250); glVertex2f(216, 266);
        glVertex2f(155, 251); glVertex2f(216, 267);

        glVertex2f(155, 288); glVertex2f(214, 287);
        glVertex2f(155, 289); glVertex2f(214, 288);

        glVertex2f(157, 318); glVertex2f(220, 301);
        glVertex2f(157, 319); glVertex2f(220, 302);

        // 오른쪽 수염
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