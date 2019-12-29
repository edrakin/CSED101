#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void setTowerNum(int *tower1, int N); 
void print_divider();
void print_poles(int tower1, int tower2, int tower3);
void print_one_pole(int tower);
int check_not_empty(int tower1, int tower2, int tower3, int Num);
int check_valid_move(int *tower1, int* tower2, int *tower3, int Num1, int Num2);
int check_finish(int firstTower1, int tower2, int tower3);

int main ()
{
	int N, tower1, tower2=0, tower3=0;
	int towerNum, towerNum2;
	int firstTower1, stepNum=0;
	
//고리 개수 정하기
	printf("하노이의 탑 층 수를 정해주세요<1층부터 5층 사이>: "); 
	while (1)
	{
		scanf("%d", &N);
		if ((N>=1)&&(N<=5))
			break;
		else
			printf("잘못된 입력입니다. 1부터 5 사이의 춧자를 입력해주세요: ");
	}
	
	
//tower1에 초기값 넣기 
	setTowerNum(&tower1, N);
//tower1초기값 저장. 
	firstTower1 = tower1;
	
	
	while (1)
	{
		print_divider();
		stepNum++;//step 수 세기 
		printf(">>>Step %d\n\n", stepNum); 
		print_poles(tower1, tower2, tower3);//현재 타워 상황 보고 
		print_divider();
		if (check_finish(firstTower1, tower2, tower3))//조건 만족 시 loop 종료 
			break;
		
		//옮길 기둥 정하기
		printf("1. 블럭을 옯길 기둥을 선택해주세요<1-3>: ");
		while (1)
		{
		scanf("%d", &towerNum);
		if (!((towerNum>=1)&&(towerNum<=3)))
			printf("1. 잘못된 입력입니다. 1부터 3 사이의 숫자를 입력해주세요:");//범위 밖이면 메세지 띄우기  
		else if (check_not_empty(tower1, tower2, tower3, towerNum))
				break;
			else
				printf("1. 해당 기둥이 비어있습니다. 비어있지 않은 기둥을 선택해주세요: ");//기둥이 비면 메세지 띄우기 
		}
		
		//옮겨질 기둥 정하기&옮기기
		printf("2. 블럭이 옮겨질 기둥을 선택해주세요.<1-3>: ");
		while(1)
		{
			scanf("%d", &towerNum2);			
			if (!((towerNum2>=1)&&(towerNum2<=3)))
				printf("2. 잘못된 입력입니다. 1부터 3 사이의 숫자를 입력해주세요:");//범위 밖이면 메세지 띄우기  
			else if (check_valid_move(&tower1, &tower2, &tower3, towerNum, towerNum2))
				break;
			else 
				printf("2. 하노이의 탑 규칙에 어긋납니다. 다른 기둥을 선택해주세요:");
		} 
		
		//창 초기화 
		system("cls");
		printf("Block Moved!\n");
	}
	
	
	//게임 마무리 멘트 
	printf("블럭이 모두 다른 기둥으로 옮겨졌습니다. 퍼즐을 종료합니다.\n");
	return 0;
}


//tower1초기값 부여하는 함수. 
void setTowerNum(int *tower1, int N)
{
	if (N==1)
		*tower1 = 1;
	else if (N==2)
		*tower1 = 12;
	else if (N==3)
		*tower1 = 123;
	else if (N==4)
		*tower1 = 1234;
	else
		*tower1 = 12345;
}


//두줄 긋는 함수 
void print_divider()
{
	int k, i;
	for (k=0;k<2;k++)	{
		for (i=0;i<20;i++)	{	
			printf("=");
		}
		printf("\n");
	}
}

//main에서 현재 기둥 상황 보여주려고 부르는 함수. 
void print_poles(int tower1, int tower2, int tower3)
{
	printf("[기둥 1]\n");
	print_one_pole(tower1);
	printf("[기둥 2]\n");
	print_one_pole(tower2);
	printf("[기둥 3]\n");
	print_one_pole(tower3);
}

