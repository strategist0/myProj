#include "user.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "tree.h"

user users[MAX_USERS];
int usercount = 0;

int findUser(const char* username) {
    for (int i = 0; i < usercount; i++) {
        if (strcmp(users[i].id, username) == 0) {
            return i;
        }
    }
    return -1;
}

int registerUser(user* u) {
    if (usercount >= MAX_USERS) {
        printf(RED "用户数量已达上限！" NONE);
        getchar();
        printf("\033[H\033[J");
        return -1;
    }

    printf("请输入ID(最大32个字符): ");
    scanf("%s", u->id);
    while (getchar() != '\n' && getchar() != EOF)
        ;
    printf("\033[H\033[J");
    if (findUser(u->id) != -1) {
        printf(RED "该ID已被注册！" NONE);
        getchar();
        printf("\033[H\033[J");
        return -1;
    }

    while (1) {
        printf("用户ID：%s\n", u->id);
        printf("请输入密码(最小6个字符, 最大16个字符): ");
        int i = 0;
        while (1) {
            u->password[i] = _getch();
            if (u->password[i] == '\r' || u->password[i] == '\n') {
                u->password[i] = '\0';
                break;
            }
            if (u->password[i] == '\b') {
                if (i > 0) {
                    printf("\b \b");
                    i--;
                }
            } else {
                printf("*");
                i++;
            }
        }
        if (strlen(u->password) < MIN_PASS_LEN ||
            strlen(u->password) > MAX_PASS_LEN) {
            printf(YELLOW "密码长度必须在%d到%d个字符之间！" NONE, MIN_PASS_LEN,
                   MAX_PASS_LEN);
            memset(u->password, 0, MAX_PASS_LEN);
            getchar();
            printf("\033[H\033[J");
        } else {
            break;
        }
    }
    strcpy(users[usercount].password, u->password);
    strcpy(users[usercount].id, u->id);
    usercount++;
    printf(GREEN "\n注册成功！" NONE);
    getchar();
    printf("\033[H\033[J");
    return 0;
}

bool loginUser(user* u) {
    printf("请输入ID: ");
    scanf("%s", u->id);
    while (getchar() != '\n' && getchar() != EOF)
        ;
    if (findUser(u->id) == -1) {
        printf(RED "该ID不存在！" NONE);
        getchar();
        printf("\033[H\033[J");
        return false;
    }

    printf("请输入密码: ");
    int i = 0;
    while (1) {
        u->password[i] = _getch();
        if (u->password[i] == '\r' || u->password[i] == '\n') {
            u->password[i] = '\0';
            break;
        }
        if (u->password[i] == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            i++;
        }
    }
    if (strcmp(users[findUser(u->id)].password, u->password) != 0) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf(RED "\n密码错误！" NONE);
        getchar();
        printf("\033[H\033[J");
        return false;
    }
    return true;
}

int passwordReset(user* u) {
    printf("请输入ID: ");
    scanf("%s", u->id);
    while (getchar() != '\n' && getchar() != EOF)
        ;
    if (findUser(u->id) == -1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf(RED "该ID不存在！" NONE);
        getchar();
        printf("\033[H\033[J");
        return -1;
    }
    printf("请输入旧密码: ");
    int i = 0;
    while (1) {
        u->password[i] = _getch();
        if (u->password[i] == '\r' || u->password[i] == '\n') {
            u->password[i] = '\0';
            break;
        }
        if (u->password[i] == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            i++;
        }
    }
    if (strcmp(users[findUser(u->id)].password, u->password) != 0) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf(RED "\n密码错误！" NONE);
        getchar();
        printf("\033[H\033[J");
        return -1;
    }
    while (1) {
        printf("\n请输入新密码(最小6个字符, 最大16个字符): ");
        int j = 0;
        while (1) {
            u->password[j] = _getch();
            if (u->password[j] == '\r' || u->password[j] == '\n') {
                u->password[j] = '\0';
                break;
            }
            if (u->password[j] == '\b') {
                if (j > 0) {
                    printf("\b \b");
                    j--;
                }
            } else {
                printf("*");
                j++;
            }
        }
        if (strlen(u->password) < MIN_PASS_LEN ||
            strlen(u->password) > MAX_PASS_LEN) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("密码长度必须在%d到%d个字符之间！", MIN_PASS_LEN,
                   MAX_PASS_LEN);
            memset(u->password, 0, MAX_PASS_LEN);
            getchar();
            printf("\033[H\033[J");
        } else {
            break;
        }
    }
    strcpy(users[findUser(u->id)].password, u->password);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    printf(GREEN "\n密码修改成功！" NONE);
    getchar();
    printf("\033[H\033[J");
    return 0;
}
