// 예상문제1 스마일맨 (눈을 세로 선으로 표현 + 주석 상세 설명)

#include <GLFW/glfw3.h>    // OpenGL과 창 관리를 위한 GLFW 라이브러리
#include <windows.h>       // GetAsyncKeyState 함수 사용
#include <math.h>          // 삼각함수

#pragma comment(lib, "opengl32.lib")  // OpenGL 라이브러리 링크 설정

#define PI 3.1415926535f   // 원주율

// -------------------------
// 원형 그리기 함수 (얼굴)
// -------------------------
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // 중심
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// -------------------------
// 웃는 입 그리기 함수
// w: 가로 길이, h: 세로 길이
// -------------------------
void drawSmile(float w, float h) {
    glLineWidth(3.0f);  // 선 두께 설정 (여기를 바꾸면 입이 더 두꺼워집니다!)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; ++i) {
        float a = (-30.0f - 120.0f * i / 20.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * w, sinf(a) * h);
    }
    glEnd();
    glLineWidth(1.0f);  // 선 두께 초기화 (다른 선에 영향 없도록)
}


// -------------------------
// 왼쪽 눈 그리기 함수 (세로 선분)
// size: 눈 길이 (길게 하려면 size를 키워주세요!)
// 선 두께는 glLineWidth로 조절할 수 있습니다.
// -------------------------
void drawLeftEye(float size) {
    glLineWidth(5.0f);  // 선 두께 (여기를 바꾸면 눈이 더 두꺼워집니다!)
    glBegin(GL_LINES);
    glVertex2f(0.0f, size / 2.0f);    // 위쪽 점
    glVertex2f(0.0f, -size / 2.0f);   // 아래쪽 점 (여기를 바꾸면 눈 길이가 늘어납니다!)
    glEnd();
    glLineWidth(1.0f);  // 선 두께 초기화
}

// -------------------------
// 오른쪽 눈 그리기 함수
// wink: 0이면 일반 눈, 1이면 윙크 ('<' 형태)
// size: 눈 길이
// -------------------------
void drawRightEye(float size, int wink) {
    if (!wink) {
        // 일반 눈 (세로 선)
        glLineWidth(5.0f);  // 선 두께 (여기를 바꾸면 눈이 더 두꺼워집니다!)
        glBegin(GL_LINES);
        glVertex2f(0.0f, size / 2.0f);   // 위쪽 점
        glVertex2f(0.0f, -size / 2.0f);  // 아래쪽 점 (여기를 바꾸면 눈 길이가 늘어납니다!)
        glEnd();
        glLineWidth(1.0f);  // 선 두께 초기화
    }
    else {
        // '<' 형태로 윙크 그리기
        glBegin(GL_LINES);
        glVertex2f(size, size);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(size, -size);
        glEnd();
    }
}

// -------------------------
// 메인 함수
// -------------------------
int main(void) {
    // 1) GLFW 초기화
    if (!glfwInit()) return -1;

    // 2) 창 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Wink (Vertical Eyes)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3) 2D 좌표계 설정 (-1 ~ 1)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 얼굴과 눈 크기 파라미터
    const float faceRadius = 0.5f;     // 얼굴 크기
    const float eyeSize = 0.1f;       // 눈 길이 (여기를 키우면 눈이 길어집니다!)
    const float eyeOffsetX = 0.2f;     // 눈의 X위치
    const float eyeOffsetY = 0.2f;     // 눈의 Y위치

    int winkState = 0;  // 오른쪽 눈 상태

    // 4) 메인 루프
    while (!glfwWindowShouldClose(window)) {
        // (1) 키 입력 처리 (W 키)
        if (GetAsyncKeyState('W') & 0x8000) winkState = 1;
        else winkState = 0;

        // (2) 화면 초기화
        glClear(GL_COLOR_BUFFER_BIT);

        // (3) 얼굴 그리기
        glColor3f(1.0f, 1.0f, 0.0f);  // 얼굴 색상 (노란색)
        drawCircle(faceRadius, 64);

        // (4) 눈 & 입 그리기
        glColor3f(0.0f, 0.0f, 0.0f);  // 눈/입 색상 (검정색)

        // 왼쪽 눈
        glPushMatrix();
        glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);  // 왼쪽 눈 위치 이동
        drawLeftEye(eyeSize);                        // 왼쪽 눈 그리기
        glPopMatrix();

        // 오른쪽 눈
        glPushMatrix();
        glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);   // 오른쪽 눈 위치 이동
        drawRightEye(eyeSize, winkState);            // 오른쪽 눈 그리기
        glPopMatrix();

        // 웃는 입
        glPushMatrix();
        glTranslatef(0.0f, -0.1f, 0.0f);  // 살짝 아래로 이동
        drawSmile(0.3f, 0.2f);            // 입 그리기
        glPopMatrix();

        // (5) 화면 출력
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 5) 종료 처리
    glfwTerminate();
    return 0;
}
