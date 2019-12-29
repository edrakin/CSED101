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


int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int* row, int* column, int* regionCount)//파일 받아서 breeding points 찾는 함수
{
	FILE* infile = NULL;//map.txt 받을 파일변수.
	int x, y;
	infile = fopen("map.txt", "r");
	if (infile == NULL)//파일이 없으면 에러 메시지와 함께 프로그램 종료
	{
		printf("Error--No file\n\t\tprogram closed");
		return 0;
	}
	fscanf(infile, "%d%d%d", row, column, regionCount);//맵의 가로세로, 땅 개수 받기

	map[0][0] = 'A';
	map[*row - 1][*column - 1] = 'B';
	antCounts[0][0] = 10;
	antCounts[*row - 1][*column - 1] = 10;//A와 B팀 basement 지정하기

	while (fscanf(infile, "%d%d", &x, &y) != EOF)//중립 구역 좌표 받고 'N' 넣기
	{
		map[x][y] = 'N';
	}
	fclose(infile);//파일에서 뽑아낼 건 다 뽑았으니 처리
	return 1;
}





void PrintMap(char map[][MAXCOLUMN], int row, int column)//맵에서 어느 개미의 구역인지 표시하는 함수
{
	int a, b;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 0)
				printf("  0");
			else if (map[a][b] == 'A')	printf(BLUE "  A" RES);//A팀이면 파란색으로 표시
			else if (map[a][b] == 'B')	printf(RED "  B" RES);//B팀이면 빨간색으로 표시
			else printf(YELLOW "  N" RES);//중립구역은 노란색임.
		}
		printf("\n");
	}
}







void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int
	row, int column)//구역별 개미 개수 표시하는 함수
{
	int a, b;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 0)	printf("  0");
			else if (map[a][b] == 'A')//A팀 개미 수는 파란색
			{
				printf(BLUE);
				printf("%3d", antCounts[a][b]);
				printf(RES);
			}
			else if (map[a][b] == 'B')//B팀 개미 수는 빨간색
			{
				printf(RED);
				printf("%3d", antCounts[a][b]);
				printf(RES);
			}
			else printf(YELLOW "  0" RES);//중립구역은 노란색으로 0마리라고 표시
		}
		printf("\n");
	}
	printf("\n");
}







