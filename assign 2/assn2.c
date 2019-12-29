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
	
//�� ���� ���ϱ�
	printf("�ϳ����� ž �� ���� �����ּ���<1������ 5�� ����>: "); 
	while (1)
	{
		scanf("%d", &N);
		if ((N>=1)&&(N<=5))
			break;
		else
			printf("�߸��� �Է��Դϴ�. 1���� 5 ������ ���ڸ� �Է����ּ���: ");
	}
	
	
//tower1�� �ʱⰪ �ֱ� 
	setTowerNum(&tower1, N);
//tower1�ʱⰪ ����. 
	firstTower1 = tower1;
	
	
	while (1)
	{
		print_divider();
		stepNum++;//step �� ���� 
		printf(">>>Step %d\n\n", stepNum); 
		print_poles(tower1, tower2, tower3);//���� Ÿ�� ��Ȳ ���� 
		print_divider();
		if (check_finish(firstTower1, tower2, tower3))//���� ���� �� loop ���� 
			break;
		
		//�ű� ��� ���ϱ�
		printf("1. ���� ���� ����� �������ּ���<1-3>: ");
		while (1)
		{
		scanf("%d", &towerNum);
		if (!((towerNum>=1)&&(towerNum<=3)))
			printf("1. �߸��� �Է��Դϴ�. 1���� 3 ������ ���ڸ� �Է����ּ���:");//���� ���̸� �޼��� ����  
		else if (check_not_empty(tower1, tower2, tower3, towerNum))
				break;
			else
				printf("1. �ش� ����� ����ֽ��ϴ�. ������� ���� ����� �������ּ���: ");//����� ��� �޼��� ���� 
		}
		
		//�Ű��� ��� ���ϱ�&�ű��
		printf("2. ���� �Ű��� ����� �������ּ���.<1-3>: ");
		while(1)
		{
			scanf("%d", &towerNum2);			
			if (!((towerNum2>=1)&&(towerNum2<=3)))
				printf("2. �߸��� �Է��Դϴ�. 1���� 3 ������ ���ڸ� �Է����ּ���:");//���� ���̸� �޼��� ����  
			else if (check_valid_move(&tower1, &tower2, &tower3, towerNum, towerNum2))
				break;
			else 
				printf("2. �ϳ����� ž ��Ģ�� ��߳��ϴ�. �ٸ� ����� �������ּ���:");
		} 
		
		//â �ʱ�ȭ 
		system("cls");
		printf("Block Moved!\n");
	}
	
	
	//���� ������ ��Ʈ 
	printf("���� ��� �ٸ� ������� �Ű������ϴ�. ������ �����մϴ�.\n");
	return 0;
}


//tower1�ʱⰪ �ο��ϴ� �Լ�. 
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


//���� �ߴ� �Լ� 
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

//main���� ���� ��� ��Ȳ �����ַ��� �θ��� �Լ�. 
void print_poles(int tower1, int tower2, int tower3)
{
	printf("[��� 1]\n");
	print_one_pole(tower1);
	printf("[��� 2]\n");
	print_one_pole(tower2);
	printf("[��� 3]\n");
	print_one_pole(tower3);
}

//print_poles���� ��� �ϳ� ����� �� �θ��� �Լ�.  
void print_one_pole(int tower)
{
	if (tower == 0)//���� ���� ��  
	{
		printf("Pole is empty\n"); 
		return;
	}
	
	int i, k, num;
	for (i=4;i>=0;i--)//���� ���� ��. 
	{
		num = tower / pow(10, i);//�� ��ü�ϱ� 
		if (num!=0)
		{
			for (k=0;k<num;k++)//���ʺ��� ��ü�� �� ��� 
			{
				printf("��");
			}
			printf("\n");
			tower = tower - num * pow(10, i); 
		}
	}
	return;
}

//���ڰ� ����Ű�� tower���� 0�̸� 0, 0�� �ƴϸ� 1�� ����ϴ� �Լ�. 
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
	if (X==0)//�� ������ 0 
		return 0;
	return 1;
}

//�ϳ���ž ��Ģ�� ��߳��� 0 ���, ��Ģ�� ��߳��� ������ �ٲٴ� �۾� �����ϰ� 1 ���. 
int check_valid_move(int *tower1, int* tower2, int *tower3, int Num1, int Num2)
{
	if (Num1==Num2)//���� ��� ���̿��� �����̸� ��ȭ�� �����Ƿ� �״�� 1 ����ϰ� ��. 
		return 1;
		int exporter, importer, ex=1, im=1;
	
	//�ִ� ��հ� �޴� ��հ��� ���� exporter�� importer�� ����. 
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

	//�ִ� ��տ��� �� ���� �� ũ�� ã��. 
	while (1)	{
		if (exporter/10==0)
			break;
		exporter = exporter / 10;
		ex = ex * 10;
	}
	//�޴� ����� �� ���� �� ũ�� ����. 
	while (1)	{
		if (importer/10==0)//Ȥ�� ���� ���ٸ� 0�� ����. 
			break;
		importer = importer / 10;
		im = im * 10;
	}
	
	//�޴� ����� ���� �� ũ�� ��Ģ�� ��߳��Ƿ� 0�� ��ȯ  
	if (importer!=0&&importer<exporter)
		return 0;
		
	//�ִ� ��տ��� �� ���� �� ����. 
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
	
	//�޴� �� ���� ���� �� �� �޴� ���. 
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
	
	//�޴� �� ���� ���� �� �� �޴� ���. 
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
	return 1;//��ü�� �����ϴٰ� 1 ���. 
}

int check_finish(int firstTower1, int tower2, int tower3)
{
	if (firstTower1==tower2||firstTower1==tower3)
		return 1;
	return 0;
}
