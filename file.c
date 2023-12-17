#include "file.h"

/************************************************

*��������FILE * file_open(char * filename)
*�������ܣ����ļ�������ֱ�Ӵ��ļ������򴴽�һ�����ļ�
*�����������ļ���
*�������أ��ļ�ָ��

*************************************************/
FILE * file_open(char * filename)
{
	FILE* fp;
	//����ļ����ڣ�ֱ�Ӵ�
	fp = fopen(filename,"rb+");
	//����ļ������ڣ�����һ���µ��ļ�
	if(fp == NULL)
	{
		fp = fopen(filename,"wb+");
	}
	return fp;
}

/************************************************

*��������void list_to_file(LINKIST_T * head,FILE * fp,int size)
*�������ܣ��������е�����д���ļ�
*��������������ͷ���,�ļ�ָ��,д�����ݴ�С
*�������أ���

*************************************************/

void list_to_file(LINKIST_T * head,FILE * fp,int size)
{
	LINKIST_T* pTemp = NULL;
	pTemp = head;

	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		//�������е�������һд���ļ�
		fwrite(pTemp->pData, size,1, fp);
	}
	fflush(fp);
}

/************************************************

*��������LINKIST_T* file_to_list(FILE * fp,int size)
*�������ܣ����ļ��е�����д������
*�����������ļ�ָ��,д�����ݴ�С
*�������أ�����ͷ���

*************************************************/
LINKIST_T* file_to_list(FILE * fp,int size)
{
	LINKIST_T* head = NULL;

	void* data = NULL;
	size_t ret = -1;
	rewind(fp);                  //�ļ�ָ�븴λ
	head = listCreate(NULL);
	
	while (1)
	{
		data = malloc(size);
		memset(data, 0, size);
		ret = fread(data,size,1,fp);
 		if (ret < 1)
		{
			break;
		}
		listAdd(head, data);
	}
	return head;
}