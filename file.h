#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include "LINKLIST.h"
FILE* file_open(char* filename);//�ļ���

void list_to_file(LINKIST_T* head, FILE* fp, int size);//������������д���ļ�

LINKIST_T* file_to_list(FILE* fp, int size);//���ļ��е����ݶ���������


#endif
