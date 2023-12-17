//����Ա����ʵ��
#include "bankAdmin.h"

//��ʼ�������û���Ϣ
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
		//��ʼ�������ڵ�
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
//���ƹ���Ա����title
void drawAdmin()
{
	gotoxy(26,2);
	printf("****************************************************");
	gotoxy(44, 4);
	printf("ATM������Ա����");
	gotoxy(26, 6);
	printf("****************************************************");
}

void funMenu(LINKIST_T* head)//����Ա����ѡ��
{
	char num[5];
//	int n;
	LINKIST_T* TMP = NULL;
	while (1)
	{
		TMP = head;
		drawAdmin();
		gotoxy(46, 8);
		printf("1.�û���ѯ");
		gotoxy(46, 9);
		printf("2.ע���û�");
		gotoxy(46, 10);
		printf("3.�û��޸�");
		gotoxy(46, 11);
		printf("4.�û�ɾ��");
		gotoxy(65, 20);
		printf("��ESC������һ��");
		gotoxy(46, 12);
		printf("5.�˳�ϵͳ");
		gotoxy(46, 15);
		printf("��ѡ��:[ ]\b\b");
		g_num = scanf_(num, 1, 1, 0);//ESC�����˳�����
		if (g_num == 1)
		{
			gotoxy(42, 18);
			printf("1.ȷ���˳�");
			gotoxy(42, 19);
			printf("2.ȡ��");
			gotoxy(42, 20);
			printf("������:[ ]\b\b");
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
		case 1://�û���ѯ
		{
			system("cls");
			while (1)
			{
				searchMenu(TMP);
			}

		}
		break;
		case 2://�û����
		{
			system("cls");
			Staff_Add(TMP);
		}
		break;
		case 3://�û������޸�
		{
			system("cls");
			modifyMune(TMP);
		}
		break;
		case 4://�û�ɾ��
		{
			system("cls");
			Staff_del(TMP);
			funMenu(TMP);
		}
		break;
		case 5://�˳�ϵͳ
		{
			gotoxy(42, 18);
			printf("1.ȷ���˳�");
			gotoxy(42, 19);
			printf("2.ȡ��");
			gotoxy(42, 20);
			printf("������:[ ]\b\b");
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
			printf("�밴��ʾ����");
			Sleep(1000);
			system("cls");
			funMenu(TMP);
		}
		break;
		}
	}
}


//���Ա����Ϣ
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
	printf("�û����");
	gotoxy(42, 10);
	printf("�� �� ��:");
	gotoxy(42, 11);
	printf("��    ��:");
	gotoxy(42, 12);
	printf("ȷ������:");
	gotoxy(42, 13);
	printf("��    ɫ:");
	gotoxy(42, 14);
	printf("0---�û� 1---����Ա");
	gotoxy(65, 20);
	printf("��ESC������һ��");
	gotoxy(51,10);
	g_num = scanf_(name,8,2,0);
	if (g_num == 1)
	{
		gotoxy(42, 18);
		printf("1.ȷ���˳�");
		gotoxy(42, 19);
		printf("2.ȡ��");
		gotoxy(42, 20);
		printf("������:[ ]\b\b");
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
			printf("���û�������!");
			getch();
			system("cls");
			Staff_Add(head);
		}
	}
	if (strlen(name) < 4)
	{
		gotoxy(44, 18);
		printf("�û������ȱ��������!");
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
			printf("1.ȷ���˳�");
			gotoxy(42, 19);
			printf("2.ȡ��");
			gotoxy(42, 20);
			printf("������:[ ]\b\b");
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
			printf("���볤��Ϊ��λ!");
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
				printf("1.ȷ���˳�");
				gotoxy(42, 19);
				printf("2.ȡ��");
				gotoxy(42, 20);
				printf("������:[ ]\b\b");
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
				printf("�������벻һ��!");
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
			printf("��������Ч�Ľ�ɫ");
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
	printf("��ӳɹ�!�����˺���%ld   ",newstaff->bankID);
	printf("�����������");
	getch();
	system("cls");
	Staff_Add(head);
	
}

