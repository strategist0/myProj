#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "tree.h"
#include "user.h"

int main() {
    user users[MAX_USERS] = {0};
    user* currUser = NULL;
    int choice;
ad:
    displayMenu1();
    while (1) {
        scanf("%d", &choice);
        while (getchar() != '\n' && getchar() != EOF)
            ;
        printf("\033[H\033[J");
        switch (choice) {
            case 1:
                registerUser(&users[usercount]);

                goto ad;
            case 2: {
                user temp;
                if (loginUser(&temp)) {
                    int idx = findUser(temp.id);
                    currUser = &users[idx];
                    printf("\033[H\033[J");
                    printf("欢迎！%s\n", currUser->id);
                    Node** root = &(currUser->library);
                    int choice1;
                bd:
                    system("cls");
                    displayMenu();
                    while (1) {
                        scanf("%d", &choice1);
                        while (getchar() != '\n' && getchar() != EOF)
                            ;
                        printf("\033[H\033[J");
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
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                printf("作者: ");
                                scanf("%s", newInfo->author);
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                printf("数量: ");
                                scanf("%d", &newInfo->num);
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                printf("日期: ");
                                scanf("%s", newInfo->date);
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                int value;
                                printf("请输入图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                *root = Add_Node(*root, value, newInfo);
                                break;
                            }
                            case 2: {
                                // 删除图书
                                int value;
                                printf("请输入要删除的图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n' && getchar() != EOF)
                                    ;
                                *root = Delete_Node(*root, value);
                                printf(GREEN "图书删除成功！\n" NONE);
                                break;
                            }
                            case 3: {
                                // 修改图书信息
                                int value;
                                printf("请输入要修改的图书编号: ");
                                scanf("%d", &value);
                                while (getchar() != '\n' && getchar() != EOF)
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
                                    while (getchar() != '\n' &&
                                           getchar() != EOF)
                                        ;
                                    printf("作者: ");
                                    scanf("%s", node->info->author);
                                    while (getchar() != '\n' &&
                                           getchar() != EOF)
                                        ;
                                    printf("数量: ");
                                    scanf("%d", &node->info->num);
                                    while (getchar() != '\n' &&
                                           getchar() != EOF)
                                        ;
                                    printf("日期: ");
                                    scanf("%s", node->info->date);
                                    while (getchar() != '\n' &&
                                           getchar() != EOF)
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
                                while (getchar() != '\n' && getchar() != EOF)
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
                                printf("\033[H\033[J");
                                goto ad;
                                break;
                            }
                            default: {
                                printf(RED "输入错误，请重新输入!\n" NONE);
                                getchar();
                                printf("\033[H\033[J");
                                goto bd;
                            }
                        }
                        printf("\n按任意键继续...");
                        getchar();
                        printf("\033[H\033[J");
                        goto bd;
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
                exit(0);
            default:
                printf(RED "输入错误，请重新输入!\n" NONE);
                getchar();
                printf("\033[H\033[J");
                goto ad;
        }
    }
    return 0;
}