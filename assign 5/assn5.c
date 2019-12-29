#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"user.h"
#include"trans.h"
#include"block.h"

void help();
void smalling(char* x);

int main()
{
	LIST_U ulist;//user ��ũ�� ����Ʈ ����
	ulist.count = 0;
	ulist.head = NULL;
	ulist.tail = NULL;
	LIST_T tlist;//transaction ��ũ�� ����Ʈ ����
	tlist.count = 0;
	tlist.head = NULL;
	tlist.tail = NULL;
	LIST_B blist;//block ��ũ�� ����Ʈ ����
	blist.count = 0;
	blist.head = NULL;
	blist.tail = NULL;

	printf("-----------------------------\n");
	printf("�� Mini Bitcoin Simulation ��\n");
	printf("-----------------------------\n");
	USER* manager = NULL;//��� ���� ����ڸ� ����Ű�� ������
	USER* nothing = (USER*)malloc(sizeof(USER));//��� special transaction���� ����� ������
	strcpy(nothing->name, "Nothing");//�׷��� �̸��� Nothing���� �־���.
	help();//�ʱ� ȭ�� ����
	char manage[10] = "/0";//��ɾ� �޴� ���ڿ�
	while (1)
	{
		printf("\n>>");
		gets(manage);//��ɾ� �Է�
		smalling(manage);//�ҹ��� ��ȯ
		if (strcmp(manage, "help") == 0)
			help();
		else if (strcmp(manage, "useradd") == 0)
			useradd(&ulist, &manager);
		else if (strcmp(manage, "userlist") == 0)
			userlist(&ulist, manager);
		else if (strcmp(manage, "getuser") == 0)
			getuser(manager);
		else if (strcmp(manage, "chuser") == 0)
			chuser(&ulist, &manager);
		else if (strcmp(manage, "mkgenblk") == 0)
			mkgenblk(manager, &blist, nothing);
		else if (strcmp(manage, "mktx") == 0)
			mktx(manager, &tlist, &ulist);
		else if (strcmp(manage, "txlist") == 0)
			txlist(&tlist);
		else if (strcmp(manage, "mkblk") == 0)
			mkblk(manager, &blist, &ulist, &tlist, nothing);
		else if (strcmp(manage, "blklist") == 0)
			blklist(&blist);
		else if (strcmp(manage, "quit") == 0)//�̰Ÿ� ����.
			break;
		else
			printf("wrong command!\n");
	}


	int i;
	FILE* last_pang = NULL;//���������� �������ֱ�. �������� ������Ƽ� last_pang�̶� ���� ��
	last_pang = fopen("BlockChain.txt", "w");
	NODE_B* b;
	for (b = blist.head; b; b = b->next)//blklist���� ����� ����̶� �Ȱ��� txt���Ͽ� ������.
	{
		fprintf(last_pang, "block\n");
		fprintf(last_pang, "Sender : %s\nReceiver : %s\nCoin : %d\n", b->data.special.sender->name, b->data.special.receiver->name, 100);
		free((NODE_T*)(&(b->data.special)));//����� ���� �ٷιٷ� �Ҵ� ������.
		for (i = 0; i < b->data.trans_num; i++)
		{
			fprintf(last_pang, "Sender : %s\nReceiver : %s\nCoin : %d\n", b->data.trans[i].sender->name, b->data.trans[i].receiver->name, b->data.trans[i].trans_coin);
			free((NODE_T*)(&(b->data.trans[i])));//����� ���� �ٷιٷ� �Ҵ� ������.
		}
	}
	fclose(last_pang);//���� �ݱ�


	last_pang = fopen("Transaction.txt", "w");//�����ִ� �ŷ� ����ϱ�
	if (tlist.head == NULL)
		fprintf(last_pang, "There is no left transaction");//Ȥ�� �ƹ��͵� �ȳ��������� ģ���ϰ� �־���.
	else//�ƴϸ� txlist���� �� ������ ������.
	{
		NODE_T* xx;
		NODE_T* ptr;
		fprintf(last_pang, "Transaction");
		for (ptr = tlist.head; ptr; xx = ptr, ptr = ptr->next, free(xx))//������ ���� �ٷιٷ� �Ҵ� ���
			fprintf(last_pang, "sender : %s\nreceiver : %s\nCoin : %d\n", ptr->data.sender, ptr->data.receiver, ptr->data.trans_coin);
	}
	fclose(last_pang);//���� �ݱ�


	last_pang = fopen("User.txt", "w");//��� �����ֱ�

	fprintf(last_pang, "User\n");
	if (manager == NULL)
		fprintf(last_pang, "There was no user\n");//Ȥ�� �ƹ��͵� �ȳ��������� ģ���ϰ� �־���.
	else 
	{
		NODE_U* xxx;
		NODE_U* ptr = NULL;
		int i = 0;
		for (ptr = ulist.head; ptr; xxx = ptr, ptr = ptr->next, free(xxx))//������ ���� �ٷιٷ� �Ҵ� ���
		{
			i++;
			fprintf(last_pang, "Name : %s\n   Coin : %d\n", ptr->data.name, ptr->data.coin);
		}
	}
	fclose(last_pang);
}

void help()//print�� �ϴ� �Լ�.
{
	printf("help: ��ɾ� ��� ����\n");
	printf("useradd: ����� ��� \n");
	printf("userlist: ��ϵ� ��� ����� ����\n");
	printf("getUser: ���� ����� Ȯ�� \n");
	printf("chuser: ����� ���� \n");
	printf("mkGenBLK: Genesis Block ����\n");
	printf("mkTx: Transaction ����\n");
	printf("Txlist: Transaction ��� ����\n");
	printf("mkBLK: Block ����\n");
	printf("blklist: BlockChain(�ŷ� ����) Ȯ��\n");
	printf("quit: ���α׷� ���� \n");
	printf("-----------------------------\n");
}

void smalling(char* x)//�ҹ��ڷ� �ٲ��ִ� �Լ�.
{
	int i, len;
	len = strlen(x);
	for (i = 0; i < len; i++)//�ѱ��ھ� ��� Ȯ��
	{
		if (*(x + i) > 64 && *(x + i) < 91)//�빮�ڸ� �ҹ��ڷ� �ٲ���. Ư�����ڸ� �𸣰���
		{
			*(x + i) = *(x + i) + 32;
		}
	}
}










