#include <stdio.h>

// PassOrFail 함수: 점수가 50점 이상이면 1, 아니면 0 반환
int PassOrFail(int score) 
{
    if (score >= 50) 
    {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int avgScore = 80;        // 수업의 예상 평균 점수
    int myScore = 20;         // 본인의 예상 점수

    // 본인 점수로 결과 확인
    int myResult = PassOrFail(myScore);

    if (myResult == 1) 
    {
        printf("재시험 없습니다!\n");
    }
    else 
    {
        printf("우리는 망했다... 재시험이다...\n");
    }

    return 0;
}
