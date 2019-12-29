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
	LIST_U ulist;//user 링크드 리스트 생성
	ulist.count = 0;
	ulist.head = NULL;
	ulist.tail = NULL;
	LIST_T tlist;//transaction 링크드 리스트 생성
	tlist.count = 0;
	tlist.head = NULL;
	tlist.tail = NULL;
	LIST_B blist;//block 링크드 리스트 생성
	blist.count = 0;
	blist.head = NULL;
	blist.tail = NULL;

	printf("-----------------------------\n");
	printf("★ Mini Bitcoin Simulation ★\n");
	printf("-----------------------------\n");
	USER* manager = NULL;//얘는 현재 사용자를 가리키는 포인터
	USER* nothing = (USER*)malloc(sizeof(USER));//얘는 special transaction에서 사용할 포인터
	strcpy(nothing->name, "Nothing");//그래서 이름을 Nothing으로 넣어줌.
	help();//초기 화면 띄우기
	char manage[10] = "/0";//명령어 받는 문자열
	while (1)
	{
		printf("\n>>");
		gets(manage);//명령어 입력
		smalling(manage);//소문자 변환
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
		else if (strcmp(manage, "quit") == 0)//이거면 끝남.
			break;
		else
			printf("wrong command!\n");
	}


	int i;
	FILE* last_pang = NULL;//파일포인터 선언해주기. 마지막에 기분좋아서 last_pang이라 지음 ㅎ
	last_pang = fopen("BlockChain.txt", "w");
	NODE_B* b;
	for (b = blist.head; b; b = b->next)//blklist에서 사용한 방법이랑 똑같이 txt파일에 적어줌.
	{
		fprintf(last_pang, "block\n");
		fprintf(last_pang, "Sender : %s\nReceiver : %s\nCoin : %d\n", b->data.special.sender->name, b->data.special.receiver->name, 100);
		free((NODE_T*)(&(b->data.special)));//출력한 것은 바로바로 할당 해제함.
		for (i = 0; i < b->data.trans_num; i++)
		{
			fprintf(last_pang, "Sender : %s\nReceiver : %s\nCoin : %d\n", b->data.trans[i].sender->name, b->data.trans[i].receiver->name, b->data.trans[i].trans_coin);
			free((NODE_T*)(&(b->data.trans[i])));//출력한 것은 바로바로 할당 해제함.
		}
	}
	fclose(last_pang);//파일 닫기


	last_pang = fopen("Transaction.txt", "w");//남아있는 거래 출력하기
	if (tlist.head == NULL)
		fprintf(last_pang, "There is no left transaction");//혹시 아무것도 안남아있으면 친절하게 넣어줌.
	else//아니면 txlist에서 쓴 방법대로 적어줌.
	{
		NODE_T* xx;
		NODE_T* ptr;
		fprintf(last_pang, "Transaction");
		for (ptr = tlist.head; ptr; xx = ptr, ptr = ptr->next, free(xx))//적어준 것은 바로바로 할당 취소
			fprintf(last_pang, "sender : %s\nreceiver : %s\nCoin : %d\n", ptr->data.sender, ptr->data.receiver, ptr->data.trans_coin);
	}
	fclose(last_pang);//파일 닫기


	last_pang = fopen("User.txt", "w");//사람 적어주기

	fprintf(last_pang, "User\n");
	if (manager == NULL)
		fprintf(last_pang, "There was no user\n");//혹시 아무것도 안남아있으면 친절하게 넣어줌.
	else 
	{
		NODE_U* xxx;
		NODE_U* ptr = NULL;
		int i = 0;
		for (ptr = ulist.head; ptr; xxx = ptr, ptr = ptr->next, free(xxx))//적어준 것은 바로바로 할당 취소
		{
			i++;
			fprintf(last_pang, "Name : %s\n   Coin : %d\n", ptr->data.name, ptr->data.coin);
		}
	}
	fclose(last_pang);
}

void help()//print만 하는 함수.
{
	printf("help: 명령어 목록 보기\n");
	printf("useradd: 사용자 등록 \n");
	printf("userlist: 등록된 모든 사용자 보기\n");
	printf("getUser: 현재 사용자 확인 \n");
	printf("chuser: 사용자 변경 \n");
	printf("mkGenBLK: Genesis Block 생성\n");
	printf("mkTx: Transaction 생성\n");
	printf("Txlist: Transaction 목록 보기\n");
	printf("mkBLK: Block 생성\n");
	printf("blklist: BlockChain(거래 내역) 확인\n");
	printf("quit: 프로그램 종료 \n");
	printf("-----------------------------\n");
}

void smalling(char* x)//소문자로 바꿔주는 함수.
{
	int i, len;
	len = strlen(x);
	for (i = 0; i < len; i++)//한글자씩 떼어서 확인
	{
		if (*(x + i) > 64 && *(x + i) < 91)//대문자면 소문자로 바꿔줌. 특수문자면 모르겠음
		{
			*(x + i) = *(x + i) + 32;
		}
	}
}










