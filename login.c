#include "login.h"


//���Ƶ�¼����
void loginMenu()
{
	//system("color 2e");
	//show_time();
	
	//showTime();
	/*
	gotoxy(0,0);
	printf("����Ա:admin");
	gotoxy(0,2);
	printf("�û�:jkeyl winkkkk");
	gotoxy(0,3);
	printf("�˺�:10000001 10000002");
	gotoxy(0,4);
	printf("�����Ϊ123456");
	gotoxy(85,25);
	printf("DX1903 ��־��");
	*/
	gotoxy(26,2);
	printf("****************************************************");
	gotoxy(42,4);
	printf("ATM���Զ��洢����ϵͳ");
	gotoxy(26, 6);
	printf("****************************************************");
	gotoxy(48, 8);
	printf("�û���¼");
	gotoxy(40, 10);
	printf("�˺�(8λ):");
	gotoxy(40, 12);
	printf("����(6λ):");
	gotoxy(26, 14);
	printf("****************************************************");
	gotoxy(65,20);
	printf("��ESC�˳�");
	//showTime();
}

/************************************************

*��������login(LINKIST_T* head)
*�������ܣ�ʵ�ֵ�¼����
*�����������û�����ͷ���
*�������أ���ǰ�ڵ������

*************************************************/
BANK_T* login(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	int n;
	char name[20];
	char pwd[20];
	int flag = 0;
	int count = 0;
	//int i;
	pTemp = head;
	count = listCount(head);
	loginMenu();
	gotoxy(50,10);
	g_num = scanf_(name, 8, 3, 0);
	if (g_num == 1)
	{
		gotoxy(42, 18);
		printf("1.ȷ���˳�");
		gotoxy(42, 19);
		printf("2.ȡ��");
		gotoxy(42, 20);
		printf("������:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			//system("pause");
			gotoxy(40, 24);
			printf("�����˳�ϵͳ�����Ժ�...");
			Sleep(1000);
			/*for (i = 0; i < 10; i++)
			{
				gotoxy(40+i, 19);
				printf("�� ");
				Sleep(250);
			}*/
			system("cls");
			exit(0);
		}
		case 2:
		{
			system("cls");
			userStatus(head);
		}
		}
	}
	if (strlen(name) < 4)
	{
		gotoxy(50,10);
		printf("�˺ų��ȴ����ģ�");
		getch();
		system("cls");
		login(head);
	}
	while(1)
	{
		gotoxy(50, 12);
		scanf_(pwd, 6, 1, 1);
		if (strlen(pwd) != 6)
		{
			gotoxy(50, 12);
			printf("���볤��Ϊ��");
			getch();
			gotoxy(50,12);
			printf("             ");
			/*
			for(i = 0;i<(int)strlen(pwd)+12;i++)
			{
				printf("\b \b");
			}
			*/
			
		}
		else
		{
			break;
		}
	}
	
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if((strcmp(bankUser->bankAccount,name) == 0 || bankUser->bankID == atoi(name)) && strcmp(bankUser->bankPwd,pwd) == 0 && bankUser->flag == 1)
		{
			return bankUser;
		}
		/*else if (flag + 2 > count)
		{
			gotoxy(42,16);
			printf("�û������˺Ų���ȷ!");
			gotoxy(42, 17);
			system("pause");
			system("cls");
			login(head);
		}
		flag++;*/
	}
	
	return NULL;
}

/************************************************

*��������userStatus(LINKIST_T* head)
*�������ܣ������û���ɫ���벻ͬ����
*�����������û�����ͷ���
*�������أ���

*************************************************/
void userStatus(LINKIST_T* head)
{
	
	//int n;
	//char ch;
	while (1)
	{
		curUser = login(head);
		if (curUser == NULL)
		{
			gotoxy(42, 16);
			printf("�û������˺Ų���ȷ!");
			gotoxy(42, 17);
			system("pause");
			system("cls");
			userStatus(head);
		}
		else
		{
			switch (curUser->role)
			{
			case 0://�û���¼����
			{
				gotoxy(40, 24);
				printf("���ڵ�½�����Ժ�...");
				Sleep(1500);
				system("cls");
				menu(head);

			}
			break;
			case 1://����Ա��¼����
			{
				gotoxy(40, 24);
				printf("���ڵ�½�����Ժ�...");
				Sleep(1500);
				system("cls");
				funMenu(head);
			}
			break;
			}

		}
	}
	
	
	
}