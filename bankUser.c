//银行用户功能实现
#include "bankUser.h"


//绘制用户界面title
void drawUser()
{
	gotoxy(26, 2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM机用户操作界面");
	gotoxy(26, 6);
	printf("****************************************************");
}

void userInio_r()
{
	record_fp = fopen("record.txt","rb+");
	if(record_fp == NULL)
	{
		record_fp = fopen("record.txt","wb+");
		g_rHead = listCreate(NULL);
	}
	else
	{	
		g_rHead = file_to_list(record_fp,sizeof(RECORD_T));
	}
}

/************* 绘制用户功能界面 ************/
void menu(LINKIST_T* head)
{
	char num[5];
	int n;
	LINKIST_T* tmp = head;
	//system("color 2e");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t*********      ▲▼中国建设银行▲▼    *************\n");
	printf("\t\t\t*********欢迎使用中国建设银行存取款系统*************\n");
	printf("\t\t\t*********       (请在<1-6>中选择)      *************\n");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       1.查询(Inquiry)     2.取款(Withdrawal)     *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       3.存款(Deposit)     4.改密(Repass)         *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       5.转账(Transfer)    6.交易记录(Exchange)   *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t         请选择(1-6):[ ]\b\b");
	gotoxy(65, 20);
	printf("按ESC退出系统");
	gotoxy(46,13);
	g_num = scanf_(num,5,1,0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d",&n);
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
			userStatus(tmp);
		}
		case 2:
		{
			system("cls");
			menu(tmp);
		}
		}
	}
	switch (atoi(num))
	{
	case 1:
	{
		system("cls");
		Inquiry(tmp);
	}
	break;
	case 2:
	{
		system("cls");
		Withdrawal(tmp);
	}
	break;
	case 3:
	{
		system("cls");
		Deposit(tmp);
	}
	break;
	case 4:
	{
		system("cls");
		Repass(tmp);
	}
	break;
	case 5:
	{
		system("cls");
		Transfer(tmp);
	}
	break;
	case 6:
	{
		system("cls");
		exchangeMune(tmp);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		menu(tmp);
	}
	break;
	}
}
/********************取款************************/
void Withdrawal(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* newRecord = NULL;
	FILE* fp = NULL; 
	time_t rawtime;
	struct tm* timeinfo;
	int n;
	char mon[10];
	char ctime[10];
	drawUser();
	gotoxy(40, 10);
	printf("当前余额:%.2f元", curUser->money);
	gotoxy(40, 12);
	printf("取款金额:");
	g_num = scanf_(mon, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			system("cls");
			menu(head);
		}
		case 2:
		{
			system("cls");
			Deposit(head);
		}
		}
	}
	if (atoi(mon) == 0)
	{
		gotoxy(38, 16);
		printf("取款金额不为0");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Withdrawal(head);
	}
	if (atoi(mon) % 100 != 0)
	{
		gotoxy(38, 16);
		printf("取款金额需是100的整数倍");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Withdrawal(head);
	}
	if (atoi(mon)>curUser->money)
	{
		gotoxy(38, 16);
		printf("当前账户余额不足");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Withdrawal(head);
	}
	
	//同步用户文件信息
	curUser->money -= atoi(mon);
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));

	//将交易记录信息存到结构体
	newRecord = (RECORD_T*)malloc(sizeof(RECORD_T));
	memset(newRecord, 0, sizeof(RECORD_T));
	newRecord->cur_id = curUser->bankID;
	strcpy(newRecord->source, "1");
	newRecord->amount = (float)atoi(mon);
	newRecord->balance = curUser->money;
	newRecord->type = 1;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ctime, "%4d-%02d-%02d", 1900 + timeinfo->tm_year, timeinfo->tm_mon+1, timeinfo->tm_mday);
	strcpy(newRecord->cur_time, ctime);
	//将数据添加到链表
	listAdd(g_rHead, newRecord);
	//将链表中数据写入文件
	//record_fp = file_open("record.txt");
	list_to_file(g_rHead, record_fp, sizeof(RECORD_T));
	
	system("cls");
	drawUser();
	gotoxy(40, 12);
	printf("当前余额:%.2f元", curUser->money);
	gotoxy(42, 14);
	printf("取款%s元成功", mon);
	printf("按任意键返回");
	getch();
	system("cls");
	menu(head);
}
/**********************存款**********************/
void Deposit(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* newRecord = NULL;
	FILE* fp = NULL;
	time_t rawtime;
	struct tm* timeinfo;
	int n;
	char mon[10];
	char ctime[10];
	
	pTemp = g_rHead;
	
	drawUser();
	gotoxy(40, 10);
	printf("当前余额:%.2f元",curUser->money);
	gotoxy(40,12);
	printf("存款金额:");
	g_num = scanf_(mon,10,1,0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			system("cls");
			menu(head);
		}
		case 2:
		{
			system("cls");
			Deposit(head);
		}
		}
	}
	if (atoi(mon) == 0)
	{
		gotoxy(38,16);
		printf("存款金额不为0");
		gotoxy(42,17);
		printf("按任意键继续");
		getch();
		system("cls");
		Deposit(head);
	}
	if (atoi(mon) % 100 != 0)
	{
		gotoxy(38,16);
		printf("存款金额需是100的整数倍");
		gotoxy(42,17);
		printf("按任意键继续");
		getch();
		system("cls");
		Deposit(head);
	}
	if (atoi(mon)>= 20000)
	{
		gotoxy(38,16);
		printf("单次交易金额不超过20000");
		gotoxy(42,17);
		printf("按任意键继续");
		getch();
		system("cls");
		Deposit(head);
	}
	//同步用户文件信息
	curUser->money += atoi(mon);
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));

	//将交易记录信息存到结构体
	newRecord = (RECORD_T*)malloc(sizeof(RECORD_T));
	memset(newRecord,0,sizeof(RECORD_T));
	newRecord->cur_id = curUser->bankID;
	strcpy(newRecord->source,"1");
	newRecord->amount = (float)atoi(mon);
	newRecord->balance = curUser->money;
	newRecord->type = 0;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ctime,"%4d-%02d-%02d",1900 + timeinfo->tm_year,timeinfo->tm_mon+1,timeinfo->tm_mday);
	strcpy(newRecord->cur_time,ctime);
	//将数据添加到链表
	listAdd(g_rHead,newRecord);
	//将链表中数据写入文件
	//record_fp = file_open("record.txt");
	list_to_file(g_rHead,record_fp,sizeof(RECORD_T));

	system("cls");
	drawUser();
	gotoxy(40,12);
	printf("当前余额:%.2f元",curUser->money);
	gotoxy(42,14);
	printf("存款%s元成功",mon);
	printf("按任意键返回");
	getch();
	system("cls");
	menu(head);
}
/******************用户余额查询*************************/
void Inquiry(LINKIST_T* head)
{
	int n;
	char num[5];
	drawUser();
	gotoxy(65, 20);
	printf("按ESC返回上一级");
	gotoxy(40,8);
	printf("%s用户,您好！", curUser->bankAccount);
	gotoxy(40,10);
	printf("您的当前余额为:%.2f元",curUser->money);
	g_num = scanf_(num,5,1,1);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			system("cls");
			menu(head);
		}
		case 2:
		{
			system("cls");
			Inquiry(head);
		}
		}
	}
}
/***********修改密码*************/
void Repass(LINKIST_T* head)
{
	int n;
	FILE* fp = NULL;
	BANK_T* bankUser = NULL;
	LINKIST_T* pTemp = NULL;
	char oldPwd[20];
	char pwd[20];
	char newpwd[20];
	int i = 0;
	pTemp = head;
	drawUser();
	gotoxy(42, 8);
	printf("用户密码修改");
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
			gotoxy(40, 15);
			printf("1.确认退出");
			gotoxy(40, 16);
			printf("2.取消");
			gotoxy(40, 17);
			printf("请输入:[ ]\b\b");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				system("cls");
				menu(head);
			}
			case 2:
			{
				system("cls");
				Repass(head);
			}
			}
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
		printf("新密码:");
		gotoxy(51, 12);
		g_num = scanf_(pwd, 6, 1, 1);
		if (g_num == 1)
		{
			gotoxy(40, 15);
			printf("1.确认退出");
			gotoxy(40, 16);
			printf("2.取消");
			gotoxy(40, 17);
			printf("请输入:[ ]\b\b");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				system("cls");
				menu(head);
			}
			case 2:
			{
				system("cls");
				Repass(head);
			}
			}
		}
		if (strlen(pwd) != 6)
		{
			gotoxy(44, 18);
			printf("密码长度为六位!");
			getch();
			gotoxy(51 + (int)strlen(pwd), 12);
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
				gotoxy(40, 15);
				printf("1.确认退出");
				gotoxy(40, 16);
				printf("2.取消");
				gotoxy(40, 17);
				printf("请输入:[ ]\b\b");
				scanf("%d", &n);
				switch (n)
				{
				case 1:
				{
					system("cls");
					menu(head);
				}
				case 2:
				{
					system("cls");
					Repass(head);
				}
				}
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
				gotoxy(51 + (int)strlen(pwd), 12);
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
	menu(head);
}
/***************转账*************/
void Transfer(LINKIST_T* head)
{
	FILE* fp = NULL;
	LINKIST_T* pTemp = NULL;
	RECORD_T* Recordout = NULL;//转出
	RECORD_T* Recordin = NULL;//转入
	BANK_T* ptmp = NULL;
	time_t rawtime;
	struct tm* timeinfo;
	int n;
	int flag = 0;
	int count;
	char mon[10];
	char id[10];
	char ctime[10];
	char ch;
	count = listCount(head);
	pTemp = head;
	drawUser();
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(40, 8);
	printf("当前余额:%.2f元",curUser->money);
	gotoxy(40, 10);
	printf("请输入转账账户:");
	g_num = scanf_(id, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			system("cls");
			menu(head);
		}
		case 2:
		{
			system("cls");
			Transfer(head);
		}
		}
	}
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		ptmp = pTemp->pData;
		if (ptmp->bankID == atoi(id))
		{
			break;
		}
		
		flag++;
	}
	if(flag==count)
	{

		gotoxy(44, 18);
		printf("转账账户不存在!");
		getch();
		system("cls");
		Transfer(head);
	}
	if (atoi(id) == curUser->bankID)
	{
		gotoxy(38, 16);
		printf("不能够转账给自己");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);
	}
	if (ptmp->role == 1)
	{
		gotoxy(38, 16);
		printf("不能够转账给管理员");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);
	}
	if(ptmp->flag == 0)
	{
		gotoxy(38, 16);
		printf("该用户已注销");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);
	}
	gotoxy(40, 12);
	printf("转账金额:");
	g_num = scanf_(mon, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.确认退出");
		gotoxy(40, 16);
		printf("2.取消");
		gotoxy(40, 17);
		printf("请输入:[ ]\b\b");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
		{
			system("cls");
			menu(head);
		}
		case 2:
		{
			system("cls");
			Transfer(head);
		}
		}
	}
	if (atoi(mon) % 100 != 0)
	{
		gotoxy(38, 16);
		printf("转账金额需是100的整数倍");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);

	}
	if (atoi(mon)>curUser->money)
	{
		gotoxy(38, 16);
		printf("当前账户余额不足");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);

	}
	if (atoi(mon) >=20000)
	{
		gotoxy(38, 16);
		printf("转账金额不能高于2万");
		gotoxy(42, 17);
		printf("按任意键继续");
		getch();
		system("cls");
		Transfer(head);

	}
	system("cls");
	drawUser();
	gotoxy(40, 10);
	printf("转账账户信息如下");
	gotoxy(40, 12);
	printf("转账账户:%s",id);
	gotoxy(40, 13);
	printf("转账金额:%d",atoi(mon));
	gotoxy(42, 16);
	printf("确认转账?Y/N");
	ch = getch();
	if(ch == 'y' || ch == 'Y')
	{
		curUser->money -= atoi(mon);
		ptmp->money += atoi(mon);

		fp = file_open("bank.txt");
		list_to_file(head, fp, sizeof(BANK_T));

		/*record_to_file((float)atoi(mon), curUser->money, curUser->bankID,2,(char)ptmp->bankID);
		record_to_file((float)atoi(mon),ptmp->money, ptmp->bankID,3, (char)curUser->bankID);*/
		//将转出记录信息存到结构体
		
		Recordout = (RECORD_T*)malloc(sizeof(RECORD_T));
		memset(Recordout, 0, sizeof(RECORD_T));
		Recordout->cur_id = id;
		strcpy(Recordout->source, id);
		Recordout->amount = (float)atoi(mon);
		Recordout->balance = curUser->money;
		Recordout->type = 2;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		sprintf(ctime, "%4d-%02d-%02d", 1900 + timeinfo->tm_year, timeinfo->tm_mon+1, timeinfo->tm_mday);
		strcpy(Recordout->cur_time, ctime);
		
		
		//将转入记录信息存到结构体
		Recordin = (RECORD_T*)malloc(sizeof(RECORD_T));
		memset(Recordin, 0, sizeof(RECORD_T));

		Recordin->cur_id = ptmp->bankID;
		sprintf(Recordin->source,"%ld",ptmp->bankID);
		Recordin->amount = (float)atoi(mon);
		Recordin->balance = ptmp->money;
		Recordin->type = 3;
		/*time(&rawtime);
		timeinfo = localtime(&rawtime);
		sprintf(ctime, "%4d-%02d-%02d", 1900 + timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday);*/
		strcpy(Recordin->cur_time, ctime);

		//将数据添加到链表
		listAdd(g_rHead, Recordout);
		listAdd(g_rHead, Recordin);
		//将链表中数据写入文件
		//record_fp = file_open("record.txt");
		list_to_file(g_rHead, record_fp, sizeof(RECORD_T));
		gotoxy(42, 14);
		printf("转账成功！");
		printf("按任意键返回");
		getch();
		system("cls");
		menu(head);
	}
	else if(ch == 'n' || ch == 'N')
	{
		system("cls");
		menu(head);
	}
	
}
/************************************************

*函数名：exchangeMune(LINKIST_T* head)
*函数功能：交易记录查询界面
*函数参数：时间指针
*函数返回：data数组

*************************************************/
void exchangeMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.全部查询\n");
	gotoxy(46, 9);
	printf("2.按时间查询\n");
	gotoxy(75, 20);
	printf("按ESC返回上一级");
	gotoxy(46, 11);
	printf("请输入:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		menu(head);
	}
	switch (atoi(num))
	{
	case 1:
	{
		system("cls");
		Exchange(head);
	}
	break;
	case 2:
	{
		system("cls");
	    check_time_record(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("请按提示输入");
		Sleep(1000);
		system("cls");
		exchangeMune(head);
	}
	break;
	}
}
/************************************************

*函数名：check_time_record(LINKIST_T* head)
*函数功能：交易记录按时间查询
*函数参数：用户链表
*函数返回：无

*************************************************/
int check_time_record(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* ptmp = NULL;
	int i,j;
	int page = 0;
	int pageSum = 0;
	int sum = 0;
	int count = 1;
	char ch;
	char* type[4] = {"存款","取款","转出","转入"};
	char date1[9];
	char date2[9];
	int ymd1[3];  //年月日
	int ymd2[3];  //年月日
	int sub;
	
	system("cls");
	gotoxy(26, 2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM机账单按日期查询");
	gotoxy(26, 6);
	printf("****************************************************");

	while(1)
	{
		while(1)
		{
			gotoxy(8,9);
			printf("请输入起始日期:");
			if(control_date(date1,ymd1)!=0)
			{	
				gotoxy(20,10);
				printf("不合法的输入时间");
				getch();
				del_line(10,1);
			}
		
			else
				break;
			
		}

		while(1)
		{
			gotoxy(50,9);
			printf("请输入结束日期:");
			if(control_date(date2,ymd2)!=0)
			{	
				gotoxy(60,10);
				printf("不合法的输入时间");
				getch();
				del_line(10,1);
			}
			
			else
				break;
		}
		sub = (ymd2[0]-ymd1[0])*365 + (ymd2[1] - ymd1[1])*30 + (ymd2[2]-ymd1[2]);//有问题这里
		if(strcmp(date1,date2)>0)
		{
			gotoxy(40,10);
			printf("起始时间大于结束时间");
			getch();
			del_line(9,2);
		}
		else if(sub > 30)
		{
			gotoxy(40,10);
			printf("间隔不能大于一个月");
			getch();
			del_line(9,2);
		}
		else
		{
		//	record_fp = file_open("record.txt");
		//	g_rHead = file_to_list(record_fp, sizeof(RECORD_T));
			sum = count_t(g_rHead,date1,date2);//计算该时间段记录条数
			if(sum%10 == 0)
			{
				pageSum = sum/10;
			}
			else
			{
				pageSum = sum/10 + 1;
			}
			
			start[pageSum] = sum + 1; 
		//	pTemp = newhead;
			while(1)
				{
					system("cls");
					gotoxy(26, 2);
					printf("****************************************************");
					gotoxy(44, 4);
					printf("ATM机账单按日期查询");
					gotoxy(26, 6);
					printf("****************************************************");
					gotoxy(20,8);
					printf("序号\t当前时间\t金额\t余额\t摘要\t\t发生源");
					gotoxy(20,9);
					printf("-------------------------------------------------------------------");
					for(i=start[page],j=1;i<=sum && i<start[page+1];i++)
					{

						ptmp = (RECORD_T *)list_getnode(newhead,i)->pData;	
						gotoxy(20,10+j);
						printf("%d\t\t%s\t%.0f\t%.0f\t%s\t\t",j, 
						ptmp->cur_time,ptmp->amount,ptmp->balance,type[ptmp->type]);
						if (strcmp(ptmp->source,"1") == 0)
						{
							printf("ATM机     \n");
						}
						else
						{
							printf("%s   \n",ptmp->source);
						}
 						j++;	
						
					}
					gotoxy(40,22);
					printf("第%d/%d页",page+1,pageSum);
					gotoxy(50,22);
					printf("1.上一页  2.下一页  3.退出:");
					ch = getch();			//1表示上一页，2表示下一页
					if(ch == '1' && page > 0)
					{
						page--;
					}
					else if(ch == '2' && start[page+1] != sum+1)//仅当下一页不为空
					{
						page++;
					}
					else if(ch == '3')
					{
						system("cls");
						menu(head);
					}
			} 
					break;
			
				}
				
			
		}

	//getch();
	return 0;
}

/************************************************

*函数名：Exchange(LINKIST_T* head)
*函数功能：交易记录全部查询
*函数参数：用户链表
*函数返回：无

*************************************************/
void Exchange(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* ptmp = NULL;
	int i,j;
	int page = 0;
	int pageSum = 0;
	int sum = 0;
	int count = 1;
	char ch;
	char* type[4] = {"存款","取款","转出","转入"};
//	record_fp = file_open("record.txt");
//	g_rHead = file_to_list(record_fp, sizeof(RECORD_T));
	
	sum = count_r(g_rHead);
	if(sum%10 == 0)
	{
		pageSum = sum/10;
	}
	else
	{
		pageSum = sum/10 + 1;
	}
	
	start[pageSum] = sum + 1; 
//	pTemp = newhead;s
	while(1)
		{
			system("cls");
			gotoxy(26, 2);
			printf("****************************************************");
			gotoxy(44, 4);
			printf("ATM机用户交易记录界面");
			gotoxy(26, 6);
			printf("****************************************************");
			gotoxy(20,8);
			printf("序号\t当前时间\t金额\t余额\t摘要\t\t发生源");
			gotoxy(20,9);
			printf("-------------------------------------------------------------------");
			
			for(i=start[page],j=1;i<=sum && i<start[page+1];i++)
			{

				ptmp = (RECORD_T *)list_getnode(newhead,i)->pData;
				gotoxy(20,10+j);
				printf("%d\t\t%s\t%.0f\t%.0f\t%s\t\t",j, 
				ptmp->cur_time,ptmp->amount,ptmp->balance,type[ptmp->type]);
				if (strcmp(ptmp->source,"1") == 0)
				{
					printf("ATM机     \n");
				}
				else
				{
					printf("%s   \n",ptmp->source);
				}
   				j++;
			}
			gotoxy(45,22);
			printf("第%d/%d页",page+1,pageSum);
			gotoxy(55,22);
			printf("1.上一页  2.下一页  3.退出:");
			ch = getch();			//1表示上一页，2表示下一页
			if(ch == '1' && page > 0)
			{
				page--;
			}
			else if(ch == '2' && start[page+1] != sum+1)//仅当下一页不为空
			{
				page++;
			}
			else if(ch == '3')
			{
				system("cls");
				menu(head);
			}
		}
}

/************************************************

*函数名：count_t(LINKIST_T* head,char *date1,char *date2)
*函数功能：计算满足时间区间的交易记录条数，并将记录写入链表
*函数参数：交易记录链表，开始日期，结束日期
*函数返回：无

*************************************************/
int count_t(LINKIST_T* head,char *date1,char *date2)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* ptmp = NULL;
	char* date = NULL;
	int i = 0;
	FILE* fp = NULL;
	int sum = 0;
	
	

	pTemp = head;
	newhead = listCreate(NULL);
	
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
 		ptmp = pTemp->pData;
		date = contime(ptmp->cur_time);//将时间转换成"20190508"形式
		if (curUser->bankID == ptmp->cur_id && strcmp(date,date1)>=0 && strcmp(date,date2)<=0)
		{
			listAdd(newhead,ptmp);
			sum++;
			if(sum%10 == 1)
			{
				start[i++] = sum;
			}
		}
		
	}
	return sum;
}
/************************************************

*函数名：count_t(LINKIST_T* head,char *date1,char *date2)
*函数功能：计算交易记录条数，并将记录写入链表
*函数参数：交易记录链表
*函数返回：无

*************************************************/
int count_r(LINKIST_T* head)
{
	LINKIST_T* pTemp = NULL;
	RECORD_T* ptmp = NULL;
	int i = 0;
	FILE* fp = NULL;
	int sum = 0;
	
	

	pTemp = head;
	newhead = listCreate(NULL);
	
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
 		ptmp = pTemp->pData;
		if (curUser->bankID == ptmp->cur_id )
		{
			listAdd(newhead,ptmp);
			sum++;
			if(sum%10 == 1)
			{
				start[i++] = sum;
			}
		}
		
	}
	return sum;
}
/************************************************

*函数名：count_t(LINKIST_T* head,char *date1,char *date2)
*函数功能：将时间字符串转化为"20190507"格式
*函数参数：时间指针
*函数返回：data数组

*************************************************/
char* contime(char *time)
{
	int i,j;
	char data[12];
	memset(data,0,sizeof(char)*12);
	//char* date;
	j = 0;
	for(i = 0;i<10;i++)
	{
	
		if(i==4 || i==7)
		{
			continue;
		}
		data[j++] = time[i];
	}
	
	return data;
}
//将交易记录写入文件
/*
void record_to_file(float amount,float balance,long int id,int t_type,char source)
{
	RECORD_T* newRecord = NULL;
	FILE* fp = NULL;
	time_t rawtime;
	struct tm* timeinfo;
	char ctime[10];
	//申请空间
	newRecord = (RECORD_T*)malloc(sizeof(RECORD_T));
	memset(newRecord,0,sizeof(RECORD_T));
	//向结构体中添加数据
	newRecord->amount = amount;
	newRecord->balance = balance;
	newRecord->cur_id = id;
	strcpy(newRecord->source, source);
	newRecord->type = t_type;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ctime, "%4d-%02d-%02d", 1900 + timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday);
	strcpy(newRecord->cur_time, ctime);
	//将数据添加到链表
	listAdd(g_rHead, newRecord);

	//写入文件
	record_fp = file_open("record.txt");
	list_to_file(g_rHead, record_fp, sizeof(RECORD_T));

}
*/
