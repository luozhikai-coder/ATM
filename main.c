#include <stdio.h>
#include "LinkList.h"
#include "login.h"
#include "file.h"

LINKIST_T* g_Head = NULL;//用户链表头结点
LINKIST_T* g_rHead = NULL;//交易记录链表头
LINKIST_T* newhead = NULL;//当前用户交易记录链表头
//FILE* bankuser_fp = NULL;//用户文件指针
FILE* record_fp = NULL;//用户记录文件指针
BANK_T* curUser = NULL;//当前用户


int start[10];
int g_num;

int main()
{
//	system("color 2e");
	//用户链表初始化
	userInit();
	
	//交易记录初始化
	userInio_r();
	//登录角色判断，进入不同界面
	userStatus(g_Head);
	
	//fclose(bankuser_fp);
	return 0;
}