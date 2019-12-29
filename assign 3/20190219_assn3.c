#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAXROW 8
#define MAXCOLUMN 8
#define RED "\x1b[31m"
#define RES "\x1b[0m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
void fight(int* from, int* to, int* comfrom, int* comto, int userN, int comN, char* land, char* comland);


int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int* row, int* column, int* regionCount)//���� �޾Ƽ� breeding points ã�� �Լ�
{
	FILE* infile = NULL;//map.txt ���� ���Ϻ���.
	int x, y;
	infile = fopen("map.txt", "r");
	if (infile == NULL)//������ ������ ���� �޽����� �Բ� ���α׷� ����
	{
		printf("Error--No file\n\t\tprogram closed");
		return 0;
	}
	fscanf(infile, "%d%d%d", row, column, regionCount);//���� ���μ���, �� ���� �ޱ�

	map[0][0] = 'A';
	map[*row - 1][*column - 1] = 'B';
	antCounts[0][0] = 10;
	antCounts[*row - 1][*column - 1] = 10;//A�� B�� basement �����ϱ�

	while (fscanf(infile, "%d%d", &x, &y) != EOF)//�߸� ���� ��ǥ �ް� 'N' �ֱ�
	{
		map[x][y] = 'N';
	}
	fclose(infile);//���Ͽ��� �̾Ƴ� �� �� �̾����� ó��
	return 1;
}





void PrintMap(char map[][MAXCOLUMN], int row, int column)//�ʿ��� ��� ������ �������� ǥ���ϴ� �Լ�
{
	int a, b;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 0)
				printf("  0");
			else if (map[a][b] == 'A')	printf(BLUE "  A" RES);//A���̸� �Ķ������� ǥ��
			else if (map[a][b] == 'B')	printf(RED "  B" RES);//B���̸� ���������� ǥ��
			else printf(YELLOW "  N" RES);//�߸������� �������.
		}
		printf("\n");
	}
}







void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int
	row, int column)//������ ���� ���� ǥ���ϴ� �Լ�
{
	int a, b;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 0)	printf("  0");
			else if (map[a][b] == 'A')//A�� ���� ���� �Ķ���
			{
				printf(BLUE);
				printf("%3d", antCounts[a][b]);
				printf(RES);
			}
			else if (map[a][b] == 'B')//B�� ���� ���� ������
			{
				printf(RED);
				printf("%3d", antCounts[a][b]);
				printf(RES);
			}
			else printf(YELLOW "  0" RES);//�߸������� ��������� 0������� ǥ��
		}
		printf("\n");
	}
	printf("\n");
}







