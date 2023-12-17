//������ز���
#include "LinkList.h"



/************************************************

*��������LINKIST_T* listCreate(void* data)
*�������ܣ�����һ������ڵ�
*�������������ͽṹ��ָ��
*�������أ��ýڵ�ĵ�ַ

*************************************************/
LINKIST_T* listCreate(void* data)
{
	LINKIST_T* pNode = NULL;

	pNode = (LINKIST_T*)malloc(sizeof(LINKIST_T));
	memset(pNode,0, sizeof(LINKIST_T));
	if (pNode == NULL)
	{
		printf("malloc fail��");
		return NULL;
	}
	pNode->pData = data;
	pNode->pNext = NULL;

	return pNode;
}

/************************************************

*��������void listPrint(LINKIST_T* head)
*�������ܣ���ӡ�����е�����
*�����������û�����ͷ���
*�������أ���

*************************************************/
void listPrint(LINKIST_T* head)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "�û�","����Ա" };
	char* status[2] = { "ע��","��Ч" };
	int count = 0;
	pTemp = head;
	printf("\n�������û���Ϣ:");
	printf("\n\nԱ���˺�\t�û���\t����\t�û�״̬\t���\t��ɫ\n\n");
	
	//��������ֱ��ָ����Ϊ��ʱ�˳�
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if (bankUser->flag == 1)
		{	
			printf("%ld\t%s\t%s\t%s\t\t%0.2f\t%s\n", bankUser->bankID, bankUser->bankAccount, bankUser->bankPwd,status[bankUser->flag],bankUser->money,role[bankUser->role]);
	
		}
		count++;
	}
//	printf("\n   �����������");
//	getch();
}
/************************************************

*��������void listAdd(LINKIST_T* head, void* data)
*�������ܣ�������β������½��
*�����������û�����ͷ���  ���ͽṹ��ָ��
*�������أ���

*************************************************/
void listAdd(LINKIST_T* head, void* data)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	//����������µĽڵ�
	LINKIST_T* pNode = NULL;
	
	pNode = listCreate(data);

	pTemp = head;
	//��������ֱ��ָ����Ϊ��ʱ�˳�ѭ��
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = pNode;

}

/************************************************

*��������int listDel(LINKIST_T* head,int index)
*�������ܣ�ɾ��ĳ���ڵ���Ϣ
*�����������û�����ͷ���  ɾ����index���ڵ�
*�������أ���

*************************************************/
int listDel(LINKIST_T* head,int index)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	//����Ҫɾ���Ľڵ�
	LINKIST_T* Temp = NULL;
	int flag = 0;
	//����������
	int count = 0;
	count = listCount(head);

	pTemp = head;
	if (count <index)
	{
		printf("\n���û�������!");
		return -1;
	}
	while (pTemp->pNext != NULL)
	{
		if (flag == index - 1)
		{
			//����Ҫ�ͷŽڵ�
			Temp = pTemp->pNext;
			//ǰһ���ڵ��ָ����ָ��Ҫɾ���ڵ����һ���ڵ�
			pTemp->pNext = pTemp->pNext->pNext;
			break;
		}
		pTemp = pTemp->pNext;
		flag++;
	}
	//���ͷ�������,���ͷŸýڵ�
	free(Temp->pData);
	free(Temp);
	return 0;
	
}

/**********************************

�������ܣ��õ���n�������ָ��,n��0��ʼ
���룺����ͷ�͵�n��
�������n�������ָ��

******************************/
LINKIST_T* list_getnode(LINKIST_T* head,int index)
{
	int i=-1;
	LINKIST_T* ptmp = head;
	while(ptmp!=NULL)
	{
		i++;
		if(i==index)
		{
			return ptmp;
		}
		ptmp=ptmp->pNext;
	}
	printf("NO such list\n");
	return NULL;
}


/************************************************

*��������int listCount(LINKIST_T* head)
*�������ܣ�����������
*�����������û�����ͷ���
*�������أ�������

*************************************************/
int listCount(LINKIST_T* head)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	int count = 0;
	pTemp = head;

	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		count++;
	}

	return count;
}

/************************************************

*��������void listModify(LINKIST_T* head,char bankAccount[], void* data)
*�������ܣ������û����޸�ĳ���ڵ���Ϣ
*�����������û�����ͷ��� �û��� �ṹ��ָ��
*�������أ���

*************************************************/
void listModify(LINKIST_T* head,char bankAccount[], void* data)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	int flag = 0;
	int count = 0;
	pTemp = head;
	count = listCount(head);
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		if (strcmp(bankUser->bankAccount,bankAccount) == 0)
		{
			pTemp->pData = data;
		}
		else if (flag+1>count)
		{
			printf("\n���û�������!");
		}
		flag++;
	}
}

//ʵ�־�ȷ��ѯ
void FuzzySearch(LINKIST_T* head, char* Str)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "�û�","����Ա" };
	char* status[2] = { "ע��","��Ч" };
	//char* pStr = NULL;
	int count = 0;
	pTemp = head;
	printf("\n�������û���Ϣ:");
	printf("\n\nԱ���˺�\t�û���\t����\t�û�״̬\t���\t��ɫ\n\n");
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		bankUser = pTemp->pData;
		
		if (strcmp(bankUser->bankAccount,Str) == 0)
		{
			printf("%ld\t%s\t%s\t%s\t\t%0.2f\t%s\n", bankUser->bankID, bankUser->bankAccount, bankUser->bankPwd, status[bankUser->flag], bankUser->money, role[bankUser->role]);
		}
		count++;
	}
	printf("\n   �����������");
	getch();
}


//�ͷ�����
void listFree(LINKIST_T* head)
{
	//����һ����ʱָ����ͷ���
	LINKIST_T* pTemp = NULL;

	pTemp = head;

	while(pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		free(pTemp->pData);
		free(pTemp);
	}
	free(head);
}

