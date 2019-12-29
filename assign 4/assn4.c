#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define WIDTH 60 
#define MAX_LINES 1000
#define MAX_FILE_NAME 30



void print(char** str, int i, int check)//10줄씩 혹은 마지막 페이지 출력하는 함수 
										//i에는 출력해야 하는 10개 줄 중 첫 번째 줄의 index가 저장됨. 
{
	//system("cls");
	int k = 0;
	if (check < 0)//10줄씩 나오는 경우 10줄 출력  
	{
		for (k = i; k < i + 10; k++)
		{
			printf("%s\n", str[k]);
		}
		printf("==================================================[%d, %d]\nf, b, o, q> ", i + 1, i + 10);
	}
	else//줄 개수를 check에 넣고 그만큼 출력  
	{
		for (k = i; k < i + check; k++)
		{
			printf("%s\n", str[k]);
		}
		printf("==================================================[%d, %d]\nf, b, o, q> ", i + 1, i + check);
	}
}

int ff(char** str, int i, int length)//10줄 앞을 출력하는 함수 
{
	if (i + 10 > length)///마지막 페이지었을 경우 
	{
		print(str, i, length - i);//현재와 같이 출력하고, 
		return i;//같은 줄 index 반환. 
	}
	else if (i + 20 > length)//마지막에서 두 번째 페이지였을 경우. 
	{
		print(str, i + 10, length - i - 10);//줄 개수를 고려해 출력하고. 
		return i + 10;//index는 10을 더해서 반환. 
	}
	print(str, i + 10, -1);//그 외에는 그다음 페이지로 넘어가고, 
	return i + 10;//index는 10을 더해서 반환. 
}


int bb(char** str, int i, int length)//10줄 뒤를 출력하는 함수. 
{
	if (length < 11)//혹시 전체 줄이 10줄 이하일 경우. 
	{
		print(str, i, length);//같은 페이지 반복. 
		return i;
	}
	if (i == 0)//첫 페이지일 경우. 
	{
		print(str, i, -1);//같은 페이지 반복. 
		return i;
	}
	print(str, i - 10, -1);//그 이외의 경우. 
	return i - 10;//10줄 위를 출력. 
}

int oo(char** phrase, int length, int* page, FILE *infile)//파일 교체 함수. 
{
	int a, len = 0;
	infile = NULL;
	printf("filename: ");
	getchar();//버퍼에 남은 이전 fboq 등을 처리 
	char changed[MAX_FILE_NAME + 1]; 
	gets(changed);//새로운 파일 이름 받기 

	infile = fopen(changed, "r");
	if (infile == NULL)//파일 입력받기 실패한 경우. 
	{
		printf("Unable to open %s\nPress Enter to continue...\n", changed);
		if (length > 10)
			print(phrase, *page, -1); 
		else
			print(phrase, *page, length);//현재 페이지를 그대로 출력하고, 
		return length;//그냥 함수 종료 
	}
	
	//파일 입력 성공 
	for (a = 0; a < length; a++)
		free(phrase[a]);//지금까지 할당한거 모두 지우기. 
	len = Readtxt(phrase, infile);//새로운 파일 입력받기. 
	*page = 0;//페이지를 0번재 줄로 초기화. 
	if (len > 10)
		print(phrase, *page, -1);
	else
		print(phrase, *page, len);//현재 페이지를 출력하고, 
	fclose(infile);//파일 닫고, 
	return len;//새로운 줄 길이를 내보냄. 
}

