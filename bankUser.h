#ifndef _BANKUSER_H_
#define _BANKUSER_H_

#include "LinkList.h"
#include "login.h"

extern LINKIST_T* g_rHead;
extern LINKIST_T* newhead;
extern FILE* record_fp;
extern int start[10];

void drawUser();//�û�����title����
void userInio_r();//��ʼ�����׼�¼
void menu(LINKIST_T* head);//�û����ܽ���
void Inquiry(LINKIST_T* head);//�û�����ѯ
void Withdrawal(LINKIST_T* head);//ȡ��
void Deposit(LINKIST_T* head);//���
void Repass(LINKIST_T* head);//�û������޸�
void Transfer(LINKIST_T* head);//ת��
void exchangeMune(LINKIST_T* head);
void Exchange(LINKIST_T* head);//���׼�¼��ѯ
int check_time_record(LINKIST_T* head);//��ʱ���ѯ
void record_to_file(float amount, float balance, long int id, int type, char source);//���׼�¼д���ļ�
int count_t(LINKIST_T* head,char *date1,char *date2);
int count_r();//���㽻�׼�¼����
char* contime(char *time);
#endif 

