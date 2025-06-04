// 태양지구달 속도 증가 + 속도 숫자 표시



#include <GLFW/glfw3.h>    // OpenGL 및 GLFW 라이브러리
#include <windows.h>       // GetAsyncKeyState 함수 사용
#include <math.h>          // 삼각함수 사용
#include <stdio.h>         // printf 등 디버깅용 (안 쓰지만 혹시 몰라 남겨둠)

#pragma comment(lib, "opengl32.lib")  // OpenGL 라이브러리 링크 설정

#define PI 3.1415926535f   // 원주율 상수 정의

// ---------------------- [1] 7-segment 숫자 정의 -------------------------
/*
 * 0 ~ 9까지 각 숫자의 7-segment 표시 형태를 비트맵으로 정의한 배열.
 * 각 비트는 a,b,c,d,e,f,g 세그먼트를 의미.
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

// ---------------------- [2] 7-segment 숫자 출력 함수 ----------------------
/*
 * 숫자를 7-segment 방식으로 OpenGL에 출력하는 함수.
 * number: 출력할 숫자(0~9)
 * size: 세그먼트 전체 크기
 */
void draw7Segment(int number, float size) {
    if (number < 0 || number > 9) return;
    unsigned char seg = SEGMENT_MAP[number];

    float x = -size / 2.0f;       // 왼쪽 시작점
    float y = size / 2.0f;        // 위쪽 시작점
    float w = size;               // 세로 기준 크기
    float h = size / 5.0f;        // 세그먼트 두께

    // 각 세그먼트를 선으로 출력 (켜진 세그먼트만)
    if (seg & 0b1000000) {  // a: 상단 가로
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glEnd();
    }
    if (seg & 0b0100000) {  // b: 오른쪽 상단 세로
        glBegin(GL_LINES);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - w / 2.0f);
        glEnd();
    }
    if (seg & 0b0010000) {  // c: 오른쪽 하단 세로
        glBegin(GL_LINES);
        glVertex2f(x + w, y - w / 2.0f);
        glVertex2f(x + w, y - w);
        glEnd();
    }
    if (seg & 0b0001000) {  // d: 하단 가로
        glBegin(GL_LINES);
        glVertex2f(x, y - w);
        glVertex2f(x + w, y - w);
        glEnd();
    }
    if (seg & 0b0000100) {  // e: 왼쪽 하단 세로
        glBegin(GL_LINES);
        glVertex2f(x, y - w / 2.0f);
        glVertex2f(x, y - w);
        glEnd();
    }
    if (seg & 0b0000010) {  // f: 왼쪽 상단 세로
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y - w / 2.0f);
        glEnd();
    }
    if (seg & 0b0000001) {  // g: 중앙 가로
        glBegin(GL_LINES);
        glVertex2f(x, y - w / 2.0f);
        glVertex2f(x + w, y - w / 2.0f);
        glEnd();
    }
}

// ---------------------- [3] 소수점 출력 함수 ----------------------
/*
 * 소수점을 점 형태로 찍는 함수
 * x, y: 위치 좌표
 * size: 크기
 */
void drawDot(float x, float y, float size) {
    glPointSize(size * 10.0f);   // 점 크기 설정 (상대적)
    glBegin(GL_POINTS);
    glVertex2f(x, y - size);
    glEnd();
}

// ---------------------- [4] 원 그리기 함수 ----------------------
/*
 * r: 반지름
 * seg: 분할 개수 (클수록 부드러움)
 */
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);    // 원의 중심
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// ---------------------- [5] 메인 함수 ----------------------
int main(void) {
    // GLFW 초기화
    if (!glfwInit()) return -1;

    // 창 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System with Speed Indicator", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 2D 좌표계 설정
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 태양, 지구, 달 반지름 및 궤도 반경 설정
    const float sunRadius = 0.2f;
    const float earthRadius = 0.1f;
    const float moonRadius = 0.05f;
    const float earthOrbitRadius = 0.6f;
    const float moonOrbitRadius = 0.2f;

    // 시간 변수 및 속도 설정
    float time = 0.0f;
    int timeDir = 1;              // 1: 정방향, -1: 역방향
    const float baseSpeed = 0.005f;  // 기본 속도
    float speed = baseSpeed;        // 현재 속도

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        // 키 입력 처리
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) timeDir = 1;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) timeDir = -1;
        if (GetAsyncKeyState('A') & 0x8000) {
            speed *= 2.0f;  // 속도 2배 증가
            if (speed > 0.2f) speed = 0.2f;  // 최대 제한
        }
        if (GetAsyncKeyState('Z') & 0x8000) {
            speed *= 0.5f;  // 속도 0.5배 감소
            if (speed < 0.001f) speed = 0.001f;  // 최소 제한
        }
        if (GetAsyncKeyState('R') & 0x8000) {
            speed = baseSpeed;  // 속도 초기화
        }

        // 시간 업데이트
        time += speed * timeDir;

        // ---------------- 화면 렌더링 ----------------
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) 태양 그리기
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(sunRadius, 64);
        glPopMatrix();

        // (2) 지구 공전 및 자전
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 1.0f);
        drawCircle(earthRadius, 32);
        glPopMatrix();

        // (3) 달 공전 및 자전
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

        // (4) 속도 상태 출력
        glPushMatrix();
        glTranslatef(-0.9f, 0.8f, 0.0f);  // 왼쪽 상단 위치
        glColor3f(1.0f, 1.0f, 1.0f);

        if (speed > baseSpeed) {
            draw7Segment(2, 0.1f);  // 속도 2배
        }
        else if (speed < baseSpeed) {
            draw7Segment(0, 0.05f);  // 0
            glTranslatef(0.07f, 0.0f, 0.0f);
            drawDot(0.0f, 0.0f, 0.05f);  // .
            glTranslatef(0.07f, 0.0f, 0.0f);
            draw7Segment(5, 0.05f);  // 5
        }
        else {
            draw7Segment(1, 0.1f);  // 속도 1배
        }
        glPopMatrix();

        // 화면 출력
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 프로그램 종료
    glfwTerminate();
    return 0;
}
