//管理员功能实现
#include "bankAdmin.h"

//初始化三个用户信息
void userInit()
{
	BANK_T* stu = NULL;
	BANK_T* stu1 = NULL;
	BANK_T* stu2 = NULL;
 
	FILE* fp = NULL;
	fp = fopen("bank.txt","rb+");
	if (fp != NULL)
	{
		g_Head = file_to_list(fp, sizeof(BANK_T));
	}
	else
	{
		fp = fopen("bank.txt","wb+");
		//初始化三个节点
		stu = (BANK_T*)malloc(sizeof(BANK_T));
		memset(stu, 0, sizeof(BANK_T));

		strcpy(stu->bankAccount, "admin");
		strcpy(stu->bankPwd, "123456");
		stu->bankID = 10000000;
		stu->role = 1;
		stu->flag = 1;
		stu->money = 0.0;

		stu1 = (BANK_T*)malloc(sizeof(BANK_T));
		memset(stu1, 0, sizeof(BANK_T));

		strcpy(stu1->bankAccount, "jkeyl");
		strcpy(stu1->bankPwd, "123456");
		stu1->bankID = 10000001;
		stu1->role = 0;
		stu1->flag = 1;
		stu1->money = 0.0;

		stu2 = (BANK_T*)malloc(sizeof(BANK_T));
		memset(stu2, 0, sizeof(BANK_T));

		strcpy(stu2->bankAccount, "winkkkk");
		strcpy(stu2->bankPwd, "123456");
		stu2->bankID = 10000002;
		stu2->role = 0;
		stu2->flag = 1;
		stu2->money = 0.0;

		g_Head = listCreate(NULL);
		listAdd(g_Head, stu);
		listAdd(g_Head, stu1);
		listAdd(g_Head, stu2);

		list_to_file(g_Head, fp, sizeof(BANK_T));
	}
	
}
//绘制管理员界面title
void drawAdmin()
{
	gotoxy(26,2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM机管理员界面");
	gotoxy(26, 6);
	printf("****************************************************");
}

void funMenu(LINKIST_T* head)//管理员功能选择
{
	char num[5];
//	int n;
	LINKIST_T* TMP = NULL;
	while (1)
	{
		TMP = head;
		drawAdmin();
		gotoxy(46, 8);
		printf("1.用户查询");
		gotoxy(46, 9);
		printf("2.注册用户");
		gotoxy(46, 10);
		printf("3.用户修改");
		gotoxy(46, 11);
		printf("4.用户删除");
		gotoxy(65, 20);
		printf("按ESC返回上一级");
		gotoxy(46, 12);
		printf("5.退出系统");
		gotoxy(46, 15);
		printf("请选择:[ ]\b\b");
		g_num = scanf_(num, 1, 1, 0);//ESC弹出退出界面
		if (g_num == 1)
		{
			gotoxy(42, 18);
			printf("1.确认退出");
			gotoxy(42, 19);
			printf("2.取消");
			gotoxy(42, 20);
			printf("请输入:[ ]\b\b");
			scanf_(num, 1, 1, 0);
			switch (atoi(num))
			{
			case 1:
			{

				system("cls");
				userStatus(TMP);
			}
			break;
			case 2:
			{
				system("cls");
				funMenu(TMP);
			}
			break;
			}
		}

		switch (atoi(num))
		{
		case 1://用户查询
		{
			system("cls");
			while (1)
			{
				searchMenu(TMP);
			}

		}
		break;
		case 2://用户添加
		{
			system("cls");
			Staff_Add(TMP);
		}
		break;
		case 3://用户密码修改
		{
			system("cls");
			modifyMune(TMP);
		}
		break;
		case 4://用户删除
		{
			system("cls");
			Staff_del(TMP);
			funMenu(TMP);
		}
		break;
		case 5://退出系统
		{
			gotoxy(42, 18);
			printf("1.确认退出");
			gotoxy(42, 19);
			printf("2.取消");
			gotoxy(42, 20);
			printf("请输入:[ ]\b\b");
			scanf_(num, 10, 1, 0);
			switch (atoi(num))
			{
			case 1:
			{
				printf("\n");
				exit(0);
			}
			break;
			case 2:
			{
				system("cls");
				funMenu(TMP);
			}
			break;
			}
			
		}
		break;
		default:
		{
			gotoxy(44,18); 
			printf("请按提示输入");
			Sleep(1000);
			system("cls");
			funMenu(TMP);
		}
		break;
		}
	}
}


//添加员工信息
void Staff_Add(LINKIST_T* head)
{
	FILE* fp = NULL;
	LINKIST_T* pTemp = NULL;
	BANK_T* newstaff = NULL;
	BANK_T* pTmp = NULL;
	char num[10];
	char name[20];
	//char id[10];
	char pwd[20];
	char newpwd[20];
	int role;
	int i;
	int count = 0;
	pTemp = head;
	drawAdmin();
	gotoxy(46,8);
	printf("用户添加");
	gotoxy(42, 10);
	printf("用 户 名:");
	gotoxy(42, 11);
	printf("密    码:");
	gotoxy(42, 12);
	printf("确认密码:");
	gotoxy(42, 13);
	printf("角    色:");
	gotoxy(42, 14);
	printf("0---用户 1---管理员");
	gotoxy(65, 20);
	printf("按ESC返回上一级");
	gotoxy(51,10);
	g_num = scanf_(name,8,2,0);
	if (g_num == 1)
	{
		gotoxy(42, 18);
		printf("1.确认退出");
		gotoxy(42, 19);
		printf("2.取消");
		gotoxy(42, 20);
		printf("请输入:[ ]\b\b");
		scanf_(num, 10, 1, 0);
		switch (atoi(num))
		{
		case 1:
		{

			system("cls");
			funMenu(head);
		}
		break;
		case 2:
		{
			system("cls");
			Staff_Add(head);
		}
		break;
		}
	}
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		pTmp = pTemp->pData;
		if (strcmp(pTmp->bankAccount, name) == 0)
		{
			gotoxy(44,18);
			printf("该用户名存在!");
			getch();
			system("cls");
			Staff_Add(head);
		}
	}
	if (strlen(name) < 4)
	{
		gotoxy(44, 18);
		printf("用户名长度必须大于四!");
		getch();
		system("cls");
		Staff_Add(head);
	}
	while (1)
	{
		gotoxy(51, 11);
		g_num = scanf_(pwd, 6, 1, 1);
		if (g_num == 1)
		{
			gotoxy(42, 18);
			printf("1.确认退出");
			gotoxy(42, 19);
			printf("2.取消");
			gotoxy(42, 20);
			printf("请输入:[ ]\b\b");
			scanf_(num, 10, 1, 0);
			switch (atoi(num))
			{
			case 1:
			{

				system("cls");
				funMenu(head);
			}
			break;
			case 2:
			{
				system("cls");
				Staff_Add(head);
			}
			break;
			}
		}
		if (strlen(pwd) != 6)
		{
			gotoxy(44, 18);
			printf("密码长度为六位!");
			getch();
			gotoxy(51 + (int)strlen(pwd), 11);
			for (i = 1; i <= (int)strlen(pwd); i++)
			{
				printf("\b \b");
			}
			gotoxy(44, 18);
			printf("                    ");
		}
		else
		{
			gotoxy(51, 12);
			g_num = scanf_(newpwd, 6, 1, 1);
			if (g_num == 1)
			{
				gotoxy(42, 18);
				printf("1.确认退出");
				gotoxy(42, 19);
				printf("2.取消");
				gotoxy(42, 20);
				printf("请输入:[ ]\b\b");
				scanf_(num, 10, 1, 0);
				switch (atoi(num))
				{
				case 1:
				{

					system("cls");
					funMenu(head);
				}
				break;
				case 2:
				{
					system("cls");
					Staff_Add(head);
				}
				break;
				}
			}
			if (strcmp(pwd, newpwd) != 0)
			{
				gotoxy(44, 18);
				printf("两次密码不一致!");
				getch();
				gotoxy(51 + (int)strlen(newpwd), 12);
				for (i = 1; i <= (int)strlen(newpwd); i++)
				{
					printf("\b \b");
				}
				gotoxy(51 + (int)strlen(pwd), 11);
				for (i = 1; i <= (int)strlen(pwd); i++)
				{
					printf("\b \b");
				}
				gotoxy(44, 18);
				printf("                    ");
			}
			else
			{
				break;
			}

		}
		
	}
	while(1)
	{
		gotoxy(51, 13);
		scanf("%d",&role);
		if(role==0 || role== 1)
		{
			break;
		}
		else
		{
			gotoxy(44, 18);
			printf("请输入有效的角色");
			getch();
			gotoxy(52,13);
			printf("\b \b");
			gotoxy(44, 18);
			printf("                    ");
			
		}
	}
	
	count = listCount(head);
	//id = bankIdRand();
	newstaff = (BANK_T*)malloc(sizeof(BANK_T));
	memset(newstaff, 0, sizeof(BANK_T));
	strcpy(newstaff->bankAccount, name);
	strcpy(newstaff->bankPwd, pwd);
	newstaff->bankID = 10000000 + count;
	newstaff->role = role;
	newstaff->flag = 1;
	listAdd(head, newstaff);
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));
	
	gotoxy(40,16);
	printf("添加成功!您的账号是%ld   ",newstaff->bankID);
	printf("按任意键继续");
	getch();
	system("cls");
	Staff_Add(head);
	
}

