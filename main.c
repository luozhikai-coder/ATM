#include <stdio.h>
#include "LinkList.h"
#include "login.h"
#include "file.h"

LINKIST_T* g_Head = NULL;//�û�����ͷ���
LINKIST_T* g_rHead = NULL;//���׼�¼����ͷ
LINKIST_T* newhead = NULL;//��ǰ�û����׼�¼����ͷ
//FILE* bankuser_fp = NULL;//�û��ļ�ָ��
FILE* record_fp = NULL;//�û���¼�ļ�ָ��
BANK_T* curUser = NULL;//��ǰ�û�


int start[10];
int g_num;

int main()
{
//	system("color 2e");
	//�û������ʼ��
	userInit();
	
	//���׼�¼��ʼ��
	userInio_r();
	//��¼��ɫ�жϣ����벻ͬ����
	userStatus(g_Head);
	
	//fclose(bankuser_fp);
	return 0;
}