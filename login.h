#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "LinkList.h"
#include "bankAdmin.h"
#include "bankUser.h"
#include "public.h"

extern int g_num;
extern BANK_T* curUser;
void loginMenu();//��¼�������
BANK_T* login(LINKIST_T* head);//��¼����ʵ��
void userStatus(LINKIST_T* head);//������ݽ��벻ͬ����
#endif