//删除用户信息(实现假删除)
void Staff_del(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	FILE* fp = NULL;
	char name[10];
	int flag = 0;
	int count = 0;
	count = listCount(head);
	pTemp = head;
	drawAdmin();
	listPrint(head);
	gotoxy(65, 20);
	printf("按ESC返回上一级");
	gotoxy(0,7);
	printf("请输入要删除的用户名:");
	g_num = scanf_(name, 8, 2, 0);
	if(g_num == 1)
	{
		system("cls");
		funMenu(head);
	}
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if (strcmp(bankUser->bankAccount,name) == 0)
		{
			if (bankUser->money != 0)
			{
				gotoxy(40, 15);
				printf("余额不为零!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else if(strcmp(curUser->bankAccount,name) == 0)
			{
				gotoxy(40, 15);
				printf("不能删除自己!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else if (bankUser->flag == 0)
			{
				gotoxy(40,15);
				printf("该用户已注销!");
				getch();
				system("cls");
			}
			else if(bankUser->role == 1)
			{
				gotoxy(40, 15);
				printf("不能删除管理员!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else
			{
			    bankUser->flag = 0;
				gotoxy(2, 20);
				printf("注销成功!");
				printf("按任意键继续");
				getch();
				system("cls");
			}
			
		}
		else if (flag >= count-1)
		{
			gotoxy(40, 15);
			printf("该用户不存在!");
			getch();
			system("cls");
			Staff_del(head);
		}
		flag++;
	}
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));
}
//修改员工信息界面
void modifyMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.修改用户角色\n");
	gotoxy(46, 9);
	printf("2.修改用户密码\n");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 11);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		funMenu(head);
	}
	switch (atoi(num))
	{
	case 1:
	{
		system("cls");
		Staffrole_Modify(head);
		
	}
	break;
	case 2:
	{
		system("cls");
		modifyPwdMune(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		modifyMune(head);
	}
	break;
	}
}
//用户角色修改
void Staffrole_Modify(LINKIST_T* head)
{
	FILE* fp = NULL;
	BANK_T* bankUser = NULL;
	LINKIST_T* pTemp = NULL;
	char name[20];
	int role;
	int flag = 0;
	int count;
	count = listCount(head);
	drawAdmin();
	gotoxy(42, 8);
	printf("用户身份修改");
	gotoxy(38, 10);
	printf("请输入要修改的用户名:");
	gotoxy(75, 20);
	printf("按ESC返回上一级");

	gotoxy(59, 10);
	g_num = scanf_(name, 8, 2, 0);
	if (g_num == 1)
	{
		system("cls");
		modifyMune(head);
	}
	pTemp = head;
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if (strcmp(bankUser->bankAccount, name) == 0)
		{
			gotoxy(38, 12);
			printf("输入用户身份:");

			gotoxy(51, 12);
			scanf("%d", &role);

			bankUser->role = role;
			fp = file_open("bank.txt");
			list_to_file(head, fp, sizeof(BANK_T));
			gotoxy(40, 16);
			printf("修改成功!");
			printf("按任意键继续");
			break;
			
		}
		else if(flag>count-1)
		{
			gotoxy(40, 15);
			printf("该用户不存在!");
			getch();
			system("cls");
			Staffrole_Modify(head);
		}
		flag++;
	}
	getch();
	system("cls");
}
//用户密码修改页面
void modifyPwdMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.修改用户密码");
	gotoxy(46, 9);
	printf("2.修改操作密码");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 11);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		funMenu(head);
	}
	switch (atoi(num))
	{
	case 1://普通用户密码修改
	{
		system("cls");
		Staffpwd_Modify(head);

	}
	break;
	case 2://管理员自己操作密码的修改
	{
		system("cls");
		adminPwd_Modify(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		modifyPwdMune(head);
	}
	break;
	}
}
//修改管理员操作密码
void adminPwd_Modify(LINKIST_T* head)
{
	FILE* fp = NULL;
	BANK_T* bankUser = NULL;
	LINKIST_T* pTemp = NULL;
	char oldPwd[20];
	char pwd[20];
	char newpwd[20];
	int i = 0;
	pTemp = head;
	drawAdmin();
	gotoxy(42, 8);
	printf("操作密码修改");
	gotoxy(38, 10);
	printf("请输入旧密码:");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	while (1)
	{
		gotoxy(51, 10);
		g_num = scanf_(oldPwd, 8, 1, 1);
		if (g_num == 1)
		{
			system("cls");
			modifyPwdMune(head);
		}
		if (strcmp(oldPwd, curUser->bankPwd) != 0)
		{
			gotoxy(40, 12);
			printf("密码错误!按任意键继续");
			getch();
			gotoxy(51 + (int)strlen(oldPwd), 10);
			for (i = 0; i < (int)strlen(oldPwd); i++)
			{
				printf("\b \b");
			}
			gotoxy(40, 12);
			printf("                                     ");
		}
		else
		{
			break;
		}
	}
	
	while (1)
	{
		gotoxy(44, 12);
		printf("密码:");
		gotoxy(49, 12);
		g_num = scanf_(pwd, 6, 1, 1);
		if (g_num == 1)
		{
			system("cls");
			modifyPwdMune(head);
		}
		if (strlen(pwd) != 6)
		{
			gotoxy(44, 18);
			printf("密码长度为六位!");
			getch();
			gotoxy(49 + (int)strlen(pwd), 12);
			for (i = 1; i <= (int)strlen(pwd); i++)
			{
				printf("\b \b");
			}
			gotoxy(44, 18);
			printf("                                         ");
		}
		else
		{
			gotoxy(44, 14);
			printf("确认密码:");
			gotoxy(53, 14);
			g_num = scanf_(newpwd, 6, 1, 1);
			if (g_num == 1)
			{
				system("cls");
				modifyPwdMune(head);
			}
			if (strcmp(pwd, newpwd) != 0)
			{
				gotoxy(44, 18);
				printf("两次密码不一致!");
				getch();
				gotoxy(53 + (int)strlen(newpwd), 14);
				for (i = 1; i <= (int)strlen(newpwd); i++)
				{
					printf("\b \b");
				}
				gotoxy(49 + (int)strlen(pwd), 12);
				for (i = 1; i <= (int)strlen(pwd); i++)
				{
					printf("\b \b");
				}
				gotoxy(44, 18);
				printf("                                         ");
			}
			else
			{
				break;
			}

		}
	}
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));
	gotoxy(42, 16);
	printf("修改成功!");
	printf("按任意键继续");
	getch();
	system("cls");
	modifyPwdMune(head);
}
//用户密码修改
void Staffpwd_Modify(LINKIST_T* head)
{
	FILE* fp = NULL;
	BANK_T* bankUser = NULL;
	LINKIST_T* pTemp = NULL;
	char name[20];
	char pwd[20];
	char newpwd[20];
	int i;
	int count = listCount(head);
	int flag = 0;
	drawAdmin();
	gotoxy(42, 8);
	printf("用户密码修改");
	gotoxy(38, 10);
	printf("请输入要修改的用户名:");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	
	gotoxy(59, 10);
	g_num = scanf_(name, 8, 2, 0);
	if (g_num == 1)
	{
		system("cls");
		modifyPwdMune(head);
	}
	pTemp = head;
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if(strcmp(bankUser->bankAccount, name) == 0)
		{
			break;
		}
		flag++;
	}
	if(flag == count)
	{
		gotoxy(40, 15);
		printf("该用户不存在!");
		getch();
		system("cls");
		gotoxy(40, 15);
		printf("                 ");
		Staffpwd_Modify(head);
	}
	if(bankUser->role == 1)
	{
		gotoxy(40, 15);
		printf("不能修改管理员!");
		getch();
		system("cls");
		gotoxy(40, 15);
		printf("                 ");
		Staffpwd_Modify(head);
	}
	while (1)
	{
		gotoxy(44, 12);
		printf("密码:");
		gotoxy(49, 12);
		g_num = scanf_(pwd, 6, 1, 1);
		if (g_num == 1)
		{
			system("cls");
			modifyPwdMune(head);
		}
		if (strlen(pwd) != 6)
		{
			gotoxy(44, 18);
			printf("密码长度为六位!");
			getch();
			gotoxy(44, 18);
			printf("                 ");
			gotoxy(49 + (int)strlen(pwd), 12);
			for (i = 1; i <= (int)strlen(pwd); i++)
			{
				printf("\b \b");
			}
			
		}
		else
		{
			gotoxy(44, 14);
			printf("确认密码:");
			gotoxy(53, 14);
			g_num = scanf_(newpwd, 6, 1, 1);
			if (g_num == 1)
			{
				system("cls");
				modifyPwdMune(head);
			}
			if (strcmp(pwd, newpwd) != 0)
			{
				gotoxy(44, 18);
				printf("两次密码不一致!");
				getch();
				gotoxy(44, 18);
				printf("                ");
				gotoxy(53 + (int)strlen(newpwd), 14);
				for (i = 1; i <= (int)strlen(newpwd); i++)
				{
					printf("\b \b");
				}
				gotoxy(49 + (int)strlen(pwd), 12);
				for (i = 1; i <= (int)strlen(pwd); i++)
				{
					printf("\b \b");
				}
			}
			else
			{
				break;
			}

		}
	}
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));
	gotoxy(42,16);
	printf("修改成功!");
	printf("按任意键继续");
	getch();
	system("cls");
	modifyPwdMune(head);
}
//查询模块
void searchMenu(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.全部查询\n");
	gotoxy(46, 9);
	printf("2.分类查询\n");
	gotoxy(46, 10);
	printf("3.条件查询\n");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 12);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		funMenu(head);
	}
	switch (atoi(num))
	{
	case 1:
	{

		listPrint(head);
		printf("按任意键继续");
		getch();
		system("cls");
		searchMenu(head);
	}
	break;
	case 2:
	{
		Staff_Class(head);
	}
	break;
	case 3:
	{
		findCon(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		searchMenu(head);
	}
	break;
	}
}
//分类查询（管理员和用户查询）
void Staff_Class(LINKIST_T* head)
{
	char num[10];
	system("cls");
	drawAdmin();
	gotoxy(46, 8);
	printf("1.查询管理员");
	gotoxy(46, 9);
	printf("2.查询用户");
	gotoxy(65, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 11);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		searchMenu(head);
	}
	switch (atoi(num))
	{
	case 1:
	{
		findClass(head, 1);

	}
	break;
	case 2:
	{
		findClass(head, 0);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		Staff_Class(head);
	}
	break;
	}


}
//分类查询功能实现
void findClass(LINKIST_T* head,int irole)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "用户","管理员" };
    char* status[2] = { "注销","有效" };
	int count = 0;
	pTemp = head;
	printf("\n\n员工账号\t用户名\t密码\t用户状态\t角色\n\n");
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if (bankUser->role == irole)
		{
			printf("%ld\t%s\t%s\t%s\t\t%s\n", bankUser->bankID, bankUser->bankAccount, bankUser->bankPwd, status[bankUser->flag], role[bankUser->role]);
		}
		
			
		count++;
	}
	printf("\n   按任意键返回");
	getch();
	system("cls");
	Staff_Class(head);
}
//条件查询
void findCon(LINKIST_T* head)
{
	char num[10];
	system("cls");
	drawAdmin();
	gotoxy(46, 8);
	printf("1.模糊查询");
	gotoxy(46, 9);
	printf("2.精确查询");
	gotoxy(65, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 11);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		searchMenu(head);
	}

	switch (atoi(num))
	{
	case 1:
	{
		Staff_Search(head);

	}
	break;
	case 2:
	{
		Staff_Search1(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		findCon(head);
	}
	break;
	}
}
//根据关键字实现精确查询
void Staff_Search1(LINKIST_T* head)
{
	char name[10];
	system("cls");
	drawAdmin();
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(40,8);
	printf("用户名精确匹配");
	gotoxy(40,10);
	printf("请输入关键字:");
	g_num = scanf_(name, 10, 2, 0);
	if(g_num == 1)
	{
		system("cls");
		findCon(head);
	}
	FuzzySearch(head, name);
	system("cls");
	findCon(head);
}
//根据关键字实现模糊查询
void Staff_Search(LINKIST_T* head)
{
	//char name[10];
	system("cls");
	drawAdmin();
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(40,8);
	printf("用户名模糊匹配");
	gotoxy(40,10);
	printf("请输入关键字:");
	//g_num = scanf_(name, 10, 2, 0);
	g_num = search(head);
	if(g_num == 1)
	{
		system("cls");
		findCon(head);
	}
	//FuzzySearch(head, name);
	system("cls");
	findCon(head);
}

