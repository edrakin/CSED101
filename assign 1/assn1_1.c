#include<stdio.h>
#include<math.h>//전처리기

int main ()
{
    int principle, period;//principle은 원금, period는 기간
    float interest, simple, compound;//interest는 이율, simple은단리, compound는 복리
    scanf("%d %f %d", &principle, &interest, &period);//원금, 이율, 기간을 입력받는다.


    interest = interest / 100;//이율을 퍼센트에서 비율로 바꿔 준다.
    simple = principle * (1 + period * interest);//단리 계산
    compound = principle * pow((1 + interest), period);//복리 계산


    printf("Simple Interest: %.0fwon\nCompound Interest: %.0fwon\n", simple, compound);//단리, 복리 출력
    return 0;
}