//print_poles에서 기둥 하나 출력할 때 부르는 함수.  
void print_one_pole(int tower)
{
	if (tower == 0)//고리가 없을 때  
	{
		printf("Pole is empty\n"); 
		return;
	}
	
	int i, k, num;
	for (i=4;i>=0;i--)//고리가 있을 때. 
	{
		num = tower / pow(10, i);//고리 해체하기 
		if (num!=0)
		{
			for (k=0;k<num;k++)//위쪽부터 해체된 고리 출력 
			{
				printf("□");
			}
			printf("\n");
			tower = tower - num * pow(10, i); 
		}
	}
	return;
}

//숫자가 가리키는 tower값이 0이면 0, 0이 아니면 1을 출력하는 함수. 
int check_not_empty(int tower1, int tower2, int tower3, int Num)
{
	int X;
	switch (Num)	{ 
		case 1:
			X=tower1;
			break;
		case 2:
			X=tower2;
			break;
		case 3:
			X=tower3;
	}
	if (X==0)//고리 없으면 0 
		return 0;
	return 1;
}

//하노이탑 규칙에 어긋나면 0 출력, 규칙에 어긋나지 않으면 바꾸는 작업 실행하고 1 출력. 
int check_valid_move(int *tower1, int* tower2, int *tower3, int Num1, int Num2)
{
	if (Num1==Num2)//같은 기둥 사이에서 움직이면 변화가 없으므로 그대로 1 출력하고 끝. 
		return 1;
		int exporter, importer, ex=1, im=1;
	
	//주는 기둥과 받는 기둥값을 각각 exporter와 importer에 저장. 
			switch (Num2)	{
		case 1:
			importer=*tower1;
			break;
		case 2:
			importer=*tower2;
			break;
		case 3:
			importer=*tower3;
	}
	switch (Num1)	{
		case 1:
			exporter=*tower1;
			break;
		case 2:
			exporter=*tower2;
			break;
		case 3:
			exporter=*tower3;
	}

	//주는 기둥에서 맨 위쪽 고리 크기 찾기. 
	while (1)	{
		if (exporter/10==0)
			break;
		exporter = exporter / 10;
		ex = ex * 10;
	}
	//받는 기둥의 맨 위쪽 고리 크기 추출. 
	while (1)	{
		if (importer/10==0)//혹시 고리가 없다면 0을 추출. 
			break;
		importer = importer / 10;
		im = im * 10;
	}
	
	//받는 기둥의 고리가 더 크면 규칙에 어긋나므로 0값 반환  
	if (importer!=0&&importer<exporter)
		return 0;
		
	//주는 기둥에서 맨 위쪽 고리 뜯어내기. 
	switch (Num1)	{
		case 1:
			*tower1 = *tower1 - exporter * ex;
			break;
		case 2:
			*tower2 = *tower2 - exporter * ex;
			break;
		case 3:
			*tower3 = *tower3 - exporter * ex;
	}
	
	//받는 놈 고리가 없을 때 고리 받는 방식. 
	if (importer==0)
	{
			switch (Num2)	{
		case 1:
			*tower1 = exporter;
			break;
		case 2:
			*tower2 = exporter;
			break;
		case 3:
			*tower3 = exporter;
		}
		return 1;
	}
	
	//받는 놈 고리가 있을 때 고리 받는 방식. 
	switch (Num2)	{
		case 1:
			*tower1 = *tower1 + exporter * im * 10;
			break;
		case 2:
			*tower2 = *tower2 + exporter * im * 10;
			break;
		case 3:
			*tower3 = *tower3 + exporter * im * 10;
	}
	return 1;//교체가 가능하다고 1 출력. 
}

int check_finish(int firstTower1, int tower2, int tower3)
{
	if (firstTower1==tower2||firstTower1==tower3)
		return 1;
	return 0;
}
