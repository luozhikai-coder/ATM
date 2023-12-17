#include "login.h"


//绘制登录界面
void loginMenu()
{
	//system("color 2e");
	//show_time();
	
	//showTime();
	/*
	gotoxy(0,0);
	printf("管理员:admin");
	gotoxy(0,2);
	printf("用户:jkeyl winkkkk");
	gotoxy(0,3);
	printf("账号:10000001 10000002");
	gotoxy(0,4);
	printf("密码均为123456");
	gotoxy(85,25);
	printf("DX1903 罗志凯");
	*/
	gotoxy(26,2);
	printf("****************************************************");
	gotoxy(42,4);
	printf("ATM机自动存储管理系统");
	gotoxy(26, 6);
	printf("****************************************************");
	gotoxy(48, 8);
	printf("用户登录");
	gotoxy(40, 10);
	printf("账号(8位):");
	gotoxy(40, 12);
	printf("密码(6位):");
	gotoxy(26, 14);
	printf("****************************************************");
	gotoxy(65,20);
	printf("按ESC退出");
	//showTime();
}

/************************************************

*函数名：login(LINKIST_T* head)
*函数功能：实现登录功能
*函数参数：用户链表头结点
*函数返回：当前节点的数据

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
		printf("1.确认退出");
		gotoxy(42, 19);
		printf("2.取消");
		gotoxy(42, 20);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			//system("pause");
			gotoxy(40, 24);
			printf("正在退出系统，请稍后...");
			Sleep(1000);
			/*for (i = 0; i < 10; i++)
			{
				gotoxy(40+i, 19);
				printf("▊ ");
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
		printf("账号长度大于四！");
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
			printf("密码长度为六");
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
			printf("用户名或账号不正确!");
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

*函数名：userStatus(LINKIST_T* head)
*函数功能：根据用户角色进入不同界面
*函数参数：用户链表头结点
*函数返回：无

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
			printf("用户名或账号不正确!");
			gotoxy(42, 17);
			system("pause");
			system("cls");
			userStatus(head);
		}
		else
		{
			switch (curUser->role)
			{
			case 0://用户登录界面
			{
				gotoxy(40, 24);
				printf("正在登陆，请稍后...");
				Sleep(1500);
				system("cls");
				menu(head);

			}
			break;
			case 1://管理员登录界面
			{
				gotoxy(40, 24);
				printf("正在登陆，请稍后...");
				Sleep(1500);
				system("cls");
				funMenu(head);
			}
			break;
			}

		}
	}
	
	
	
}