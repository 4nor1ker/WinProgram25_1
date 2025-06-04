// 태양 지구 달에 숫자 표시 

#include <GLFW/glfw3.h>     // OpenGL과 창 관리를 위한 GLFW 라이브러리
#include <windows.h>        // GetAsyncKeyState 함수 사용 (윈도우 키보드 입력)
#include <math.h>           // 삼각함수 계산용 (cos, sin)

#pragma comment(lib, "opengl32.lib")  // OpenGL 라이브러리 링크 설정

#define PI 3.1415926535f    // 원주율 상수

// 7-segment 숫자 비트마스크 배열 (0~9)
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

// 화면에 직선을 그리는 함수
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// 7-segment 숫자 그리는 함수
void draw7Segment(int number, float size) {
    if (number < 0 || number > 9) return;
    unsigned char seg = SEGMENT_MAP[number];

    float x = -size / 2.0f;
    float y = size / 2.0f;
    float w = size;
    float h = size / 5.0f;

    // a (상단 가로)
    if (seg & 0b1000000) drawLine(x, y, x + w, y);
    // b (우상 세로)
    if (seg & 0b0100000) drawLine(x + w, y, x + w, y - w / 2.0f);
    // c (우하 세로)
    if (seg & 0b0010000) drawLine(x + w, y - w / 2.0f, x + w, y - w);
    // d (하단 가로)
    if (seg & 0b0001000) drawLine(x, y - w, x + w, y - w);
    // e (좌하 세로)
    if (seg & 0b0000100) drawLine(x, y - w / 2.0f, x, y - w);
    // f (좌상 세로)
    if (seg & 0b0000010) drawLine(x, y, x, y - w / 2.0f);
    // g (중앙 가로)
    if (seg & 0b0000001) drawLine(x, y - w / 2.0f, x + w, y - w / 2.0f);
}

// 원형을 그리는 함수
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
        // 키 입력 처리
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            timeDir = 1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            timeDir = -1;
        }

        time += 0.01f * timeDir;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) 태양
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);  // 노란색
        drawCircle(sunRadius, 64);   // 태양
        glColor3f(0.0f, 0.0f, 0.0f);  // 검정 숫자
        draw7Segment(0, 0.1f);       // 태양에 0 표시
        glPopMatrix();

        // (2) 지구 공전
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);           // 지구 공전
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f);

        // (2-1) 지구 자전
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);         // 지구 자전
        glColor3f(0.0f, 0.0f, 1.0f);                // 파란색
        drawCircle(earthRadius, 32);               // 지구
        glColor3f(1.0f, 1.0f, 1.0f);               // 흰색 숫자
        draw7Segment(2, 0.05f);                    // 지구에 2 표시
        glPopMatrix();

        // (3) 달 공전
        glPushMatrix();
        glRotatef(time * 100.0f, 0, 0, 1);          // 달 공전
        glTranslatef(moonOrbitRadius, 0.0f, 0.0f);

        // (3-1) 달 자전
        glPushMatrix();
        glRotatef(-time * 200.0f, 0, 0, 1);         // 달 자전
        glColor3f(0.6f, 0.6f, 0.6f);                // 회색
        drawCircle(moonRadius, 16);                // 달
        glColor3f(1.0f, 1.0f, 0.0f);               // 노란색 숫자
        draw7Segment(4, 0.03f);                    // 달에 4 표시
        glPopMatrix();                             // 달 자전 복원

        glPopMatrix();  // 달 공전 복원
        glPopMatrix();  // 지구 공전 복원

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
