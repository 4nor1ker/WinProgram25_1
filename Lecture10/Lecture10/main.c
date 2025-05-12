// OpenGL 기본 라이브러리 연결 (Windows에 내장되어 있음)
#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>  // GLFW 라이브러리 (창 생성 및 입력 처리)
#include <math.h>        // 수학 함수 사용 (cosf, sinf 등)

#define PI 3.14159265f   // 파이 상수 정의

// 화면에 알록달록한 원을 그리는 함수
void draw_colorful_circle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);  // 삼각형 팬 모드로 원 구성 시작

    // 원의 중심점 색상 (흰색)
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(cx, cy);  // 중심 좌표

    // 원 둘레 점들 계산 및 색상 지정
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;  // 현재 각도
        float x = cx + radius * cosf(angle);     // x 좌표
        float y = cy + radius * sinf(angle);     // y 좌표

        // 꼭짓점마다 색상 다르게 지정 (알록달록)
        float r = (cosf(angle) + 1.0f) / 2.0f;
        float g = (sinf(angle) + 1.0f) / 2.0f;
        float b = (cosf(angle * 2.0f) + 1.0f) / 2.0f;
        glColor3f(r, g, b);  // 꼭짓점 색상 설정

        glVertex2f(x, y);    // 꼭짓점 좌표 추가
    }

    glEnd();  // 도형 그리기 끝
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) return -1;

    // OpenGL 2.1 버전 요청 (glBegin 같은 레거시 함수 사용 가능하게 함)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // 창 생성 (500x500 크기, 타이틀: "GLFW: Rainbow Circle")
    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Rainbow Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // OpenGL 렌더링 컨텍스트를 현재 창에 연결
    glfwMakeContextCurrent(window);

    // 좌표계 설정: -1.0 ~ 1.0 사이 (2D 정규화 좌표계)
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드로 설정
    glLoadIdentity();            // 기본 행렬 로드
    glOrtho(-1, 1, -1, 1, -1, 1); // 2D 직교 투영 설정

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // 이전 프레임 지우기 (배경 클리어)

        draw_colorful_circle(0.0f, 0.0f, 0.5f, 100);  // 화면 중앙에 반지름 0.5짜리 원 그리기

        glfwSwapBuffers(window);  // 프레임 출력 (더블 버퍼링)
        glfwPollEvents();         // 입력 이벤트 처리
    }

    // 리소스 정리
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}