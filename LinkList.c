//链表相关操作
#include "LinkList.h"



/************************************************

*函数名：LINKIST_T* listCreate(void* data)
*函数功能：创建一个链表节点
*函数参数：泛型结构体指针
*函数返回：该节点的地址

*************************************************/
LINKIST_T* listCreate(void* data)
{
	LINKIST_T* pNode = NULL;

	pNode = (LINKIST_T*)malloc(sizeof(LINKIST_T));
	memset(pNode,0, sizeof(LINKIST_T));
	if (pNode == NULL)
	{
		printf("malloc fail！");
		return NULL;
	}
	pNode->pData = data;
	pNode->pNext = NULL;

	return pNode;
}

/************************************************

*函数名：void listPrint(LINKIST_T* head)
*函数功能：打印链表中的数据
*函数参数：用户链表头结点
*函数返回：无

*************************************************/
void listPrint(LINKIST_T* head)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "用户","管理员" };
	char* status[2] = { "注销","有效" };
	int count = 0;
	pTemp = head;
	printf("\n以下是用户信息:");
	printf("\n\n员工账号\t用户名\t密码\t用户状态\t余额\t角色\n\n");
	
	//遍历链表，直到指针域为空时退出
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
//	printf("\n   按任意键返回");
//	getch();
}
/************************************************

*函数名：void listAdd(LINKIST_T* head, void* data)
*函数功能：向链表尾部添加新结点
*函数参数：用户链表头结点  泛型结构体指针
*函数返回：无

*************************************************/
void listAdd(LINKIST_T* head, void* data)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	//创建链表的新的节点
	LINKIST_T* pNode = NULL;
	
	pNode = listCreate(data);

	pTemp = head;
	//遍历链表，直到指针域为空时退出循环
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = pNode;

}

/************************************************

*函数名：int listDel(LINKIST_T* head,int index)
*函数功能：删除某个节点信息
*函数参数：用户链表头结点  删除第index个节点
*函数返回：无

*************************************************/
int listDel(LINKIST_T* head,int index)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	//保存要删除的节点
	LINKIST_T* Temp = NULL;
	int flag = 0;
	//计算链表长度
	int count = 0;
	count = listCount(head);

	pTemp = head;
	if (count <index)
	{
		printf("\n该用户不存在!");
		return -1;
	}
	while (pTemp->pNext != NULL)
	{
		if (flag == index - 1)
		{
			//保存要释放节点
			Temp = pTemp->pNext;
			//前一个节点的指针域指向要删除节点的下一个节点
			pTemp->pNext = pTemp->pNext->pNext;
			break;
		}
		pTemp = pTemp->pNext;
		flag++;
	}
	//先释放数据域,再释放该节点
	free(Temp->pData);
	free(Temp);
	return 0;
	
}

/**********************************

函数功能：得到第n个链表的指针,n从0开始
输入：链表头和第n个
输出：第n个链表的指针

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

*函数名：int listCount(LINKIST_T* head)
*函数功能：计算链表长度
*函数参数：用户链表头结点
*函数返回：链表长度

*************************************************/
int listCount(LINKIST_T* head)
{
	//定义一个临时指针存放头结点
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

*函数名：void listModify(LINKIST_T* head,char bankAccount[], void* data)
*函数功能：根据用户名修改某个节点信息
*函数参数：用户链表头结点 用户名 结构体指针
*函数返回：无

*************************************************/
void listModify(LINKIST_T* head,char bankAccount[], void* data)
{
	//定义一个临时指针存放头结点
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
			printf("\n该用户不存在!");
		}
		flag++;
	}
}

//实现精确查询
void FuzzySearch(LINKIST_T* head, char* Str)
{
	//定义一个临时指针存放头结点
	LINKIST_T* pTemp = NULL;
	BANK_T* bankUser = NULL;
	char* role[2] = { "用户","管理员" };
	char* status[2] = { "注销","有效" };
	//char* pStr = NULL;
	int count = 0;
	pTemp = head;
	printf("\n以下是用户信息:");
	printf("\n\n员工账号\t用户名\t密码\t用户状态\t余额\t角色\n\n");
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
	printf("\n   按任意键返回");
	getch();
}


//释放链表
void listFree(LINKIST_T* head)
{
	//定义一个临时指针存放头结点
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