void move(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int
	row, int column, int region)//���� �̵��ϰ�, �ο�� �Լ�.
{
	int num = 0;
	int *from, *to, fromax, toax, *comfrom, *comto, comfromax, comtoax, userN, comN;
	//from�� to�� ���� �����°��� �޴� ���� �ּ�, ax�� ������ ��ǥ�� ��ȣȭ.
	//userN�� comN�� ���� ������ ������ ��
	char N[100] = { 0 };
	int check = 0, sum = 0;
	char* land, *comland;
	int* choice[63] = { 0 };
	int adr[63] = { 0 };
	int a, b;
	int x;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 'A')//A�� ��ġ ��ĵ
			{
				printf("%d : (%d, %d)\n", ++num, a, b);//��ȣ �ű��, �ĺ� ����� �ּҴ� choice��, ��ǥ���� adr�� ����.
				choice[num] = &antCounts[a][b];
				adr[num] = 10 * a + b;
			}
		}
	}
	printf("where ants start? ");


	while (1)
	{
		scanf("%s", a);
		for (a = 0; a < 100; a++)
		{
			if (N[a] == '\0')
			{
				break;
			}
			else if (N[a] > 57 || N[a] < 48)
			{
				//���ڰ� ������
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			printf("Please type an integer from 1 to %d : ", num);
		}
		else
		{
			for (b = 0; b < a; b++)
			{
				sum = 10 * sum + (N[b] - 48);
			}

			if (sum > 0 && sum < num)
			{
				break;
			}
			else
				printf("Please type an integer from 1 to %d : ", num);
		}
	}
		




	from = choice[sum];//���̰� ����ϴ� ���� �ּ�.
	fromax = adr[sum];
	printf("\n");
	int up = 8, down = 8, right = 8, left = 8;//�����¿� ��Ģ�� ���� �ִ� �Ÿ��� �����ϴ� ������.
	int rightnum = 0, leftnum = 0;//���� row���� ���ʰ� �����ʿ� ���� ��� breeding points�� �ִ��� �˷��ִ� ����.

	for (b = 0; b < (fromax % 10); b++)//���� ���� ����. �ִܰŸ� ����
	{
		if (map[fromax / 10][b] != 0)
		{
			leftnum++;
			if (fromax % 10 - b < left)	left = fromax % 10 - b;
		}
	}
	for (b = (fromax % 10) + 1; b < column; b++)//������ ���� ����, �ִܰŸ� ����
	{
		if (map[fromax / 10][b] != 0)
		{
			rightnum++;
			if (b - fromax % 10 < right)	right = b - fromax % 10;
		}
	}


	for (a = 0; a < (fromax / 10); a++)//���� �ִܰŸ� ����.
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] != 0)
			{
				if (up > fromax / 10 - a)
					up = fromax / 10 - a;
			}
		}
	}

	for (a = (fromax / 10) + 1; a < row; a++)//�Ʒ��� �ִܰŸ� ����.
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] != 0)
			{
				if (down > a - fromax / 10)
					down = a - fromax / 10;
			}
		}
	}//������� distance ����.

	num = 0;
	if (up != 8)//���ʿ� �ƹ��͵� ���ٸ� up�� �״�� 8�� ���̹Ƿ� pass.
	{
		for (b = 0; b < column; b++)//8�� �ƴϸ� ���� �ִܰŸ� row�� �ִ� ��� breeding points�� ��ȣ �ű��.
		{
			if (map[fromax / 10 - up][b] != 0)
			{
				printf("%d (%d, %d)\n", ++num, fromax / 10 - up, b);
				choice[num] = &antCounts[fromax / 10 - up][b];
				adr[num] = 10 * (fromax / 10 - up) + b;
			}
		}
	}
	if (down != 8)//�Ʒ��ʿ� �ƹ��͵� ���ٸ� down�� �״�� 8�� ���̹Ƿ� pass.
	{
		for (b = 0; b < column; b++)//8�� �ƴϸ� �Ʒ��� �ִܰŸ� row�� �ִ� ��� breeding points�� ��ȣ �ű��.
		{
			if (map[fromax / 10 + down][b] != 0)
			{
				printf("%d (%d, %d)\n", ++num, fromax / 10 + down, b);
				choice[num] = &antCounts[fromax / 10 + down][b];
				adr[num] = 10 * (fromax / 10 + down) + b;
			}
		}//���Ʒ� �����ű��
	}


	if (leftnum + rightnum >= 2)//�� row�� breeding point�� 3�� �̻��̸�,
	{
		if (leftnum == 0)//���� �ٸ� points�� ��� �����ʿ� ������ �ִܰŸ� �ϳ��� �� �� ����.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 + right);
			choice[num] = &antCounts[fromax / 10][fromax % 10 + right];
			adr[num] = 10 * (fromax / 10) + fromax % 10 + right;
		}
		else if (rightnum == 0)//���������� �ٸ� points�� ��� ���ʿ� ������ �ִܰŸ� �ϳ��� �� �� ����.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 - left);
			choice[num] = &antCounts[fromax / 10][fromax % 10 - left];
			adr[num] = 10 * (fromax / 10) + fromax % 10 - left;
		}
		else//�� �� �ƴϸ� ���� �ִܰŸ� �ϳ��� ��ȣ �ű��.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 - left);
			choice[num] = &antCounts[fromax / 10][fromax % 10 - left];
			adr[num] = 10 * (fromax / 10) + fromax % 10 - left;
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 + right);
			choice[num] = &antCounts[fromax / 10][fromax % 10 + right];
			adr[num] = 10 * (fromax) / 10 + fromax % 10 + right;
		}
	}
	else//3������ ���� �ִٸ� �� �ٿ��� ���� ����� ������ ��� ���� ã�Ƽ� ��ȣ �ű��.
	{
		for (b = 0; b < column; b++)
		{
			if (b == fromax % 10)
				continue;
			if (map[fromax / 10][b] != 0)
			{
				printf("%d (%d, %d)\n", ++num, fromax / 10, b);
				choice[num] = &antCounts[fromax / 10][b];
				adr[num] = 10 * (fromax / 10) + b;
			}
		}
	}
	printf("where ants go? ");
	for (a = 0; a < 100; a++)
	{
		N[a] = '\0';
	}
	sum = 0, check = 0;
	while (1)
	{
		scanf("%s", a);
		for (a = 0; a < 100; a++)
		{
			if (N[a] == '\0')
			{
				break;
			}
			else if (N[a] > 57 || N[a] < 48)
			{
				//���ڰ� ������
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			printf("Please type an integer from 1 to %d : ", num);
		}
		else
		{
			for (b = 0; b < a; b++)
			{
				sum = 10 * sum + (N[b] - 48);
			}

			if (sum > 0 && sum < num)
			{
				break;
			}
			else
				printf("Please type an integer from 1 to %d : ", num);
		}
	}
	to = choice[sum];//������ antCounts�� �ּ�
	toax = adr[sum];//������ ��ǥ��
	land = &map[toax / 10][toax % 10];//������ map�� �ּ�
	printf("\n");


	printf("How many ants go? (0~%d)", *from - 1);//���� �� ����.
	sum = 0, check = 0;
	while (1)
	{
		scanf("%s", a);
		for (a = 0; a < 100; a++)
		{
			if (N[a] == '\0')
			{
				break;
			}
			else if (N[a] > 57 || N[a] < 48)
			{
				//���ڰ� ������
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			printf("Please type an integer from 0 to %d : ", (*from - 1));
		}
		else
		{
			for (b = 0; b < a; b++)
			{
				sum = 10 * sum + (N[b] - 48);
			}

			if (sum >= 0 && sum < (*from - 1))
			{
				break;
			}
			else
				printf("Please type an integer from 0 to %d : ", (*from - 1));
		}
	}
	userN = sum;//���� ���� userN�� ����.
	//�������� ����



	/*��ǻ�ʹ� rand�Լ��� ���� ������ ����ó�� ����, printf�� ��� ���ְ� num�� �� �����ؼ� 
	user ���� �Ȱ��� �ڵ����ָ� �ȴ�.*/



	num = 0;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 'B')
			{
				num++;
				choice[num] = &antCounts[a][b];
				adr[num] = 10 * a + b;
			}
		}
	}
	x = rand() % num + 1;
	comfrom = choice[x];
	comfromax = adr[x];
	up = 8, down = 8, right = 8, left = 8;
	rightnum = 0, leftnum = 0;

	for (b = 0; b < (comfromax % 10); b++)
	{
		if (map[comfromax / 10][b] != 0)
		{
			leftnum++;
			if (comfromax % 10 - b < left)	left = comfromax % 10 - b;
		}
	}

	for (b = (comfromax % 10) + 1; b < column; b++)
	{
		if (map[a][b] != 0)
		{
			rightnum++;
			if (b - comfromax % 10 < right)	right = b - comfromax % 10;
		}
	}


	for (a = 0; a < (comfromax / 10); a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] != 0)
			{
				if (up > comfromax / 10 - a)
					up = comfromax / 10 - a;
			}
		}
	}

	for (a = (comfromax / 10) + 1; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] != 0)
			{
				if (down > a - comfromax / 10)
					down = a - comfromax / 10;
			}
		}
	}//������� distance ����.

	num = 0;
	if (up != 8)
	{
		for (b = 0; b < column; b++)
		{
			if (map[comfromax / 10 - up][b] != 0)
			{
				num++;
				choice[num] = &antCounts[comfromax / 10 - up][b];
				adr[num] = 10 * (comfromax / 10 - up) + b;
			}
		}
	}
	if (down != 8)
	{
		for (b = 0; b < column; b++)
		{
			if (map[comfromax / 10 + down][b] != 0)
			{
				num++;
				choice[num] = &antCounts[comfromax / 10 + down][b];
				adr[num] = 10 * (comfromax / 10 + down) + b;
			}
		}//���Ʒ� �����ű��
	}
	if (leftnum + rightnum >= 2)
	{
		if (leftnum == 0)
		{
			num++;
			choice[num] = &antCounts[comfromax / 10][comfromax % 10 + right];
			adr[num] = 10 * (comfromax / 10) + comfromax % 10 + right;
		}
		else if (rightnum == 0)
		{
			num++;
			choice[num] = &antCounts[comfromax / 10][comfromax % 10 - left];
			adr[num] = 10 * (comfromax / 10) + comfromax % 10 - left;
		}
		else
		{
			num++;
			choice[num] = &antCounts[comfromax / 10][comfromax % 10 - left];
			adr[num] = 10 * (comfromax / 10) + comfromax % 10 - left;
			num++;
			choice[num] = &antCounts[comfromax / 10][comfromax % 10 + right];
			adr[num] = 10 * (comfromax / 10) + comfromax % 10 + right;
		}
	}
	else
	{
		for (b = 0; b < column; b++)
		{
			if (b == comfromax % 10)
				continue;

			if (map[comfromax / 10][b] != 0)
			{
				num++;
				choice[num] = &antCounts[comfromax / 10][b];
				adr[num] = 10 * (comfromax / 10) + b;
			}
		}
	}
		//printf("where ants go? ");
		x = rand() % num + 1;
		comto = choice[x];
		comtoax = adr[x];
		comland = &map[comtoax / 10][comtoax % 10];
		printf("\n");
		comN = rand() % (*comfrom);//���� ���� comN�� �ֱ�.


		printf("YOU moves %d ants from (%d, %d) to (%d, %d)\n",userN, fromax / 10, fromax % 10, toax / 10, toax % 10);
		printf("Computer moves %d ants from (%d, %d) to (%d, %d)\n", comN, comfromax / 10, comfromax % 10, comtoax / 10, comtoax % 10);
		//�̹� �� ��Ȳ ����ϱ�.
		fight(from, to, comfrom, comto, userN, comN, land, comland);//���̵� �ο�� �Լ�.
	
}

