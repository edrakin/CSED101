#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define WIDTH 60 
#define MAX_LINES 1000
#define MAX_FILE_NAME 30



void print(char** str, int i, int check)//10�پ� Ȥ�� ������ ������ ����ϴ� �Լ� 
										//i���� ����ؾ� �ϴ� 10�� �� �� ù ��° ���� index�� �����. 
{
	//system("cls");
	int k = 0;
	if (check < 0)//10�پ� ������ ��� 10�� ���  
	{
		for (k = i; k < i + 10; k++)
		{
			printf("%s\n", str[k]);
		}
		printf("==================================================[%d, %d]\nf, b, o, q> ", i + 1, i + 10);
	}
	else//�� ������ check�� �ְ� �׸�ŭ ���  
	{
		for (k = i; k < i + check; k++)
		{
			printf("%s\n", str[k]);
		}
		printf("==================================================[%d, %d]\nf, b, o, q> ", i + 1, i + check);
	}
}

int ff(char** str, int i, int length)//10�� ���� ����ϴ� �Լ� 
{
	if (i + 10 > length)///������ ���������� ��� 
	{
		print(str, i, length - i);//����� ���� ����ϰ�, 
		return i;//���� �� index ��ȯ. 
	}
	else if (i + 20 > length)//���������� �� ��° ���������� ���. 
	{
		print(str, i + 10, length - i - 10);//�� ������ ����� ����ϰ�. 
		return i + 10;//index�� 10�� ���ؼ� ��ȯ. 
	}
	print(str, i + 10, -1);//�� �ܿ��� �״��� �������� �Ѿ��, 
	return i + 10;//index�� 10�� ���ؼ� ��ȯ. 
}


int bb(char** str, int i, int length)//10�� �ڸ� ����ϴ� �Լ�. 
{
	if (length < 11)//Ȥ�� ��ü ���� 10�� ������ ���. 
	{
		print(str, i, length);//���� ������ �ݺ�. 
		return i;
	}
	if (i == 0)//ù �������� ���. 
	{
		print(str, i, -1);//���� ������ �ݺ�. 
		return i;
	}
	print(str, i - 10, -1);//�� �̿��� ���. 
	return i - 10;//10�� ���� ���. 
}

int oo(char** phrase, int length, int* page, FILE *infile)//���� ��ü �Լ�. 
{
	int a, len = 0;
	infile = NULL;
	printf("filename: ");
	getchar();//���ۿ� ���� ���� fboq ���� ó�� 
	char changed[MAX_FILE_NAME + 1]; 
	gets(changed);//���ο� ���� �̸� �ޱ� 

	infile = fopen(changed, "r");
	if (infile == NULL)//���� �Է¹ޱ� ������ ���. 
	{
		printf("Unable to open %s\nPress Enter to continue...\n", changed);
		if (length > 10)
			print(phrase, *page, -1); 
		else
			print(phrase, *page, length);//���� �������� �״�� ����ϰ�, 
		return length;//�׳� �Լ� ���� 
	}
	
	//���� �Է� ���� 
	for (a = 0; a < length; a++)
		free(phrase[a]);//���ݱ��� �Ҵ��Ѱ� ��� �����. 
	len = Readtxt(phrase, infile);//���ο� ���� �Է¹ޱ�. 
	*page = 0;//�������� 0���� �ٷ� �ʱ�ȭ. 
	if (len > 10)
		print(phrase, *page, -1);
	else
		print(phrase, *page, len);//���� �������� ����ϰ�, 
	fclose(infile);//���� �ݰ�, 
	return len;//���ο� �� ���̸� ������. 
}

