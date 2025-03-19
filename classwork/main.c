#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admini.h"
#include "menu.h"
#include "tree.h"
#include "user.h"

int main() {
    user users[MAX_USERS] = {0};
    int usercount = 0;
    user* currUser = NULL;
    GetUsers("f:\\VScode\\myProj\\classwork\\users.txt", users, &usercount);
    int choice;
ad:
    displayMenu1();
    while (1) {
        choice = 0;
        scanf("%d", &choice);
        while (getchar() != '\n' && getchar() != EOF)
            ;
        system("cls");
        switch (choice) {
            case 1:
                user u;
                registerUser(&u, &usercount, users);
                goto ad;
                break;
            case 2: {
                user temp;
                if (loginUser(&temp)) {
                    int index =
                        findUser(temp.id, users, usercount,
                                 "f:\\VScode\\myProj\\classwork\\users.txt");
                    if (index == -1) {
                        printf(RED "用户不存在！\n" NONE);
                        goto ad;
                    }
                    currUser = &users[index];
                    if (currUser == NULL) {
                        printf(RED "用户不存在！\n" NONE);
                        goto ad;
                    }
                    system("cls");
                    printf("欢迎！%s\n", currUser->id);
                    Node** root = &(currUser->library);
                    int choice1;
                    while (1) {
                        displayMenu();
                        choice1 = 0;
                        scanf("%d", &choice1);
                        while (getchar() != '\n')
                            ;
                        system("cls");
                        switch (choice1) {
                            case 1: {
                                // 添加图书
                                Info* newInfo = (Info*)malloc(sizeof(Info));
                                if (newInfo == NULL) {
                                    perror("malloc failed");
                                    break;
                                }
                                printf("请输入图书信息\n");
                                printf("书名: ");
                                scanf("%s", newInfo->name);
                                while (getchar() != '\n')
                                    ;
                                printf("作者: ");
                                scanf("%s", newInfo->author);
                                while (getchar() != '\n')
                                    ;
                                printf("数量: ");
                                scanf("%d", &newInfo->num);
                                while (getchar() != '\n')
                                    ;
                                printf("日期: ");
                                scanf("%s", newInfo->date);
                                while (getchar() != '\n')
                                    ;
                                int value;
                                printf("请输入图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n')
                                    ;
                                *root = Add_Node(*root, value, newInfo);
                                break;
                            }
                            case 2: {
                                // 删除图书
                                int value;
                                printf("请输入要删除的图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n')
                                    ;
                                Node* node = Search_Node(*root, value);
                                if (node != NULL) {
                                    *root = Delete_Node(
                                        *root,
                                        value);  // 删除节点时，Delete_Node
                                                 // 已处理内存释放
                                    printf(GREEN "图书删除成功！\n" NONE);
                                } else {
                                    printf(RED
                                           "错误：未找到图书编号 %04d！\n" NONE,
                                           value);
                                }
                                break;
                            }
                            case 3: {
                                // 修改图书信息
                                int value;
                                printf("请输入要修改的图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n')
                                    ;
                                Node* node = Search_Node(*root, value);
                                if (node == NULL) {
                                    printf(RED "未找到该图书！\n" NONE);
                                } else {
                                    printf("当前图书信息:\n");
                                    printf("书名: %s\n", node->info->name);
                                    printf("作者: %s\n", node->info->author);
                                    printf("数量: %d\n", node->info->num);
                                    printf("日期: %s\n", node->info->date);
                                    printf("请输入新的图书信息\n");
                                    printf("书名: ");
                                    scanf("%s", node->info->name);
                                    while (getchar() != '\n')
                                        ;
                                    printf("作者: ");
                                    scanf("%s", node->info->author);
                                    while (getchar() != '\n')
                                        ;
                                    printf("数量: ");
                                    scanf("%d", &node->info->num);
                                    while (getchar() != '\n')
                                        ;
                                    printf("日期: ");
                                    scanf("%s", node->info->date);
                                    while (getchar() != '\n')
                                        ;
                                    printf(GREEN "图书信息修改成功！\n" NONE);
                                }
                                break;
                            }
                            case 4: {
                                // 查找图书
                                int value;
                                printf("请输入要查找的图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n')
                                    ;
                                Node* node = Search_Node(*root, value);
                                if (node == NULL) {
                                    printf(RED "未找到该图书！\n" NONE);
                                } else {
                                    printf("图书信息:\n");
                                    printf("书名: %s\n", node->info->name);
                                    printf("作者: %s\n", node->info->author);
                                    printf("数量: %d\n", node->info->num);
                                    printf("日期: %s\n", node->info->date);
                                }
                                break;
                            }
                            case 5: {
                                // 显示所有图书
                                DisplayAllBooks(*root);
                                break;
                            }
                            case 6: {
                                // 退出系统
                                currUser = NULL;
                                system("cls");
                                goto ad;
                                break;
                            }
                                system("cls");
                                goto ad;
                                break;
                            default: {
                                printf(RED "输入错误，请重新输入!\n" NONE);
                                break;
                            }
                        }
                        printf("\n按任意键继续...");
                        getchar();
                        system("cls");
                    }
                } else {
                    goto ad;
                }
                break;
            }
            case 3:
                passwordReset(&users[usercount]);
                goto ad;
            case 4:
                int choice2;
                if (AdminiManage() == false) {
                    goto ad;
                }
            cd:
                system("cls");
                AdminiMenu();
                choice2 = 0;
                scanf("%d", &choice2);
                while (getchar() != '\n' && getchar() != EOF)
                    ;
                system("cls");
                switch (choice2) {
                    case 1:
                        SortUsers();
                        goto cd;
                    case 2:
                        AdmPswReset();
                        goto ad;
                        break;
                    case 3:
                        UserPswReset();
                        goto cd;
                    case 4:
                        DisplayAllUsersBooks(users, &usercount);
                        goto cd;
                    case 5:
                        goto ad;
                    default:
                        printf(RED "输入错误，请重新输入!\n" NONE);
                        getchar();
                        system("cls");
                        goto ad;
                }
            case 5:
                exit(0);
            default:
                printf(RED "输入错误，请重新输入!\n" NONE);
                getchar();
                system("cls");
                goto ad;
        }
    }
    return 0;
}