//实现模糊查询
int search(LINKIST_T* head)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	char* pStr = NULL;
	BANK_T* bankUser = NULL;
	char str[12];
	char cstr[12];
	int i;
	char* role[2] = { "用户","管理员" };
    char* status[2] = { "注销","有效" };
	char ch;
	
	int ilen = 0;
	memset(str,0,sizeof(char)*12);
	memset(cstr,0,sizeof(char)*12);
	pTemp = head;
	while (1)
	{
		ch = getch();
		if(ilen>0)
		{
			if(ch == '\b')
			{
				printf("\b \b");
				ilen--;
			}
		}
		if(ch == 27)
		{
			return 1;
		}
		if(ilen<8)
		{
			if((ch >= '0' && ch <= '9' )|| (ch >= 'a' && ch <= 'z' )||( ch >= 'A' && ch <= 'Z'))
			{
				putchar(ch);
				str[ilen] = ch;
				ilen++;
			}
		}
		
		system("cls");
		drawAdmin();

		
		memset(cstr,0,sizeof(char)*12);
		for(i = 0;i<ilen;i++)
		{
			cstr[i] = str[i];
		}
		gotoxy(75, 20);
		printf("按ESC返回上一级");
		gotoxy(40,8);
		printf("用户名模糊匹配");
		gotoxy(40, 10);
		printf("请输入关键字:%s",cstr);
		gotoxy(0, 12);
		printf("员工账号\t用户名\t密码\t用户状态\t余额\t角色");
		if(strlen(cstr)==0)
		{
			gotoxy(0, 12);
			printf("                                                                ");
			gotoxy(53+ilen,10);
			continue;
			
		}
		gotoxy(0, 13);
		while (pTemp->pNext != NULL)
		{
			pTemp = pTemp->pNext;
			bankUser = pTemp->pData;
			pStr = strstr(bankUser->bankAccount, cstr);
			//pStr = strstr(bankUser->bankID, cstr);
			if (pStr != NULL)
			{
				printf("%ld\t%s\t%s\t%s\t\t%0.2f\t%s\n", bankUser->bankID, bankUser->bankAccount, bankUser->bankPwd, status[bankUser->flag], bankUser->money, role[bankUser->role]);
			}
		}
		pTemp = head;
		gotoxy(53+ilen,10);
	}
}
