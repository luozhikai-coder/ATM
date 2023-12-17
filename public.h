#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

HANDLE handle;
COORD coord;

int scanf_(char acStr[], int iMaxLen, int iPutType, int isPlaintext);//控制输入输出
int gotoxy(int x, int y);//设置光标位置
void getxy(int* x, int* y);//获取光标位置
int color(int c);//设置文字颜色
void showTime();//显示当前时间
int control_date(char data[9],int date[3]);//输入日期控制
void del_line(int col,int num);//删除多行

#endif
