#include "file.h"

/************************************************

*函数名：FILE * file_open(char * filename)
*函数功能：若文件存在则直接打开文件，否则创建一个新文件
*函数参数：文件名
*函数返回：文件指针

*************************************************/
FILE * file_open(char * filename)
{
	FILE* fp;
	//如果文件存在，直接打开
	fp = fopen(filename,"rb+");
	//如果文件不存在，创建一个新的文件
	if(fp == NULL)
	{
		fp = fopen(filename,"wb+");
	}
	return fp;
}

/************************************************

*函数名：void list_to_file(LINKIST_T * head,FILE * fp,int size)
*函数功能：将链表中的数据写入文件
*函数参数：链表头结点,文件指针,写入数据大小
*函数返回：无

*************************************************/

void list_to_file(LINKIST_T * head,FILE * fp,int size)
{
	LINKIST_T* pTemp = NULL;
	pTemp = head;

	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		//将链表中的数据逐一写到文件
		fwrite(pTemp->pData, size,1, fp);
	}
	fflush(fp);
}

/************************************************

*函数名：LINKIST_T* file_to_list(FILE * fp,int size)
*函数功能：将文件中的数据写入链表
*函数参数：文件指针,写入数据大小
*函数返回：链表头结点

*************************************************/
LINKIST_T* file_to_list(FILE * fp,int size)
{
	LINKIST_T* head = NULL;

	void* data = NULL;
	size_t ret = -1;
	rewind(fp);                  //文件指针复位
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