void move(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int
	row, int column, int region)//개미 이동하고, 싸우는 함수.
{
	int num = 0;
	int *from, *to, fromax, toax, *comfrom, *comto, comfromax, comtoax, userN, comN;
	//from과 to는 각각 보내는곳과 받는 곳의 주소, ax는 각각의 좌표값 암호화.
	//userN과 comN은 각각 보내는 개미의 수
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
			if (map[a][b] == 'A')//A팀 위치 스캔
			{
				printf("%d : (%d, %d)\n", ++num, a, b);//번호 매기고, 후보 목록의 주소는 choice에, 좌표값은 adr에 저장.
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
				//문자가 나왔음
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
		




	from = choice[sum];//개미가 출발하는 구역 주소.
	fromax = adr[sum];
	printf("\n");
	int up = 8, down = 8, right = 8, left = 8;//상하좌우 규칙에 따른 최단 거리를 저장하는 변수들.
	int rightnum = 0, leftnum = 0;//같은 row에서 왼쪽과 오른쪽에 각각 몇개의 breeding points가 있는지 알려주는 변수.

	for (b = 0; b < (fromax % 10); b++)//왼쪽 개수 세기. 최단거리 저장
	{
		if (map[fromax / 10][b] != 0)
		{
			leftnum++;
			if (fromax % 10 - b < left)	left = fromax % 10 - b;
		}
	}
	for (b = (fromax % 10) + 1; b < column; b++)//오른쪽 개수 세기, 최단거리 저장
	{
		if (map[fromax / 10][b] != 0)
		{
			rightnum++;
			if (b - fromax % 10 < right)	right = b - fromax % 10;
		}
	}


	for (a = 0; a < (fromax / 10); a++)//위쪽 최단거리 저장.
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

	for (a = (fromax / 10) + 1; a < row; a++)//아래쪽 최단거리 저장.
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] != 0)
			{
				if (down > a - fromax / 10)
					down = a - fromax / 10;
			}
		}
	}//여기까지 distance 구함.

	num = 0;
	if (up != 8)//위쪽에 아무것도 없다면 up은 그대로 8일 것이므로 pass.
	{
		for (b = 0; b < column; b++)//8이 아니면 위쪽 최단거리 row에 있는 모든 breeding points에 번호 매기기.
		{
			if (map[fromax / 10 - up][b] != 0)
			{
				printf("%d (%d, %d)\n", ++num, fromax / 10 - up, b);
				choice[num] = &antCounts[fromax / 10 - up][b];
				adr[num] = 10 * (fromax / 10 - up) + b;
			}
		}
	}
	if (down != 8)//아래쪽에 아무것도 없다면 down은 그대로 8일 것이므로 pass.
	{
		for (b = 0; b < column; b++)//8이 아니면 아래쪽 최단거리 row에 있는 모든 breeding points에 번호 매기기.
		{
			if (map[fromax / 10 + down][b] != 0)
			{
				printf("%d (%d, %d)\n", ++num, fromax / 10 + down, b);
				choice[num] = &antCounts[fromax / 10 + down][b];
				adr[num] = 10 * (fromax / 10 + down) + b;
			}
		}//위아래 순서매기기
	}


	if (leftnum + rightnum >= 2)//그 row에 breeding point가 3개 이상이면,
	{
		if (leftnum == 0)//만약 다른 points가 모두 오른쪽에 있으면 최단거리 하나만 갈 수 있음.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 + right);
			choice[num] = &antCounts[fromax / 10][fromax % 10 + right];
			adr[num] = 10 * (fromax / 10) + fromax % 10 + right;
		}
		else if (rightnum == 0)//마찬가지로 다른 points가 모두 왼쪽에 있으면 최단거리 하나만 갈 수 있음.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 - left);
			choice[num] = &antCounts[fromax / 10][fromax % 10 - left];
			adr[num] = 10 * (fromax / 10) + fromax % 10 - left;
		}
		else//둘 다 아니면 양쪽 최단거리 하나씩 번호 매기기.
		{
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 - left);
			choice[num] = &antCounts[fromax / 10][fromax % 10 - left];
			adr[num] = 10 * (fromax / 10) + fromax % 10 - left;
			printf("%d (%d, %d)\n", ++num, fromax / 10, fromax % 10 + right);
			choice[num] = &antCounts[fromax / 10][fromax % 10 + right];
			adr[num] = 10 * (fromax) / 10 + fromax % 10 + right;
		}
	}
	else//3개보다 적게 있다면 그 줄에서 현재 출발점 제외한 모든 곳을 찾아서 번호 매기기.
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
				//문자가 나왔음
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
	to = choice[sum];//도착지 antCounts의 주소
	toax = adr[sum];//도착지 좌표값
	land = &map[toax / 10][toax % 10];//도착지 map의 주소
	printf("\n");


	printf("How many ants go? (0~%d)", *from - 1);//개미 수 지정.
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
				//문자가 나왔음
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
	userN = sum;//개미 수를 userN에 넣음.
	//여까지가 유저



	/*컴퓨터는 rand함수를 쓰기 때문에 예외처리 없고, printf를 모두 없애고 num만 잘 지정해서 
	user 경우와 똑같이 코딩해주면 된다.*/



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
	}//여기까지 distance 구함.

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
		}//위아래 순서매기기
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
		comN = rand() % (*comfrom);//개미 수를 comN에 넣기.


		printf("YOU moves %d ants from (%d, %d) to (%d, %d)\n",userN, fromax / 10, fromax % 10, toax / 10, toax % 10);
		printf("Computer moves %d ants from (%d, %d) to (%d, %d)\n", comN, comfromax / 10, comfromax % 10, comtoax / 10, comtoax % 10);
		//이번 턴 상황 요약하기.
		fight(from, to, comfrom, comto, userN, comN, land, comland);//개미들 싸우는 함수.
	
}

void fight(int* from, int* to, int* comfrom, int* comto, int userN, int comN, char* land, char* comland)//개미들 싸우는 함수.
{
	*from = *from - userN;
	*comfrom = *comfrom - comN;
	//일단 개미들이 출발한다.
	if ((land == comland) && (*land == 'N'))//만약 중립구역에서 둘이 만난다면...
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
	}//개미 수가 많은 팀의 땅이 될 것이다.

	else//그 이외의 경우
	{
		if (*land == 'A')
			* to = *to + userN;
		else
			*to = *to - userN;
		if (*comland == 'B')
			* comto = *comto + comN;
		else
			*comto = *comto - comN;
		//같은 팀의 땅에 가면 더해지고, 다른 팀의 땅에 가면 빼진다.

		if (*to == 0)
			* land = 'N';//도착지의 개미 수가 0마리가 되면 중립구역이 된다.
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
		}//개미 수가 음수가 된다면 그 땅의 팀이 전환된다.
	}
}

