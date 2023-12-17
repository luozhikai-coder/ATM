#include "public.h"

/*******************************************************************
名称：允许输入字母和数字的函数
参数：
acStr 表示: 保存的数组
iMaxLen表示: 最大输入字符数
iPutType表示:
0 (无控制) 1(只能输入数字) 2(只能输入字母)
3 (只能输入数字和字母)
isPlaintext表示是否显示明文 1表示明文
***************************************************************/
int scanf_(char acStr[20], int iMaxLen, int iPutType, int isPlaintext)
{

	int iLen = 0;//当前长度
	char ch = 0;
	int x, y;
	int j;
	int offset = 0;//左右的偏移量
	memset(acStr,0,sizeof(char)*20);
	acStr[0] = '\0';
	
	//int i = 0;
	while (1)
	{
		ch = getch();
		if (ch == '\b')//回删控制
		{
			if (iLen > 0)
			{
				if (acStr[iLen] == 0)		//光标在末尾
				{
					iLen--;
					acStr[iLen] = 0;
			
					printf("\b \b");

				}
				else if (acStr[iLen] != 0 )				//光标在中间
				{
					j = iLen;
					getxy(&x, &y);
					while (acStr[j] != 0)
					{
						acStr[j] = acStr[j + 1];
						j++;
						printf("%c", !isPlaintext ? acStr[j] : '*');
					}
					gotoxy(x, y);
				}
			}

		}
		if (ch == '\r')//回车控制
		{
			if (iLen > 0)
			{	
				break;
			}
			if (!iLen)
			{
				printf("输入不能为空");
				getch();
				printf("\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b");
			}

		}
 		if (ch == 27)//ESC键退出
		{
			return 1;
		}
		if (ch == -32)
		{
			ch = getch();
			if (ch == 75)
			{
				if (iLen > 0)
				{
					getxy(&x, &y);
					gotoxy(--x, y);
					offset++;

					iLen--;
				}

			}
			if (ch == 77)
			{
				if (offset!=0)
				{
					getxy(&x, &y);
					gotoxy(++x, y);
					offset--;
					iLen++;
				}

			}
		}
		else
		{
			if (iLen < iMaxLen)
			{
				switch (iPutType)
				{
				case 0:
					if (ch != '\b' && ch != '\r')
					{
						if (isPlaintext == 0)
						{
							putchar(ch);
						}
						else
						{
							putchar('*');
						}
						acStr[iLen] = ch;
						iLen++;
					}


					break;
				case 1:

					if (ch >= '0' && ch <= '9')
					{
						if (isPlaintext == 0)
						{
							putchar(ch);
						}
						else
						{
							putchar('*');
						}
						acStr[iLen] = ch;
						iLen++;
					}

					break;
				case 2:

					if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
					{
						if (isPlaintext == 0)
						{
							putchar(ch);
						}
						else
						{
							putchar('*');
						}
						acStr[iLen] = ch;
						iLen++;
					}

					break;
				case 3:

					if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
					{
						if (isPlaintext == 0)
						{
							putchar(ch);
						}
						else
						{
							putchar('*');
						}
						acStr[iLen] = ch;
						iLen++;
					}

					break;
					/*
				case 4:
					putch(ch);
					break;
					*/
				default:
				{
					exit(0);
				}
				break;
				}
			}

		}
		
	}
	return 0;
}

/************************************************

*函数名：gotoxy(int x, int y)
*函数功能：设置当前光标位置
*函数参数：x , y坐标
*函数返回：无

*************************************************/
int gotoxy(int x, int y)
{
	HANDLE handle;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
	return 0;
}

/************************************************

*函数名：getxy(int* x, int* y)
*函数功能：获取当前光标位置
*函数参数：x , y坐标
*函数返回：无

*************************************************/
void getxy(int* x, int* y) //获取当前光标位置,调用：getxy(&x,&y);
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;
	}
}

/******************************

函数功能：控制字体颜色
输入：整数c
返回：返回0

*******************************
int color(int c)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, c);
	return 0;
}
*/

/******************************

函数功能：显示时间
函数参数：无
返回：无

********************************/
void showTime()
{
	time_t rawtime;
	struct tm* timeinfo;
	int tmp = 0;
	//printf ( "The current date/time is: %s\n", asctime (timeinfo) );
	while (!kbhit())
	{
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		if (tmp != timeinfo->tm_sec)
		{
			gotoxy(0, 0);
			printf("当前时间为:%4d-%02d-%02d %02d:%02d:%02d\n", 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			tmp = timeinfo->tm_sec;
		}
		
		
	}
	
	

}


/******************************

函数功能：输入日期控制函数
输入：接收指针
返回：返回1表示日期格式错误，2表示超过当前日期，0表示正确

********************************/
int control_date(char data[9],int date[3])
{														
	int i;												
	char ch;
	time_t t;
    struct tm * lt;

	printf("----/--/--");printf("\b\b\b\b\b\b\b\b\b\b");	
	
	i=0;
	while(1)
	{	
			//show_time();
			ch=getch();
			if(ch>='0'&&ch<='9'&&i<10)
			{
				
				printf("%c",ch);
				if(i==3||i==5)
					printf("/");
				
				data[i]=ch;
				i++;
				
			}
			else if(ch == 27)
			{
				return 3;
			}
			else if((i>0)&&(ch=='\b'))
			{
				
				if(i==4||i==6)
					printf("\b\b-/\b\b");
				else
				printf("\b-\b");
				i--;
			}
			else if((ch=='\r')&&(i == 8))
				break;	
	
	}
	data[i]='\0';

	date[1] =( data[4]-'0')*10+(data[5]-'0');//月份越界检查
	if(date[1] < 1||date[1] > 12)
		return 1;

	date[2] = (data[6]-'0')*10+(data[7]-'0');//日期越界检查
	if(date[2] > 31)
		return 1;
	date[0] = (data[0]-'0')*1000 + (data[1]-'0')*100 + (data[2]-'0')*10 + (data[3]-'0');

	time (&t);				//获取时间
	lt = localtime (&t);	//转为tm时间结构。
	
	if((lt->tm_year+1900<date[0]) || (lt->tm_year+1900 == date[0] && (lt->tm_mon+1) < date[1]) ||
			(lt->tm_year+1900 == date[0] && (lt->tm_mon+1) == date[1] && lt->tm_mday < date[2] ) )
	{
		return 2;
	}

	return 0;
}
/*************************************************************

  函数功能：删除多行
  函数参数：从第col行开始，删除num行

**************************************************************/
void del_line(int col,int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		gotoxy(0,col+i);
		printf("\r%*c\r",79,' ');
	}
}


/*上下左右键控制光标移动
void show_time()
{
	time_t t;
	struct tm* lt;
	int tmp;
	int x, y;
	getxy(&x, &y);


	while (!kbhit())
	{
		time(&t);				//获取时间
		lt = localtime(&t);	//转为tm时间结构。

		if (tmp != lt->tm_sec)
		{
			setxy(0, 0);
			printf("%d年%2d月%2d日 %02d:%02d:%02d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			tmp = lt->tm_sec;
			setxy(x, y);
		}
	}
	//setxy(x,y);

}
*/