//ɾ���û���Ϣ(ʵ�ּ�ɾ��)
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
	printf("��ESC������һ��");
	gotoxy(0,7);
	printf("������Ҫɾ�����û���:");
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
				printf("��Ϊ��!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else if(strcmp(curUser->bankAccount,name) == 0)
			{
				gotoxy(40, 15);
				printf("����ɾ���Լ�!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else if (bankUser->flag == 0)
			{
				gotoxy(40,15);
				printf("���û���ע��!");
				getch();
				system("cls");
			}
			else if(bankUser->role == 1)
			{
				gotoxy(40, 15);
				printf("����ɾ������Ա!");
				getch();
				system("cls");
				Staff_del(head);
			}
			else
			{
			    bankUser->flag = 0;
				gotoxy(2, 20);
				printf("ע���ɹ�!");
				printf("�����������");
				getch();
				system("cls");
			}
			
		}
		else if (flag >= count-1)
		{
			gotoxy(40, 15);
			printf("���û�������!");
			getch();
			system("cls");
			Staff_del(head);
		}
		flag++;
	}
	fp = file_open("bank.txt");
	list_to_file(head, fp, sizeof(BANK_T));
}
//�޸�Ա����Ϣ����
void modifyMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.�޸��û���ɫ\n");
	gotoxy(46, 9);
	printf("2.�޸��û�����\n");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(46, 11);
	printf("������:[ ]\b\b");
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		modifyMune(head);
	}
	break;
	}
}
//�û���ɫ�޸�
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
	printf("�û�����޸�");
	gotoxy(38, 10);
	printf("������Ҫ�޸ĵ��û���:");
	gotoxy(75, 20);
	printf("��ESC������һ��");

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
			printf("�����û����:");

			gotoxy(51, 12);
			scanf("%d", &role);

			bankUser->role = role;
			fp = file_open("bank.txt");
			list_to_file(head, fp, sizeof(BANK_T));
			gotoxy(40, 16);
			printf("�޸ĳɹ�!");
			printf("�����������");
			break;
			
		}
		else if(flag>count-1)
		{
			gotoxy(40, 15);
			printf("���û�������!");
			getch();
			system("cls");
			Staffrole_Modify(head);
		}
		flag++;
	}
	getch();
	system("cls");
}
//�û������޸�ҳ��
void modifyPwdMune(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.�޸��û�����");
	gotoxy(46, 9);
	printf("2.�޸Ĳ�������");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(46, 11);
	printf("������:[ ]\b\b");
	g_num = scanf_(num, 10, 1, 0);
	if (g_num == 1)
	{
		system("cls");
		funMenu(head);
	}
	switch (atoi(num))
	{
	case 1://��ͨ�û������޸�
	{
		system("cls");
		Staffpwd_Modify(head);

	}
	break;
	case 2://����Ա�Լ�����������޸�
	{
		system("cls");
		adminPwd_Modify(head);
	}
	break;
	default:
	{
		gotoxy(44,18); 
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		modifyPwdMune(head);
	}
	break;
	}
}
//�޸Ĺ���Ա��������
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
	printf("���������޸�");
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
			system("cls");
			modifyPwdMune(head);
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
		printf("����:");
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
			printf("���볤��Ϊ��λ!");
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
			printf("ȷ������:");
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
				printf("�������벻һ��!");
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
	printf("�޸ĳɹ�!");
	printf("�����������");
	getch();
	system("cls");
	modifyPwdMune(head);
}
//�û������޸�
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
	printf("�û������޸�");
	gotoxy(38, 10);
	printf("������Ҫ�޸ĵ��û���:");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	
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
		printf("���û�������!");
		getch();
		system("cls");
		gotoxy(40, 15);
		printf("                 ");
		Staffpwd_Modify(head);
	}
	if(bankUser->role == 1)
	{
		gotoxy(40, 15);
		printf("�����޸Ĺ���Ա!");
		getch();
		system("cls");
		gotoxy(40, 15);
		printf("                 ");
		Staffpwd_Modify(head);
	}
	while (1)
	{
		gotoxy(44, 12);
		printf("����:");
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
			printf("���볤��Ϊ��λ!");
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
			printf("ȷ������:");
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
				printf("�������벻һ��!");
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
	printf("�޸ĳɹ�!");
	printf("�����������");
	getch();
	system("cls");
	modifyPwdMune(head);
}
//��ѯģ��
void searchMenu(LINKIST_T* head)
{
	char num[10];
	drawAdmin();
	gotoxy(46, 8);
	printf("1.ȫ����ѯ\n");
	gotoxy(46, 9);
	printf("2.�����ѯ\n");
	gotoxy(46, 10);
	printf("3.������ѯ\n");
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(46, 12);
	printf("������:[ ]\b\b");
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
		printf("�����������");
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		searchMenu(head);
	}
	break;
	}
}
//�����ѯ������Ա���û���ѯ��
void Staff_Class(LINKIST_T* head)
{
	char num[10];
	system("cls");
	drawAdmin();
	gotoxy(46, 8);
	printf("1.��ѯ����Ա");
	gotoxy(46, 9);
	printf("2.��ѯ�û�");
	gotoxy(65, 20);
	printf("��ESC������һ��");
	gotoxy(46, 11);
	printf("������:[ ]\b\b");
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		Staff_Class(head);
	}
	break;
	}


}
//�����ѯ����ʵ��
void findClass(LINKIST_T* head,int irole)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "�û�","����Ա" };
    char* status[2] = { "ע��","��Ч" };
	int count = 0;
	pTemp = head;
	printf("\n\nԱ���˺�\t�û���\t����\t�û�״̬\t��ɫ\n\n");
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
	printf("\n   �����������");
	getch();
	system("cls");
	Staff_Class(head);
}
//������ѯ
void findCon(LINKIST_T* head)
{
	char num[10];
	system("cls");
	drawAdmin();
	gotoxy(46, 8);
	printf("1.ģ����ѯ");
	gotoxy(46, 9);
	printf("2.��ȷ��ѯ");
	gotoxy(65, 20);
	printf("��ESC������һ��");
	gotoxy(46, 11);
	printf("������:[ ]\b\b");
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
		printf("�밴��ʾ����");
		Sleep(1000);
		system("cls");
		findCon(head);
	}
	break;
	}
}
//���ݹؼ���ʵ�־�ȷ��ѯ
void Staff_Search1(LINKIST_T* head)
{
	char name[10];
	system("cls");
	drawAdmin();
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(40,8);
	printf("�û�����ȷƥ��");
	gotoxy(40,10);
	printf("������ؼ���:");
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
//���ݹؼ���ʵ��ģ����ѯ
void Staff_Search(LINKIST_T* head)
{
	//char name[10];
	system("cls");
	drawAdmin();
	gotoxy(75, 20);
	printf("��ESC������һ��");
	gotoxy(40,8);
	printf("�û���ģ��ƥ��");
	gotoxy(40,10);
	printf("������ؼ���:");
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

//ʵ��ģ����ѯ
int search(LINKIST_T* head)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	char* pStr = NULL;
	BANK_T* bankUser = NULL;
	char str[12];
	char cstr[12];
	int i;
	char* role[2] = { "�û�","����Ա" };
    char* status[2] = { "ע��","��Ч" };
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
		printf("��ESC������һ��");
		gotoxy(40,8);
		printf("�û���ģ��ƥ��");
		gotoxy(40, 10);
		printf("������ؼ���:%s",cstr);
		gotoxy(0, 12);
		printf("Ա���˺�\t�û���\t����\t�û�״̬\t���\t��ɫ");
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
