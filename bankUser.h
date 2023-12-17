#ifndef _BANKUSER_H_
#define _BANKUSER_H_

#include "LinkList.h"
#include "login.h"

extern LINKIST_T* g_rHead;
extern LINKIST_T* newhead;
extern FILE* record_fp;
extern int start[10];

void drawUser();//用户界面title绘制
void userInio_r();//初始化交易记录
void menu(LINKIST_T* head);//用户功能界面
void Inquiry(LINKIST_T* head);//用户余额查询
void Withdrawal(LINKIST_T* head);//取款
void Deposit(LINKIST_T* head);//存款
void Repass(LINKIST_T* head);//用户密码修改
void Transfer(LINKIST_T* head);//转账
void exchangeMune(LINKIST_T* head);
void Exchange(LINKIST_T* head);//交易记录查询
int check_time_record(LINKIST_T* head);//按时间查询
void record_to_file(float amount, float balance, long int id, int type, char source);//交易记录写入文件
int count_t(LINKIST_T* head,char *date1,char *date2);
int count_r();//计算交易记录总数
char* contime(char *time);
#endif 

