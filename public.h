#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

HANDLE handle;
COORD coord;

int scanf_(char acStr[], int iMaxLen, int iPutType, int isPlaintext);//�����������
int gotoxy(int x, int y);//���ù��λ��
void getxy(int* x, int* y);//��ȡ���λ��
int color(int c);//����������ɫ
void showTime();//��ʾ��ǰʱ��
int control_date(char data[9],int date[3]);//�������ڿ���
void del_line(int col,int num);//ɾ������

#endif
