
#ifndef _LINKLIST_H_
#define _LINKLIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct bank
{
	long int bankID;      //员工帐号（依次递增）
	char bankAccount[10]; //用户名
	char bankPwd[10];     //密码
	int role;             //角色 0 用户 1 管理员
	int flag;             //标志位 0 离职 1 在职
	float money;          //余额

}BANK_T;

typedef struct rocord
{
	char cur_time[10];  //当前时间
	float  amount;		//金额
	float  balance;		//余额
	int    type;		//交易类型 0-存款 1-取款 2-转出 3-转入
	char   source[10];	//交易发生源 1 为ATM 
	long int cur_id;    //账单拥有者用户名	
}RECORD_T;

typedef struct list
{
	void* pData;         //数据域
	struct list* pNext;  //指针域，指向下一个节点地址
}LINKIST_T;

//extern char* role[2];
//extern char* status[2];

LINKIST_T* listCreate(void* data);//创建节点
void listPrint(LINKIST_T* head);//打印所有节点信息
void listAdd(LINKIST_T* head, void* data);//添加链表节点
int listDel(LINKIST_T* head, int index);//根据用户名删除（真删除）
LINKIST_T* list_getnode(LINKIST_T* head,int index);//获取第index个节点
int listCount(LINKIST_T* head);//计算链表长度
void listModify(LINKIST_T* head, char bankAccount[], void* data);//修改链表节点
void FuzzySearch(LINKIST_T* head, char* Str);//模糊查询


#endif
