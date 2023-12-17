#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "LinkList.h"
#include "bankAdmin.h"
#include "bankUser.h"
#include "public.h"

extern int g_num;
extern BANK_T* curUser;
void loginMenu();//登录界面绘制
BANK_T* login(LINKIST_T* head);//登录功能实现
void userStatus(LINKIST_T* head);//根据身份进入不同界面
#endif