int fight_2(char A, char B)//승패를 판단하는 함수.
{
	if (A == 'A' && B == 'B')//아직 게임 안 끝남.
		return 0;
	else if (A == 'A')//승리
		return 1;
	else if (B == 'B')//패배
		return 2;
	else//무승부
		return 3;
}
void breeding(int ant[][MAXCOLUMN], int row, int column)//개미 번식하는 함수.
{
	int a, b;
	printf("\nants breeding ~_~\n\n");//yeah~~
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)//breeding points에서 개미 수가 1씩 늘어난다.
		{
			if (ant[a][b] != 0)
				ant[a][b]++;
		}
	}
	ant[0][0]++;
	ant[row - 1][column - 1]++;//각 팀의 basement에서는 2씩 늘어나니까 추가.
}

void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column, int gameResult)//게임의 결과를 reply.txt에 저장하는 함수.
{
	int user = 0, com = 0, userant = 0, comant = 0, a, b;
	//user과 com은 땅의 개수, userant와 comant는 개미 수.
	char result;
	for (a = 0; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			if (map[a][b] == 'A')
			{
				user++;//A팀 땅 발견.
				userant = userant + antCounts[a][b];//A팀 땅의 개미 수를 추가.
			}
			else if (map[a][b] == 'B')
			{
				com++;//B팀 땅 발견
				comant = comant + antCounts[a][b];//B팀 땅의 개미 수를 추가.
			}
		}
	}
	switch (gameResult)//게임을 이겼는지 졌는지 무승부인지 판단.
	{
	case 1:	result = 'W';//승리
		break;
	case 2:	result = 'L';//패배
		break;
	case 3: result = 'D';//무승부
		break;
	}
	FILE* out = NULL;//파일 변수 만들기.
	out = fopen("reply.txt", "w");//쓰기 모드로 열어서
	fprintf(out, "%c\n", result);//승부 결과를 넣고,
	fprintf(out, "%d %d\n%d %d", user, userant, com, comant);//user와 com의 땅 수, 개미 수를 표기.
	fclose(out);//파일 변수 닫기.
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
	system("clear");//콘솔 창 초기화 후 게임 시작
	srand(time(NULL));//랜덤함수를 쓸 것이기 때문에 넣음.
	char map[MAXROW][MAXCOLUMN] = { 0 };
	int ant[MAXROW][MAXCOLUMN] = { 0 };
	int row = 0, column = 0, regionCount = 0;
	int a, b, k;
	char result;
	if (ReadMap(map, ant, &row, &column, &regionCount) == 0)//맵을 받아옴.
		return  0;
	PrintMap(map, row, column);
	printf("---------------------------------------\n");
	PrintAntCounts(map, ant, row, column);//현재 상태 알려주고
	while (1)//루프로 들어감.
	{
		move(map, ant, row, column, regionCount);//개미 움직이고 싸움.
		k = fight_2(map[0][0], map[row - 1][column - 1]);//승패 여부 확인
		if (k != 0)//k == 0이면 계속, 아니면 게임 끝내기 위해 break;
			break;
		printf("\nants fight each other!\n\n");//싸운다!
		printf("---------------------------------------\n");
		PrintMap(map, row, column);
		printf("---------------------------------------\n");//싸운 뒤 상황 보여주기
		PrintAntCounts(map, ant, row, column);
		breeding(ant, row, column);//번식한다!
		PrintMap(map, row, column);
		printf("---------------------------------------\n");//번식 후 상황 보여주기-다시 move로 돌아감.
		PrintAntCounts(map, ant, row, column);
	}//루프는 여기까지
	system("clear");//승패가 갈렸으니 콘솔 초기화
	if (k == 1)//마지막에 확인한 게임 승패 콘솔에 출력.
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
	printf("---------------------------------------\n");//마지막에 확인한 게임 결과 콘솔에 출력.
	PrintAntCounts(map, ant, row, column);
	PrintResult(map, ant, row, column, k);//결과를 reply.txt에 저장.
}