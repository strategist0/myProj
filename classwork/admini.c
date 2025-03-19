#include "admini.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "user.h"

bool AdminiManage() {
    admini adm;
    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\admini.txt", "r");
    if (file == NULL) {
        printf(RED "无法打开管理员信息文件！" NONE);
        getchar();
        system("cls");
        return false;
    }

    if (fscanf(file, "%s %s", adm.id, adm.password) == EOF) {
        printf(RED "管理员信息文件为空！" NONE);
        getchar();
        system("cls");
        return false;
    }
    fclose(file);

    printf("请输入管理员ID: ");
    char id[33], password[17];
    scanf("%s", id);
    while (getchar() != '\n' && getchar() != EOF)
        ;
    if (strcmp(id, adm.id) != 0) {
        printf(RED "\n管理员ID错误！" NONE);
        getchar();
        system("cls");
        return false;
    }

    printf("请输入密码: ");
    int i = 0;
    while (1) {
        password[i] = _getch();
        if (password[i] == '\r' || password[i] == '\n') {
            password[i] = '\0';
            break;
        }
        if (password[i] == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            i++;
        }
    }

    if (strcmp(password, adm.password) != 0) {
        printf(RED "\n密码错误！" NONE);
        getchar();
        system("cls");
        return false;
    }

    return true;
}

void SortUsers() {
    char id[MAX_USERS][MAX_NAME_LEN + 1], pswd[MAX_USERS][MAX_PASS_LEN + 1];
    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "r");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件！" NONE);
        getchar();
        system("cls");
        return;
    }

    int i = 0;
    while (i < MAX_USERS) {  // 添加边界检查
        if (fscanf(file, "%s %s", id[i], pswd[i]) == EOF)
            break;
        i++;
    }
    fclose(file);  // 文件读取完成后再关闭

    for (int j = 0; j < i; j++) {
        for (int k = j + 1; k < i; k++) {
            if (strcmp(id[j], id[k]) > 0) {
                char temp[MAX_NAME_LEN + 1];
                strcpy(temp, id[j]);
                strcpy(id[j], id[k]);
                strcpy(id[k], temp);

                strcpy(temp, pswd[j]);
                strcpy(pswd[j], pswd[k]);
                strcpy(pswd[k], temp);
            }
        }
    }

    for (int j = 0; j < i; j++) {
        printf("ID: %s, 密码: %s\n", id[j], pswd[j]);
    }

    printf(GREEN "全部用户信息（已排序）" NONE);
    getchar();
    system("cls");
}

bool AdmPswReset() {
    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\admini.txt", "r");
    if (file == NULL) {
        perror("无法打开管理员信息文件");
        return false;
    }

    admini tmpadm;
    if (fscanf(file, "%s %s", tmpadm.id, tmpadm.password) == EOF) {
        printf(RED "管理员信息文件为空！" NONE);
        fclose(file);
        return false;
    }
    fclose(file);

    char password[17];
    getPassword(password, "请输入旧密码: ");
    if (strcmp(tmpadm.password, password) != 0) {
        printf(RED "密码错误！" NONE);
        getchar();
        system("cls");
        return false;
    }

    getPassword(password, "请输入新密码: ");
    FILE* tempFile =
        fopen("f:\\VScode\\myProj\\classwork\\admini_temp.txt", "w");
    if (tempFile == NULL) {
        perror("无法创建临时文件");
        return false;
    }

    fprintf(tempFile, "%s %s", tmpadm.id, password);
    fclose(tempFile);

    if (remove("f:\\VScode\\myProj\\classwork\\admini.txt") != 0 ||
        rename("f:\\VScode\\myProj\\classwork\\admini_temp.txt",
               "f:\\VScode\\myProj\\classwork\\admini.txt") != 0) {
        perror("无法替换管理员信息文件");
        return false;
    }

    printf(GREEN "密码重置成功！" NONE);
    return true;
}

void getPassword(char* password, const char* prompt) {
    printf("%s", prompt);
    int i = 0;
    while (1) {
        password[i] = _getch();
        if (password[i] == '\r' || password[i] == '\n') {
            password[i] = '\0';
            break;
        }
        if (password[i] == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            i++;
        }
    }
    printf("\n");
}

void UserPswReset() {
    char userId[MAX_NAME_LEN + 1];
    char newPassword[MAX_PASS_LEN + 1];

    printf("请输入需要重置密码的用户ID: ");
    scanf("%s", userId);
    while (getchar() != '\n' && getchar() != EOF)
        ;

    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "r");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件！" NONE);
        getchar();
        system("cls");
        return;
    }

    user temp_users[MAX_USERS];
    int temp_usercount = 0;
    bool user_found = false;

    // 读取用户信息到内存
    while (fscanf(file, "%s %s", temp_users[temp_usercount].id,
                  temp_users[temp_usercount].password) != EOF) {
        if (strcmp(temp_users[temp_usercount].id, userId) == 0) {
            user_found = true;
        }
        temp_usercount++;
    }
    fclose(file);

    if (!user_found) {
        printf(RED "该ID不存在！" NONE);
        getchar();
        system("cls");
        return;
    }

    // 输入新密码
    while (true) {
        printf("\n请输入新密码(最小6个字符, 最大16个字符): ");
        int i = 0;
        while (1) {
            newPassword[i] = _getch();
            if (newPassword[i] == '\r' || newPassword[i] == '\n') {
                newPassword[i] = '\0';
                break;
            }
            if (newPassword[i] == '\b') {
                if (i > 0) {
                    printf("\b \b");
                    i--;
                }
            } else {
                printf("*");
                i++;
            }
        }
        if (strlen(newPassword) < MIN_PASS_LEN ||
            strlen(newPassword) > MAX_PASS_LEN) {
            printf(YELLOW "\n密码长度必须在%d到%d个字符之间！" NONE,
                   MIN_PASS_LEN, MAX_PASS_LEN);
            memset(newPassword, 0, MAX_PASS_LEN);
            getchar();
            system("cls");
        } else {
            break;
        }
    }

    // 更新用户密码
    for (int j = 0; j < temp_usercount; j++) {
        if (strcmp(temp_users[j].id, userId) == 0) {
            strcpy(temp_users[j].password, newPassword);
            break;
        }
    }

    // 将修改后的用户信息写回文件
    file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "w");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件以保存更改！" NONE);
        getchar();
        system("cls");
        return;
    }

    for (int j = 0; j < temp_usercount; j++) {
        fprintf(file, "%s %s\n", temp_users[j].id, temp_users[j].password);
    }
    fclose(file);

    printf(GREEN "\n密码重置成功！" NONE);
    getchar();
    system("cls");
}