int Readtxt(char** phrase, FILE* infile)//파일 받고 읽는 함수. 
{
	int wrapLen = 0, joolLen = 0, i = 0, a, b;//워드랩 문자열의 크기, 현재 줄의 길이. 
	char* wrap;//워드랩 위치 저장. 
	char last, first;//현재 줄의 마지막, 그다음 줄의 첫번째 문자 저장. 
	int EnterNum = 0;//그 줄에 엔터 개수. 
	int check = 0;
	int k = 0;
	char jool[WIDTH + 2];//일단 여기에 받음. 
	while (1)
	{
		check = 0;
		EnterNum = 0;
		k = 0;
		for (a = 0; a < wrapLen; a++)//워드랩 크기만큼 입력받음. 
			jool[a] = wrap[a];
		for (a = wrapLen; a < WIDTH + 2; a++)//그 뒤에 있던 것들 모두 초기화. 
 			jool[a] = '\0';
		for (a = wrapLen; a < WIDTH + 1; a++)//워드랩 길이 뒤부터 61번째 문자까지 입력받음. 
		{
			if (fscanf(infile, "%c", &jool[a]) == EOF)//혹시 끝까지 읽었으면 
			{
				check = 3;//빠져나갈 구멍. 
				break;
			}
		}
		if (check == 3)//파일 다 읽었으면 
		{
			phrase[i] = (char*)calloc(a + 1, sizeof(char));//지금까지 읽은 거 크기만큼 할당. 
			for (b = 0; b < a; b++)
				phrase[i][b] = jool[b];//그리고 저장. 
			phrase[i][a] = '\0';//끝에는 널문자. 
			i++;//줄 길이는 정확하게 세 주기. 
			break;//while문 탈출. 
		}

		first = jool[WIDTH];// 다음 줄 첫 문자 저장. 
		last = jool[WIDTH - 1];//현재 줄 마지막 문자 저장. 
		wrapLen = 0;
		joolLen = 0;

		for (a = 0; a < WIDTH + 1; a++)//엔터 개수 세기. 
		{
			if (jool[a] == '\n')
			{
				EnterNum++;
			}
		}

		if (EnterNum == 1 && jool[WIDTH] == '\n')//60개가 정상이고 first가 엔터면 
		{
			phrase[i] = (char*)calloc(WIDTH + 1, sizeof(char));//60개 문자로 한 줄 만들고, 
			for (a = 0; a < WIDTH; a++)
				phrase[i][a] = jool[a];
			phrase[i][WIDTH] = '\0';
			i++;
			phrase[i] = (char*)calloc(60, sizeof(char));//그  다음 줄 만들기. ////////////////////////
		}
		else if (EnterNum > 0)//이외에 엔터가 있으면  
		{
			for (a = 0; a < WIDTH + 1; a++)
			{
				if (jool[a] == '\n')
				{
					phrase[i] = (char*)calloc(a - k + 2, sizeof(char));//엔터 줄만큼 끊고 줄마다 할당. 
					for (b = k; b < a; b++)
						phrase[i][b - k] = jool[b];//그리고 입력. 
					phrase[i][a - k] = '\0';
					k = a + 1;
					i++;
				}
			}//복잡하니까 오류 날수도 있음
			wrap = &jool[k];//마지막 엔터 뒤에 남은 것은 워드랩으로 인식. 
			wrapLen = strlen(wrap);
		}
		else//엔터가 없는 경우. 
		{
			for (a = 0; a < WIDTH; a++)//예외처리를 위해 넣었음. 
			{
				if (jool[a] == ' ')
				{
					check = 5;//60개에 띄어쓰기가 없으면  
				}
			}
			if (check != 5 && first == ' ')//아무것도 하지 않고 넘어감. 
			{
				joolLen = WIDTH;
				wrapLen = 0;
			}
			else if (check != 5 && first != ' ')//61개가 이어져 있으면 어쩔 수 없이 60를 한 줄로 하고 1개를 짜름. 
			{
				joolLen = WIDTH;
				wrapLen = 1;
				wrap = &jool[WIDTH];
			}
			else if (first != ' ' && last != ' ')//그 이외에 두 개 모두 문자일 때는  
			{
				wrap = strrchr(jool, ' ') + 1;//그 단어 맨 앞을 wrap으로 잡고, 
				wrapLen = strlen(wrap);//문자 길이를 잼. 
				*(wrap - 1) = '\0';//문자 앞 스페이스바는 널문자로 해꿔줌. 
				joolLen = strlen(jool);//줄 길이 재고. 
			}
			else if (first == ' ' && last != ' ')//60까지 해서 단어가 끝나면  
			{
				joolLen = WIDTH;//거기까지 짜름. 
				wrapLen = 0;//공백은 없음. 
			}
			else if (first != ' ' && last == ' ')//59에서 단어가 끝나고 first에서 단어가 시작하면 
			{
				joolLen = WIDTH - 1;//줄에 last 빼고 저장. 
				wrapLen = 1;//그 다음줄에 first 저장. 
				wrap = &jool[WIDTH];
			}
			else//둘다 공백이면  
			{
				joolLen = WIDTH - 1;
				wrapLen = 0;
			}
			phrase[i] = (char*)calloc(joolLen + 2, sizeof(char));//줄 길이만큼 메모리 할당. (혹시 몰라서 살짝 여유롭게 
			for (a = 0; a < joolLen; a++)//그리고 저장. 
				phrase[i][a] = jool[a];
			phrase[i][joolLen] = '\0';//마지막에는  널문자. 
			i++;
		}

	}
	return i;//그리고 줄 길이 내보냄. 
}

int main()
{
	FILE* infile = NULL;
	while (1)//파일 가져올때까지 반복  
	{
		printf("* Text File Viewer *\nfilename: ");
		char name[MAX_FILE_NAME + 1];
		gets(name);//파일 이름 받기. 

		infile = fopen(name, "r");
		if (infile == NULL)//파일 못받으면 반복. 
		{
			printf("Unable to open %s\nPress Enter to continue...", name);
			getchar();
			system("cls");
			continue;
		}
		break;
	}
	

	char* phrase[MAX_LINES + 1];//txt 파일 받을 포인터 배열 생성. 
	int length;//길이 받을 변수 생성. 
	length = Readtxt(phrase, infile);//txt 파일 받기. 
	fclose(infile);//파일 닫기. 

	char fboq; 
	int page = 0;//현재 몇 번째 줄에 있는지 알려줌. 
	if(length>10)
		print(phrase, page, -1);
	else
		print(phrase, page, length);//초기 화면 출력. 
	while (1)//txt 출력하기
	{
		scanf("%c", &fboq);//무엇을 할 것인지 받아서. 
		if (fboq == 'f')
			page = ff(phrase, page, length);//각자 기능을 하고, 
		else if (fboq == 'b')
			page = bb(phrase, page, length);
		else if (fboq == 'o')
			length = oo(phrase, length, &page, infile);
		else  if (fboq == 'q')//q 누르면 break; 
			break;
	}

	int i;//마지막에 메모리 할당 해제. 
	for (i = 0; i < length; i++)
	{
		free(phrase[i]);
	}
	return 0; 
}