void fight(int* from, int* to, int* comfrom, int* comto, int userN, int comN, char* land, char* comland)//���̵� �ο�� �Լ�.
{
	*from = *from - userN;
	*comfrom = *comfrom - comN;
	//�ϴ� ���̵��� ����Ѵ�.
	if ((land == comland) && (*land == 'N'))//���� �߸��������� ���� �����ٸ�...
	{
		if (userN > comN)
		{
			*to = userN - comN;
			*land = 'A';
		}
		else if (userN < comN)
		{
			*to = comN - userN;
			*land = 'B';
		}
	}//���� ���� ���� ���� ���� �� ���̴�.

	else//�� �̿��� ���
	{
		if (*land == 'A')
			* to = *to + userN;
		else
			*to = *to - userN;
		if (*comland == 'B')
			* comto = *comto + comN;
		else
			*comto = *comto - comN;
		//���� ���� ���� ���� ��������, �ٸ� ���� ���� ���� ������.

		if (*to == 0)
			* land = 'N';//�������� ���� ���� 0������ �Ǹ� �߸������� �ȴ�.
		else if (*to < 0)
		{
			if (*land == 'B')
			{
				*land = 'A';
				*to = -*to;
			}
			else
			{
				*to = -*to;
				*land = 'A';
			}
		}
		if (*comto == 0)
			* comland = 'N';
		else if (*comto < 0)
		{
			if (*comland == 'B')
			{
				*comland = 'A';
				*comto = -*comto;
			}
			else
			{
				*comto = -*comto;
				*comland = 'B';
			}
		}//���� ���� ������ �ȴٸ� �� ���� ���� ��ȯ�ȴ�.
	}
}

