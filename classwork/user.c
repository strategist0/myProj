#include "user.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "tree.h"

user users[MAX_USERS] = {0};

int findUser(const char* username,
             user* usersArray,
             int userCount,
             const char* filename) {
    // 在内存中搜索
    for (int i = 0; i < userCount; i++) {
        if (strcmp(usersArray[i].id, username) == 0) {
            return i;  // 返回找到的用户索引
        }
    }

    // 在文件中搜索
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件！" NONE);
        return -1;
    }

    char file_id[MAX_NAME_LEN + 1], file_password[MAX_PASS_LEN + 1];
    int i = 0;
    while (fscanf(file, "%s %s", file_id, file_password) != EOF) {
        i++;
        if (strcmp(file_id, username) == 0) {
            fclose(file);
            return i;  // 返回 -2 表示用户在文件中，但不在内存中
        }
    }
    fclose(file);

    return -1;  // 未找到用户
}

void saveUsersToFile(const char* filename, user* users, int usercount) {
    FILE* file = fopen(filename, "w");  // 使用 "w" 模式覆盖文件内容
    if (file == NULL) {
        printf(RED "无法打开文件保存用户信息！" NONE);
        return;
    }
    for (int i = 0; i < usercount; i++) {  // 修正循环条件，避免重复写入
        fprintf(file, "%s %s\n", users[i].id, users[i].password);
    }
    fclose(file);
    printf(GREEN "用户信息已保存到文件！" NONE);
}

int registerUser(user* u, int* usercount, user* users) {
    if ((*usercount) >= MAX_USERS) {
        printf(RED "用户数量已达上限！" NONE);
        getchar();
        system("cls");
        return -1;
    }

    while (1) {
        printf("请输入ID(最大32个字符): ");
        scanf_s("%s", u->id, MAX_NAME_LEN);
        while (getchar() != '\n' && getchar() != EOF)
            ;
        system("cls");
        if (findUser(u->id, users, (*usercount),
                     "f:\\VScode\\myProj\\classwork\\users.txt") != -1) {
            printf(RED "该ID已被注册！" NONE);
            getchar();
            system("cls");
            continue;
        }

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
            printf(YELLOW "\n密码长度必须在%d到%d个字符之间！" NONE,
                   MIN_PASS_LEN, MAX_PASS_LEN);
            memset(u->password, 0, MAX_PASS_LEN);
            getchar();
            system("cls");
            continue;
        }

        printf("\n请确认以下信息：\n");
        printf("用户ID：%s\n", u->id);
        printf("密码：%s\n", u->password);
        printf("确认无误请输入 Y/y，否则输入 N/n: ");
        char confirm;
        scanf(" %c", &confirm);

        // 清空输入缓冲区
        while (getchar() != '\n' && getchar() != EOF)
            ;

        if (confirm == 'Y' || confirm == 'y') {
            break;
        } else {
            system("cls");
        }
    }

    strcpy(users[(*usercount)].password, u->password);
    strcpy(users[(*usercount)].id, u->id);
    (*usercount)++;
    printf(GREEN "\n注册成功！" NONE);
    saveUsersToFile("f:\\VScode\\myProj\\classwork\\users.txt", users,
                    *usercount);  // 保存用户信息到文件
    getchar();
    system("cls");
    return 0;
}

bool loginUser(user* u) {
    printf("请输入ID: ");
    scanf("%s", u->id);

    // 清空输入缓冲区
    while (getchar() != '\n' && getchar() != EOF)
        ;

    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "r");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件！" NONE);
        getchar();
        system("cls");
        return false;
    }

    char file_id[33], file_password[17];
    bool user_found = false;
    while (fscanf(file, "%s %s", file_id, file_password) != EOF) {
        if (strcmp(file_id, u->id) == 0) {
            user_found = true;
            break;
        }
    }
    fclose(file);

    if (!user_found) {
        printf(RED "该ID不存在！" NONE);
        getchar();
        system("cls");
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

    if (strcmp(file_password, u->password) != 0) {
        printf(RED "\n密码错误！" NONE);
        getchar();
        system("cls");
        return false;
    }

    return true;
}

int passwordReset(user* u) {
    printf("请输入ID: ");
    scanf("%s", u->id);
    while (getchar() != '\n' && getchar() != EOF)
        ;

    FILE* file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "r");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件！" NONE);
        getchar();
        system("cls");
        return -1;
    }

    user temp_users[MAX_USERS];
    int temp_usercount = 0;
    bool user_found = false;

    // 读取用户信息到内存
    while (fscanf(file, "%s %s", temp_users[temp_usercount].id,
                  temp_users[temp_usercount].password) != EOF) {
        if (strcmp(temp_users[temp_usercount].id, u->id) == 0) {
            user_found = true;
        }
        temp_usercount++;
    }
    fclose(file);

    if (!user_found) {
        printf(RED "该ID不存在！" NONE);
        getchar();
        system("cls");
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

    for (int j = 0; j < temp_usercount; j++) {
        if (strcmp(temp_users[j].id, u->id) == 0) {
            if (strcmp(temp_users[j].password, u->password) != 0) {
                printf(RED "\n密码错误！" NONE);
                getchar();
                system("cls");
                return -1;
            }

            while (true) {
                printf("\n请输入新密码(最小6个字符, 最大16个字符): ");
                int k = 0;
                while (1) {
                    u->password[k] = _getch();
                    if (u->password[k] == '\r' || u->password[k] == '\n') {
                        u->password[k] = '\0';
                        break;
                    }
                    if (u->password[k] == '\b') {
                        if (k > 0) {
                            printf("\b \b");
                            k--;
                        }
                    } else {
                        printf("*");
                        k++;
                    }
                }
                if (strlen(u->password) < MIN_PASS_LEN ||
                    strlen(u->password) > MAX_PASS_LEN) {
                    printf(YELLOW "\n密码长度必须在%d到%d个字符之间！" NONE,
                           MIN_PASS_LEN, MAX_PASS_LEN);
                    memset(u->password, 0, MAX_PASS_LEN);
                    getchar();
                    system("cls");
                } else {
                    break;
                }
            }

            strcpy(temp_users[j].password, u->password);
            break;
        }
    }

    // 将修改后的用户信息写回文件
    file = fopen("f:\\VScode\\myProj\\classwork\\users.txt", "w");
    if (file == NULL) {
        printf(RED "无法打开用户信息文件以保存更改！" NONE);
        getchar();
        system("cls");
        return -1;
    }

    for (int j = 0; j < temp_usercount; j++) {
        fprintf(file, "%s %s\n", temp_users[j].id, temp_users[j].password);
    }
    fclose(file);

    printf(GREEN "\n密码修改成功！" NONE);
    getchar();
    system("cls");
    return 0;
}

int GetUsers(const char* filename, user* usersArray, int* usercount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开用户信息文件：%s\n", filename);
        return -1;  // 返回 -1 表示文件打开失败
    }

    *usercount = 0;  // 重置用户计数
    while (fscanf(file, "%s %s", usersArray[*usercount].id,
                  usersArray[*usercount].password) != EOF) {
        (*usercount)++;
        if (*usercount >= MAX_USERS) {
            printf("用户数量已达到最大限制：%d\n", MAX_USERS);
            break;
        }
    }
    fclose(file);

    return 0;  // 返回 0 表示成功
}