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

void userInit();//初始化三个用户信息
void drawAdmin();//绘制管理员界面title
void funMenu(LINKIST_T* head);//管理员功能选择

void Staff_Add(LINKIST_T* head);//管理员添加

void Staff_del(LINKIST_T* head);//管理员删除（假删除）

void modifyMune(LINKIST_T* head);//修改信息界面
void Staffrole_Modify(LINKIST_T* head);//管理员修改用户角色
void modifyPwdMune(LINKIST_T* head);//用户密码修改界面
void Staffpwd_Modify(LINKIST_T* head);//用户密码修改
void adminPwd_Modify(LINKIST_T* head);//管理员操作密码
void searchMenu(LINKIST_T* head);//管理员查询界面
void Staff_Class(LINKIST_T* head);//分类查询（管理员，普通用户）
void findClass(LINKIST_T* head, int irole);//分类查询功能实现
void findCon(LINKIST_T* head);//条件查询界面
void Staff_Search(LINKIST_T* head);//实现模糊查询
void Staff_Search1(LINKIST_T* head);//实现精确查询
int search(LINKIST_T* head);//实现
//char* bankIdRand();//随机生成8位银行卡号

#endif
