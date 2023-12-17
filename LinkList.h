
#ifndef _LINKLIST_H_
#define _LINKLIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct bank
{
	long int bankID;      //Ա���ʺţ����ε�����
	char bankAccount[10]; //�û���
	char bankPwd[10];     //����
	int role;             //��ɫ 0 �û� 1 ����Ա
	int flag;             //��־λ 0 ��ְ 1 ��ְ
	float money;          //���

}BANK_T;

typedef struct rocord
{
	char cur_time[10];  //��ǰʱ��
	float  amount;		//���
	float  balance;		//���
	int    type;		//�������� 0-��� 1-ȡ�� 2-ת�� 3-ת��
	char   source[10];	//���׷���Դ 1 ΪATM 
	long int cur_id;    //�˵�ӵ�����û���	
}RECORD_T;

typedef struct list
{
	void* pData;         //������
	struct list* pNext;  //ָ����ָ����һ���ڵ��ַ
}LINKIST_T;

//extern char* role[2];
//extern char* status[2];

LINKIST_T* listCreate(void* data);//�����ڵ�
void listPrint(LINKIST_T* head);//��ӡ���нڵ���Ϣ
void listAdd(LINKIST_T* head, void* data);//�������ڵ�
int listDel(LINKIST_T* head, int index);//�����û���ɾ������ɾ����
LINKIST_T* list_getnode(LINKIST_T* head,int index);//��ȡ��index���ڵ�
int listCount(LINKIST_T* head);//����������
void listModify(LINKIST_T* head, char bankAccount[], void* data);//�޸�����ڵ�
void FuzzySearch(LINKIST_T* head, char* Str);//ģ����ѯ


#endif
