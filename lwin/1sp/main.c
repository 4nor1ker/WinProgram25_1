// 예상문제 2번 태양지구달

#include <GLFW/glfw3.h>    // OpenGL과 창 관리를 위한 GLFW 라이브러리
#include <windows.h>       // GetAsyncKeyState 함수 사용 (윈도우 키보드 입력)
#include <math.h>          // 삼각함수 계산용 (cos, sin)

#pragma comment(lib, "opengl32.lib")  // OpenGL 라이브러리 링크 설정

#define PI 3.1415926535f   // 원주율 상수

// 원형을 그리는 함수
// r: 원의 반지름
// seg: 원을 몇 등분해서 그릴지 결정 (seg가 클수록 원형이 부드럽게 보임)
void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);  // 삼각형 팬으로 원형을 채우기
    glVertex2f(0.0f, 0.0f);    // 원의 중심 좌표
    for (int i = 0; i <= seg; ++i) {
        // 0도 ~ 360도까지 seg개로 나눠서 원형을 그린다
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);  // 반지름과 각도로 꼭짓점 좌표 계산
    }
    glEnd();
}

int main(void) {
    // GLFW 라이브러리 초기화
    if (!glfwInit()) return -1;

    // 800x600 크기의 창 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 2D 좌표계 설정 (-1 ~ 1 범위)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 태양 반지름 설정
    // 문제에서 태양 반지름을 0.2로 명시했으므로 const float sunRadius = 0.2f로 설정
    const float sunRadius = 0.2f;

    // 지구 반지름 설정
    const float earthRadius = 0.1f;

    // 달 반지름 설정
    const float moonRadius = 0.05f;

    // 태양과 지구 사이 거리 (공전 반경)
    // 문제에서 0.6 거리로 공전하라고 했으므로 earthOrbitRadius = 0.6f로 설정
    const float earthOrbitRadius = 0.6f;

    // 지구와 달 사이 거리 (공전 반경)
    const float moonOrbitRadius = 0.2f;

    // 시간 변수 (프레임마다 일정한 값을 누적)
    float time = 0.0f;

    // 시간 흐름 방향 (1: 정방향, -1: 역방향)
    int timeDir = 1;

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        // 키 입력 처리
        // →키가 눌리면 정방향(1), ←키가 눌리면 역방향(-1)
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            timeDir = 1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            timeDir = -1;
        }

        // 시간 누적 (프레임마다 0.01씩 누적)
        // timeDir 값에 따라 정/역방향으로 시간 변화
        time += 0.01f * timeDir;

        // 화면 초기화
        glClear(GL_COLOR_BUFFER_BIT);

        // (1) 태양 그리기
        // 태양은 중심(0,0)에 고정되어 있음
        // 색상: 노란색
        // 반지름: sunRadius(0.2)
        // drawCircle(sunRadius, 64)에서 seg=64는 원형을 64등분해서 부드럽게 그린다는 의미
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);  // 노란색
        drawCircle(sunRadius, 64);   // 태양 반지름, seg=64
        glPopMatrix();

        // (2) 지구 공전
        // 태양 중심을 기준으로 반시계 방향으로 회전
        // glRotatef로 회전한 뒤 glTranslatef로 공전 궤도 반경(0.6)만큼 x축으로 이동
        glPushMatrix();
        glRotatef(time * 30.0f, 0, 0, 1);           // 지구 공전 (반시계 방향)
        glTranslatef(earthOrbitRadius, 0.0f, 0.0f); // 태양과 지구 사이 거리 0.6

        // (3) 지구 자전
        // 지구 자신의 중심을 기준으로 시계방향으로 자전
        // 색상: 파란색
        // 반지름: earthRadius(0.1)
        glPushMatrix();
        glRotatef(-time * 100.0f, 0, 0, 1);         // 지구 자전 (시계방향)
        glColor3f(0.0f, 0.0f, 1.0f);                // 파란색
        drawCircle(earthRadius, 32);               // 지구 반지름, seg=32
        glPopMatrix();                             // 지구 자전 좌표계 복원

        // (4) 달 공전
        // 지구를 중심으로 반시계 방향으로 회전
        // glRotatef로 회전 후 glTranslatef로 달 공전 반경(0.2)만큼 x축으로 이동
        glPushMatrix();
        glRotatef(time * 100.0f, 0, 0, 1);          // 달 공전 (반시계 방향)
        glTranslatef(moonOrbitRadius, 0.0f, 0.0f);  // 지구와 달 사이 거리 0.2

        // (5) 달 자전
        // 달 자신의 중심을 기준으로 시계방향으로 자전
        // 색상: 회색
        // 반지름: moonRadius(0.05)
        glPushMatrix();
        glRotatef(-time * 200.0f, 0, 0, 1);         // 달 자전 (시계방향)
        glColor3f(0.6f, 0.6f, 0.6f);                // 회색
        drawCircle(moonRadius, 16);                // 달 반지름, seg=16
        glPopMatrix();                             // 달 자전 좌표계 복원

        // (6) 행렬 복원
        glPopMatrix();  // 달 공전 좌표계 복원
        glPopMatrix();  // 지구 공전 좌표계 복원

        // 화면 출력 (버퍼 교체)
        glfwSwapBuffers(window);
        // 이벤트 처리
        glfwPollEvents();
    }

    // 프로그램 종료
    glfwTerminate();
    return 0;
}
