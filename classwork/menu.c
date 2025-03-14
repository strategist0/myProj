#include "menu.h"
#include <stdio.h>

#define NONE "\033[0m"
#define GREEN "\033[0;32;32m"
#define YELLOW "\033[0;33;33m"
#define BLUE "\033[0;34;34m"
#define RED "\033[0;32;31m"

void displayMenu() {
    printf(GREEN "\n====== 个人图书管理系统 ======\n" NONE);
    printf(YELLOW "1. 添加图书\n" NONE);
    printf(YELLOW "2. 删除图书\n" NONE);
    printf(YELLOW "3. 更新图书信息\n" NONE);
    printf(YELLOW "4. 查找图书\n" NONE);
    printf(YELLOW "5. 显示所有图书\n" NONE);
    printf(YELLOW "6. 退出\n" NONE);
    printf(GREEN "=========================\n" NONE);
    printf("请输入您的选择: ");
}

void displayMenu1() {
    printf(BLUE
           "\n====================================================\n" NONE);
    printf(BLUE "               图书用户账号管理系统\n" NONE);
    printf(BLUE "====================================================\n" NONE);
    printf(GREEN "1. 注册账号\n" NONE);
    printf(GREEN "2. 登录\n" NONE);
    printf(GREEN "3. 修改密码\n" NONE);
    printf(GREEN "4. 退出系统\n" NONE);
    printf(BLUE "====================================================\n" NONE);
    printf(BLUE "请输入您的选择: " NONE);
}