#include<stdio.h>
#include<math.h>//��ó����

int main ()
{
    int principle, period;//principle�� ����, period�� �Ⱓ
    float interest, simple, compound;//interest�� ����, simple���ܸ�, compound�� ����
    scanf("%d %f %d", &principle, &interest, &period);//����, ����, �Ⱓ�� �Է¹޴´�.


    interest = interest / 100;//������ �ۼ�Ʈ���� ������ �ٲ� �ش�.
    simple = principle * (1 + period * interest);//�ܸ� ���
    compound = principle * pow((1 + interest), period);//���� ���


    printf("Simple Interest: %.0fwon\nCompound Interest: %.0fwon\n", simple, compound);//�ܸ�, ���� ���
    return 0;
}