int fight_2(char A, char B)//���и� �Ǵ��ϴ� �Լ�.
{
	if (A == 'A' && B == 'B')//���� ���� �� ����.
		return 0;
	else if (A == 'A')//�¸�
		return 1;
	else if (B == 'B')//�й�
		return 2;
	else//���º�
		return 3;
}
void breeding(int ant[][MAXCOLUMN], int row, int column)//���� �����ϴ� �Լ�.
{
	int a, b;
	printf("\nants breeding ~_~\n\n");//yeah~~
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)//breeding points���� ���� ���� 1�� �þ��.
		{
			if (ant[a][b] != 0)
				ant[a][b]++;
		}
	}
	ant[0][0]++;
	ant[row - 1][column - 1]++;//�� ���� basement������ 2�� �þ�ϱ� �߰�.
}

void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column, int gameResult)//������ ����� reply.txt�� �����ϴ� �Լ�.
{
	int user = 0, com = 0, userant = 0, comant = 0, a, b;
	//user�� com�� ���� ����, userant�� comant�� ���� ��.
	char result;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 'A')
			{
				user++;//A�� �� �߰�.
				userant = userant + antCounts[a][b];//A�� ���� ���� ���� �߰�.
			}
			else if (map[a][b] == 'B')
			{
				com++;//B�� �� �߰�
				comant = comant + antCounts[a][b];//B�� ���� ���� ���� �߰�.
			}
		}
	}
	switch (gameResult)//������ �̰���� ������ ���º����� �Ǵ�.
	{
	case 1:	result = 'W';//�¸�
		break;
	case 2:	result = 'L';//�й�
		break;
	case 3: result = 'D';//���º�
		break;
	}
	FILE* out = NULL;//���� ���� �����.
	out = fopen("reply.txt", "w");//���� ���� ���
	fprintf(out, "%c\n", result);//�º� ����� �ְ�,
	fprintf(out, "%d %d\n%d %d", user, userant, com, comant);//user�� com�� �� ��, ���� ���� ǥ��.
	fclose(out);//���� ���� �ݱ�.
}