int Readtxt(char** phrase, FILE* infile)//���� �ް� �д� �Լ�. 
{
	int wrapLen = 0, joolLen = 0, i = 0, a, b;//���左 ���ڿ��� ũ��, ���� ���� ����. 
	char* wrap;//���左 ��ġ ����. 
	char last, first;//���� ���� ������, �״��� ���� ù��° ���� ����. 
	int EnterNum = 0;//�� �ٿ� ���� ����. 
	int check = 0;
	int k = 0;
	char jool[WIDTH + 2];//�ϴ� ���⿡ ����. 
	while (1)
	{
		check = 0;
		EnterNum = 0;
		k = 0;
		for (a = 0; a < wrapLen; a++)//���左 ũ�⸸ŭ �Է¹���. 
			jool[a] = wrap[a];
		for (a = wrapLen; a < WIDTH + 2; a++)//�� �ڿ� �ִ� �͵� ��� �ʱ�ȭ. 
 			jool[a] = '\0';
		for (a = wrapLen; a < WIDTH + 1; a++)//���左 ���� �ں��� 61��° ���ڱ��� �Է¹���. 
		{
			if (fscanf(infile, "%c", &jool[a]) == EOF)//Ȥ�� ������ �о����� 
			{
				check = 3;//�������� ����. 
				break;
			}
		}
		if (check == 3)//���� �� �о����� 
		{
			phrase[i] = (char*)calloc(a + 1, sizeof(char));//���ݱ��� ���� �� ũ�⸸ŭ �Ҵ�. 
			for (b = 0; b < a; b++)
				phrase[i][b] = jool[b];//�׸��� ����. 
			phrase[i][a] = '\0';//������ �ι���. 
			i++;//�� ���̴� ��Ȯ�ϰ� �� �ֱ�. 
			break;//while�� Ż��. 
		}

		first = jool[WIDTH];// ���� �� ù ���� ����. 
		last = jool[WIDTH - 1];//���� �� ������ ���� ����. 
		wrapLen = 0;
		joolLen = 0;

		for (a = 0; a < WIDTH + 1; a++)//���� ���� ����. 
		{
			if (jool[a] == '\n')
			{
				EnterNum++;
			}
		}

		if (EnterNum == 1 && jool[WIDTH] == '\n')//60���� �����̰� first�� ���͸� 
		{
			phrase[i] = (char*)calloc(WIDTH + 1, sizeof(char));//60�� ���ڷ� �� �� �����, 
			for (a = 0; a < WIDTH; a++)
				phrase[i][a] = jool[a];
			phrase[i][WIDTH] = '\0';
			i++;
			phrase[i] = (char*)calloc(60, sizeof(char));//��  ���� �� �����. ////////////////////////
		}
		else if (EnterNum > 0)//�̿ܿ� ���Ͱ� ������  
		{
			for (a = 0; a < WIDTH + 1; a++)
			{
				if (jool[a] == '\n')
				{
					phrase[i] = (char*)calloc(a - k + 2, sizeof(char));//���� �ٸ�ŭ ���� �ٸ��� �Ҵ�. 
					for (b = k; b < a; b++)
						phrase[i][b - k] = jool[b];//�׸��� �Է�. 
					phrase[i][a - k] = '\0';
					k = a + 1;
					i++;
				}
			}//�����ϴϱ� ���� ������ ����
			wrap = &jool[k];//������ ���� �ڿ� ���� ���� ���左���� �ν�. 
			wrapLen = strlen(wrap);
		}
		else//���Ͱ� ���� ���. 
		{
			for (a = 0; a < WIDTH; a++)//����ó���� ���� �־���. 
			{
				if (jool[a] == ' ')
				{
					check = 5;//60���� ���Ⱑ ������  
				}
			}
			if (check != 5 && first == ' ')//�ƹ��͵� ���� �ʰ� �Ѿ. 
			{
				joolLen = WIDTH;
				wrapLen = 0;
			}
			else if (check != 5 && first != ' ')//61���� �̾��� ������ ��¿ �� ���� 60�� �� �ٷ� �ϰ� 1���� ¥��. 
			{
				joolLen = WIDTH;
				wrapLen = 1;
				wrap = &jool[WIDTH];
			}
			else if (first != ' ' && last != ' ')//�� �̿ܿ� �� �� ��� ������ ����  
			{
				wrap = strrchr(jool, ' ') + 1;//�� �ܾ� �� ���� wrap���� ���, 
				wrapLen = strlen(wrap);//���� ���̸� ��. 
				*(wrap - 1) = '\0';//���� �� �����̽��ٴ� �ι��ڷ� �ز���. 
				joolLen = strlen(jool);//�� ���� ���. 
			}
			else if (first == ' ' && last != ' ')//60���� �ؼ� �ܾ ������  
			{
				joolLen = WIDTH;//�ű���� ¥��. 
				wrapLen = 0;//������ ����. 
			}
			else if (first != ' ' && last == ' ')//59���� �ܾ ������ first���� �ܾ �����ϸ� 
			{
				joolLen = WIDTH - 1;//�ٿ� last ���� ����. 
				wrapLen = 1;//�� �����ٿ� first ����. 
				wrap = &jool[WIDTH];
			}
			else//�Ѵ� �����̸�  
			{
				joolLen = WIDTH - 1;
				wrapLen = 0;
			}
			phrase[i] = (char*)calloc(joolLen + 2, sizeof(char));//�� ���̸�ŭ �޸� �Ҵ�. (Ȥ�� ���� ��¦ �����Ӱ� 
			for (a = 0; a < joolLen; a++)//�׸��� ����. 
				phrase[i][a] = jool[a];
			phrase[i][joolLen] = '\0';//����������  �ι���. 
			i++;
		}

	}
	return i;//�׸��� �� ���� ������. 
}

int main()
{
	FILE* infile = NULL;
	while (1)//���� �����ö����� �ݺ�  
	{
		printf("* Text File Viewer *\nfilename: ");
		char name[MAX_FILE_NAME + 1];
		gets(name);//���� �̸� �ޱ�. 

		infile = fopen(name, "r");
		if (infile == NULL)//���� �������� �ݺ�. 
		{
			printf("Unable to open %s\nPress Enter to continue...", name);
			getchar();
			system("cls");
			continue;
		}
		break;
	}
	

	char* phrase[MAX_LINES + 1];//txt ���� ���� ������ �迭 ����. 
	int length;//���� ���� ���� ����. 
	length = Readtxt(phrase, infile);//txt ���� �ޱ�. 
	fclose(infile);//���� �ݱ�. 

	char fboq; 
	int page = 0;//���� �� ��° �ٿ� �ִ��� �˷���. 
	if(length>10)
		print(phrase, page, -1);
	else
		print(phrase, page, length);//�ʱ� ȭ�� ���. 
	while (1)//txt ����ϱ�
	{
		scanf("%c", &fboq);//������ �� ������ �޾Ƽ�. 
		if (fboq == 'f')
			page = ff(phrase, page, length);//���� ����� �ϰ�, 
		else if (fboq == 'b')
			page = bb(phrase, page, length);
		else if (fboq == 'o')
			length = oo(phrase, length, &page, infile);
		else  if (fboq == 'q')//q ������ break; 
			break;
	}

	int i;//�������� �޸� �Ҵ� ����. 
	for (i = 0; i < length; i++)
	{
		free(phrase[i]);
	}
	return 0; 
}
