#include <stdio.h>

// 평균 점수를 기준으로 합격 여부 판단
// PassOrFail 함수: score가 avg 이상이면 1, 아니면 0 반환
int PassOrFail(int score, int avg)
{
    if (score >= avg) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int avgScore = 80;    // 수업의 예상 평균 점수
    int myScore = 20;     // 본인의 예상 점수

    // 평균 점수를 기준으로 합격 여부 확인
    int myResult = PassOrFail(myScore, avgScore);

    if (myResult == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다... 재시험이다...\n");
    }

    return 0;
}
