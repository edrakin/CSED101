#include<stdio.h>//전처리기

char lowerToUpper(char c);//소문자를 대문자로 변환
int getSequenceNum(char capital);//해당 알파벳 대문자의 순서 번호를 반환
char encrypt(char c, int num);//알파벳 문자에서 한자리 정수를 뺀 문자를 반환

int main ()
{
	char letter, LETTER, signal;//letter는 받을 소문자, LETTER는 대문자, signal은 마지막 출력 문자
	int N, seq;//N은 암호화 정수, seq는 대문자의 순서 번호
	
	printf("Enter a character in Lowercase: ");
	scanf("%c", &letter);
	printf("Enter encoding number(1~9): ");
	scanf("%d", &N);//소문자와 암호화 정수를 입력받는다.
	
	
	LETTER = lowerToUpper(letter);//소문자를 대문자에 넣는다.
	seq = getSequenceNum(LETTER);//알파벳의 순서 번호를 seq에 넣는다.
	signal = encrypt(LETTER, N);//signal을 계산해서 저장.

	
	printf("Uppercase of Entered character: %c\n", LETTER);
	printf("Sequence Number of entered character: %d\n", seq);
	printf("Encrupted output: %c\n", signal);//요구사항을 모두 출력한다.
}


char lowerToUpper(char c)
{
	return c - 32;
}


int getSequenceNum(char capital)
{
	return capital - 64;
}


char encrypt(char c, int num)
{
	return c - num;
}