int main()
{
	printf("\n\n***********************");
	printf(RED"\n linux user mode ANTs");
	printf(YELLOW"\n          VS");
	printf(BLUE"\nlinux kernel mode ANTs"RES);
	printf("\n***********************");
	printf("\nPress Enter to start game : ");
	getchar();
	system("clear");//�ܼ� â �ʱ�ȭ �� ���� ����
	srand(time(NULL));//�����Լ��� �� ���̱� ������ ����.
	char map[MAXROW][MAXCOLUMN] = { 0 };
	int ant[MAXROW][MAXCOLUMN] = { 0 };
	int row = 0, column = 0, regionCount = 0;
	int a, b, k;
	char result;
	if (ReadMap(map, ant, &row, &column, &regionCount) == 0)//���� �޾ƿ�.
		return  0;
	PrintMap(map, row, column);
	printf("---------------------------------------\n");
	PrintAntCounts(map, ant, row, column);//���� ���� �˷��ְ�
	while (1)//������ ��.
	{
		move(map, ant, row, column, regionCount);//���� �����̰� �ο�.
		k = fight_2(map[0][0], map[row - 1][column - 1]);//���� ���� Ȯ��
		if (k != 0)//k == 0�̸� ���, �ƴϸ� ���� ������ ���� break;
			break;
		printf("\nants fight each other!\n\n");//�ο��!
		printf("---------------------------------------\n");
		PrintMap(map, row, column);
		printf("---------------------------------------\n");//�ο� �� ��Ȳ �����ֱ�
		PrintAntCounts(map, ant, row, column);
		breeding(ant, row, column);//�����Ѵ�!
		PrintMap(map, row, column);
		printf("---------------------------------------\n");//���� �� ��Ȳ �����ֱ�-�ٽ� move�� ���ư�.
		PrintAntCounts(map, ant, row, column);
	}//������ �������
	system("clear");//���а� �������� �ܼ� �ʱ�ȭ
	if (k == 1)//�������� Ȯ���� ���� ���� �ֿܼ� ���.
	{
		printf("YOU WIN\n");
	}
	else if (k == 2)
	{
		printf("YOU LOSE\n");
	}
	else if (k == 3)
	{
		printf("DRAW\n");
	}
	printf("\n\n");
	PrintMap(map, row, column);
	printf("---------------------------------------\n");//�������� Ȯ���� ���� ��� �ֿܼ� ���.
	PrintAntCounts(map, ant, row, column);
	PrintResult(map, ant, row, column, k);//����� reply.txt�� ����.
}