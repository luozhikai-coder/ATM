//�����û�����ʵ��
#include "bankUser.h"


//�����û�����title
void drawUser()
{
	gotoxy(26, 2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM���û���������");
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

/************* �����û����ܽ��� ************/
void menu(LINKIST_T* head)
{
	char num[5];
	int n;
	LINKIST_T* tmp = head;
	//system("color 2e");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t*********      �����й��������С���    *************\n");
	printf("\t\t\t*********��ӭʹ���й��������д�ȡ��ϵͳ*************\n");
	printf("\t\t\t*********       (����<1-6>��ѡ��)      *************\n");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       1.��ѯ(Inquiry)     2.ȡ��(Withdrawal)     *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       3.���(Deposit)     4.����(Repass)         *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t*       5.ת��(Transfer)    6.���׼�¼(Exchange)   *\n");
	printf("\t\t\t*                                                  *\n");
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t         ��ѡ��(1-6):[ ]\b\b");
	gotoxy(65, 20);
	printf("��ESC�˳�ϵͳ");
	gotoxy(46,13);
	g_num = scanf_(num,5,1,0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
		scanf("%d",&n);
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		menu(tmp);
	}
	break;
	}
}
/********************ȡ��************************/
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
	printf("��ǰ���:%.2fԪ", curUser->money);
	gotoxy(40, 12);
	printf("ȡ����:");
	g_num = scanf_(mon, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
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
		printf("ȡ���Ϊ0");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Withdrawal(head);
	}
	if (atoi(mon) % 100 != 0)
	{
		gotoxy(38, 16);
		printf("ȡ��������100��������");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Withdrawal(head);
	}
	if (atoi(mon)>curUser->money)
	{
		gotoxy(38, 16);
		printf("��ǰ�˻�����");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Withdrawal(head);
	}
	
	//ͬ���û��ļ���Ϣ
	curUser->money -= atoi(mon);
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));

	//�����׼�¼��Ϣ�浽�ṹ��
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
	//��������ӵ�����
	listAdd(g_rHead, newRecord);
	//������������д���ļ�
	//record_fp = file_open("record.txt");
	list_to_file(g_rHead, record_fp, sizeof(RECORD_T));
	
	system("cls");
	drawUser();
	gotoxy(40, 12);
	printf("��ǰ���:%.2fԪ", curUser->money);
	gotoxy(42, 14);
	printf("ȡ��%sԪ�ɹ�", mon);
	printf("�����������");
	getch();
	system("cls");
	menu(head);
}
/**********************���**********************/
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
	printf("��ǰ���:%.2fԪ",curUser->money);
	gotoxy(40,12);
	printf("�����:");
	g_num = scanf_(mon,10,1,0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
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
		printf("����Ϊ0");
		gotoxy(42,17);
		printf("�����������");
		getch();
		system("cls");
		Deposit(head);
	}
	if (atoi(mon) % 100 != 0)
	{
		gotoxy(38,16);
		printf("���������100��������");
		gotoxy(42,17);
		printf("�����������");
		getch();
		system("cls");
		Deposit(head);
	}
	if (atoi(mon)>= 20000)
	{
		gotoxy(38,16);
		printf("���ν��׽�����20000");
		gotoxy(42,17);
		printf("�����������");
		getch();
		system("cls");
		Deposit(head);
	}
	//ͬ���û��ļ���Ϣ
	curUser->money += atoi(mon);
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));

	//�����׼�¼��Ϣ�浽�ṹ��
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
	//��������ӵ�����
	listAdd(g_rHead,newRecord);
	//������������д���ļ�
	//record_fp = file_open("record.txt");
	list_to_file(g_rHead,record_fp,sizeof(RECORD_T));

	system("cls");
	drawUser();
	gotoxy(40,12);
	printf("��ǰ���:%.2fԪ",curUser->money);
	gotoxy(42,14);
	printf("���%sԪ�ɹ�",mon);
	printf("�����������");
	getch();
	system("cls");
	menu(head);
}
/******************�û�����ѯ*************************/
void Inquiry(LINKIST_T* head)
{
	int n;
	char num[5];
	drawUser();
	gotoxy(65, 20);
	printf("��ESC������һ��");
	gotoxy(40,8);
	printf("%s�û�,���ã�", curUser->bankAccount);
	gotoxy(40,10);
	printf("���ĵ�ǰ���Ϊ:%.2fԪ",curUser->money);
	g_num = scanf_(num,5,1,1);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
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
/***********�޸�����*************/
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
	printf("�û������޸�");
	gotoxy(38, 10);
	printf("�����������:");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	while (1)
	{
		gotoxy(51, 10);
		g_num = scanf_(oldPwd, 8, 1, 1);
		if (g_num == 1)
		{
			gotoxy(40, 15);
			printf("1.ȷ���˳�");
			gotoxy(40, 16);
			printf("2.ȡ��");
			gotoxy(40, 17);
			printf("������:[ ]\b\b");
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
			printf("�������!�����������");
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
		printf("������:");
		gotoxy(51, 12);
		g_num = scanf_(pwd, 6, 1, 1);
		if (g_num == 1)
		{
			gotoxy(40, 15);
			printf("1.ȷ���˳�");
			gotoxy(40, 16);
			printf("2.ȡ��");
			gotoxy(40, 17);
			printf("������:[ ]\b\b");
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
			printf("���볤��Ϊ��λ!");
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
			printf("ȷ������:");
			gotoxy(53, 14);
			g_num = scanf_(newpwd, 6, 1, 1);
			if (g_num == 1)
			{
				gotoxy(40, 15);
				printf("1.ȷ���˳�");
				gotoxy(40, 16);
				printf("2.ȡ��");
				gotoxy(40, 17);
				printf("������:[ ]\b\b");
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
				printf("�������벻һ��!");
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
	printf("�޸ĳɹ�!");
	printf("�����������");
	getch();
	system("cls");
	menu(head);
}
/***************ת��*************/
void Transfer(LINKIST_T* head)
{
	FILE* fp = NULL;
	LINKIST_T* pTemp = NULL;
	RECORD_T* Recordout = NULL;//ת��
	RECORD_T* Recordin = NULL;//ת��
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
	printf("��ESC������һ��");
	gotoxy(40, 8);
	printf("��ǰ���:%.2fԪ",curUser->money);
	gotoxy(40, 10);
	printf("������ת���˻�:");
	g_num = scanf_(id, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
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
		printf("ת���˻�������!");
		getch();
		system("cls");
		Transfer(head);
	}
	if (atoi(id) == curUser->bankID)
	{
		gotoxy(38, 16);
		printf("���ܹ�ת�˸��Լ�");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);
	}
	if (ptmp->role == 1)
	{
		gotoxy(38, 16);
		printf("���ܹ�ת�˸�����Ա");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);
	}
	if(ptmp->flag == 0)
	{
		gotoxy(38, 16);
		printf("���û���ע��");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);
	}
	gotoxy(40, 12);
	printf("ת�˽��:");
	g_num = scanf_(mon, 10, 1, 0);
	if (g_num == 1)
	{
		gotoxy(40, 15);
		printf("1.ȷ���˳�");
		gotoxy(40, 16);
		printf("2.ȡ��");
		gotoxy(40, 17);
		printf("������:[ ]\b\b");
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
		printf("ת�˽������100��������");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);

	}
	if (atoi(mon)>curUser->money)
	{
		gotoxy(38, 16);
		printf("��ǰ�˻�����");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);

	}
	if (atoi(mon) >=20000)
	{
		gotoxy(38, 16);
		printf("ת�˽��ܸ���2��");
		gotoxy(42, 17);
		printf("�����������");
		getch();
		system("cls");
		Transfer(head);

	}
	system("cls");
	drawUser();
	gotoxy(40, 10);
	printf("ת���˻���Ϣ����");
	gotoxy(40, 12);
	printf("ת���˻�:%s",id);
	gotoxy(40, 13);
	printf("ת�˽��:%d",atoi(mon));
	gotoxy(42, 16);
	printf("ȷ��ת��?Y/N");
	ch = getch();
	if(ch == 'y' || ch == 'Y')
	{
		curUser->money -= atoi(mon);
		ptmp->money += atoi(mon);

		fp = file_open("bank.txt");
		list_to_file(head, fp, sizeof(BANK_T));

		/*record_to_file((float)atoi(mon), curUser->money, curUser->bankID,2,(char)ptmp->bankID);
		record_to_file((float)atoi(mon),ptmp->money, ptmp->bankID,3, (char)curUser->bankID);*/
		//��ת����¼��Ϣ�浽�ṹ��
		
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
		
		
		//��ת���¼��Ϣ�浽�ṹ��
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

		//��������ӵ�����
		listAdd(g_rHead, Recordout);
		listAdd(g_rHead, Recordin);
		//������������д���ļ�
		//record_fp = file_open("record.txt");
		list_to_file(g_rHead, record_fp, sizeof(RECORD_T));
		gotoxy(42, 14);
		printf("ת�˳ɹ���");
		printf("�����������");
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

*��������exchangeMune(LINKIST_T* head)
*�������ܣ����׼�¼��ѯ����
*����������ʱ��ָ��
*�������أ�data����

*************************************************/
void exchangeMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.ȫ����ѯ\n");
	gotoxy(46, 9);
	printf("2.��ʱ���ѯ\n");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(46, 11);
	printf("������:[ ]\b\b");
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		exchangeMune(head);
	}
	break;
	}
}
/************************************************

*��������check_time_record(LINKIST_T* head)
*�������ܣ����׼�¼��ʱ���ѯ
*�����������û�����
*�������أ���

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
	char* type[4] = {"���","ȡ��","ת��","ת��"};
	char date1[9];
	char date2[9];
	int ymd1[3];  //������
	int ymd2[3];  //������
	int sub;
	
	system("cls");
	gotoxy(26, 2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM���˵������ڲ�ѯ");
	gotoxy(26, 6);
	printf("****************************************************");

	while(1)
	{
		while(1)
		{
			gotoxy(8,9);
			printf("��������ʼ����:");
			if(control_date(date1,ymd1)!=0)
			{	
				gotoxy(20,10);
				printf("���Ϸ�������ʱ��");
				getch();
				del_line(10,1);
			}
		
			else
				break;
			
		}

		while(1)
		{
			gotoxy(50,9);
			printf("�������������:");
			if(control_date(date2,ymd2)!=0)
			{	
				gotoxy(60,10);
				printf("���Ϸ�������ʱ��");
				getch();
				del_line(10,1);
			}
			
			else
				break;
		}
		sub = (ymd2[0]-ymd1[0])*365 + (ymd2[1] - ymd1[1])*30 + (ymd2[2]-ymd1[2]);//����������
		if(strcmp(date1,date2)>0)
		{
			gotoxy(40,10);
			printf("��ʼʱ����ڽ���ʱ��");
			getch();
			del_line(9,2);
		}
		else if(sub > 30)
		{
			gotoxy(40,10);
			printf("������ܴ���һ����");
			getch();
			del_line(9,2);
		}
		else
		{
		//	record_fp = file_open("record.txt");
		//	g_rHead = file_to_list(record_fp, sizeof(RECORD_T));
			sum = count_t(g_rHead,date1,date2);//�����ʱ��μ�¼����
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
					printf("ATM���˵������ڲ�ѯ");
					gotoxy(26, 6);
					printf("****************************************************");
					gotoxy(20,8);
					printf("���\t��ǰʱ��\t���\t���\tժҪ\t\t����Դ");
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
							printf("ATM��     \n");
						}
						else
						{
							printf("%s   \n",ptmp->source);
						}
 						j++;	
						
					}
					gotoxy(40,22);
					printf("��%d/%dҳ",page+1,pageSum);
					gotoxy(50,22);
					printf("1.��һҳ  2.��һҳ  3.�˳�:");
					ch = getch();			//1��ʾ��һҳ��2��ʾ��һҳ
					if(ch == '1' && page > 0)
					{
						page--;
					}
					else if(ch == '2' && start[page+1] != sum+1)//������һҳ��Ϊ��
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

*��������Exchange(LINKIST_T* head)
*�������ܣ����׼�¼ȫ����ѯ
*�����������û�����
*�������أ���

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
	char* type[4] = {"���","ȡ��","ת��","ת��"};
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
			printf("ATM���û����׼�¼����");
			gotoxy(26, 6);
			printf("****************************************************");
			gotoxy(20,8);
			printf("���\t��ǰʱ��\t���\t���\tժҪ\t\t����Դ");
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
					printf("ATM��     \n");
				}
				else
				{
					printf("%s   \n",ptmp->source);
				}
   				j++;
			}
			gotoxy(45,22);
			printf("��%d/%dҳ",page+1,pageSum);
			gotoxy(55,22);
			printf("1.��һҳ  2.��һҳ  3.�˳�:");
			ch = getch();			//1��ʾ��һҳ��2��ʾ��һҳ
			if(ch == '1' && page > 0)
			{
				page--;
			}
			else if(ch == '2' && start[page+1] != sum+1)//������һҳ��Ϊ��
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

*��������count_t(LINKIST_T* head,char *date1,char *date2)
*�������ܣ���������ʱ������Ľ��׼�¼������������¼д������
*�������������׼�¼������ʼ���ڣ���������
*�������أ���

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
		date = contime(ptmp->cur_time);//��ʱ��ת����"20190508"��ʽ
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

*��������count_t(LINKIST_T* head,char *date1,char *date2)
*�������ܣ����㽻�׼�¼������������¼д������
*�������������׼�¼����
*�������أ���

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

*��������count_t(LINKIST_T* head,char *date1,char *date2)
*�������ܣ���ʱ���ַ���ת��Ϊ"20190507"��ʽ
*����������ʱ��ָ��
*�������أ�data����

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
//�����׼�¼д���ļ�
/*
void record_to_file(float amount,float balance,long int id,int t_type,char source)
{
	RECORD_T* newRecord = NULL;
	FILE* fp = NULL;
	time_t rawtime;
	struct tm* timeinfo;
	char ctime[10];
	//����ռ�
	newRecord = (RECORD_T*)malloc(sizeof(RECORD_T));
	memset(newRecord,0,sizeof(RECORD_T));
	//��ṹ�����������
	newRecord->amount = amount;
	newRecord->balance = balance;
	newRecord->cur_id = id;
	strcpy(newRecord->source, source);
	newRecord->type = t_type;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ctime, "%4d-%02d-%02d", 1900 + timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday);
	strcpy(newRecord->cur_time, ctime);
	//��������ӵ�����
	listAdd(g_rHead, newRecord);

	//д���ļ�
	record_fp = file_open("record.txt");
	list_to_file(g_rHead, record_fp, sizeof(RECORD_T));

}
*/
