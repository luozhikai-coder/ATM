#ifndef _BANKACCOUNT_H_
#define _BANKACCOUNT_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "LinkList.h"
#include "public.h"
#include "login.h"
#include "file.h"

extern FILE* bankuser_fp;
extern LINKIST_T* g_Head;

void userInit();//��ʼ�������û���Ϣ
void drawAdmin();//���ƹ���Ա����title
void funMenu(LINKIST_T* head);//����Ա����ѡ��

void Staff_Add(LINKIST_T* head);//����Ա���

void Staff_del(LINKIST_T* head);//����Աɾ������ɾ����

void modifyMune(LINKIST_T* head);//�޸���Ϣ����
void Staffrole_Modify(LINKIST_T* head);//����Ա�޸��û���ɫ
void modifyPwdMune(LINKIST_T* head);//�û������޸Ľ���
void Staffpwd_Modify(LINKIST_T* head);//�û������޸�
void adminPwd_Modify(LINKIST_T* head);//����Ա��������
void searchMenu(LINKIST_T* head);//����Ա��ѯ����
void Staff_Class(LINKIST_T* head);//�����ѯ������Ա����ͨ�û���
void findClass(LINKIST_T* head, int irole);//�����ѯ����ʵ��
void findCon(LINKIST_T* head);//������ѯ����
void Staff_Search(LINKIST_T* head);//ʵ��ģ����ѯ
void Staff_Search1(LINKIST_T* head);//ʵ�־�ȷ��ѯ
int search(LINKIST_T* head);//ʵ��
//char* bankIdRand();//�������8λ���п���

#endif
