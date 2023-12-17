#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include "LINKLIST.h"
FILE* file_open(char* filename);//文件打开

void list_to_file(LINKIST_T* head, FILE* fp, int size);//将链表中数据写到文件

LINKIST_T* file_to_list(FILE* fp, int size);//将文件中的数据读到链表中


#endif
