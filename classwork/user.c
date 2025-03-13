#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define NAME_MAX 64

#define MAX_NAME_LEN 32
#define MAX_PASS_LEN 16
#define MIN_PASS_LEN 6
#define MAX_USERS 10
#define NONE "\033[0m"
#define GREEN "\033[0;32;32m"
#define YELLOW "\033[0;33;33m"
#define BLUE "\033[0;34;34m"
#define RED "\033[0;32;31m"

typedef struct User {
    char id[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    struct TreeNode* library;
} user;

typedef struct LibInfo {
    char name[NAME_MAX];
    char author[NAME_MAX];
    int num;
    char date[12];
} Info;

typedef struct TreeNode {
    int value;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
    Info* info;
} Node;

Node* Init_Node(int value, Info* info) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->info = (Info*)malloc(sizeof(Info));
    if (node == NULL || node->info == NULL) {
        perror("malloc failed");
        return NULL;
    }
    if (node == NULL) {
        perror("malloc failed");
        return NULL;
    }
    memcpy(node->info, info, sizeof(Info));

    node->height = 1;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->info = info;
    return node;
}

void Calc_Height(Node* node) {
    if (node == NULL)
        return;
    int left_height = (node->left) ? node->left->height : 0;
    int right_height = (node->right) ? node->right->height : 0;
    node->height = 1 + max(left_height, right_height);
}

int Balance_Factor(Node* node) {
    if (node == NULL)
        return 0;
    int left = node->left ? node->left->height : 0;
    int right = node->right ? node->right->height : 0;
    return left - right;
}

Node* RRotate(Node* R) {
    if (R == NULL || R->left == NULL) {
        return R;
    }

    Node* Lnode = R->left;
    R->left = Lnode->right;

    if (Lnode->right != NULL) {
        Lnode->right->parent = R;
    }

    Lnode->right = R;
    Lnode->parent = R->parent;
    R->parent = Lnode;

    if (Lnode->parent != NULL) {
        if (Lnode->parent->left == R) {
            Lnode->parent->left = Lnode;
        } else {
            Lnode->parent->right = Lnode;
        }
    }

    Calc_Height(R);
    Calc_Height(Lnode);

    return Lnode;
}

Node* LRotate(Node* R) {
    if (R == NULL || R->right == NULL) {
        return R;
    }

    Node* Rnode = R->right;

    R->right = Rnode->left;
    if (Rnode->left != NULL) {
        Rnode->left->parent = R;
    }

    Rnode->left = R;
    Rnode->parent = R->parent;
    R->parent = Rnode;

    if (Rnode->parent != NULL) {
        if (Rnode->parent->left == R) {
            Rnode->parent->left = Rnode;
        } else {
            Rnode->parent->right = Rnode;
        }
    }

    Calc_Height(R);

    Calc_Height(Rnode);

    return Rnode;
}

Node* AVLRR(Node* rr) {
    return LRotate(rr);
}

Node* AVLLL(Node* ll) {
    return RRotate(ll);
}

Node* AVLLR(Node* lr) {
    lr->left = LRotate(lr->left);
    return RRotate(lr);
}

Node* AVLRL(Node* rl) {
    rl->right = RRotate(rl->right);
    return LRotate(rl);
}

Node* AVLBalance(Node* node) {
    if (node == NULL)
        return NULL;

    int bf = Balance_Factor(node);

    if (bf > 1) {
        if (node->left != NULL) {
            int left_bf = Balance_Factor(node->left);
            if (left_bf >= 0) {
                node = RRotate(node);
            } else {
                node->left = LRotate(node->left);
                node = RRotate(node);
            }
        }
    }

    else if (bf < -1) {
        if (node->right != NULL) {
            int right_bf = Balance_Factor(node->right);
            if (right_bf <= 0) {
                node = LRotate(node);
            } else {
                node->right = RRotate(node->right);
                node = LRotate(node);
            }
        }
    }

    Calc_Height(node);
    return node;
}

Node* Add_Node(Node* root, int value, Info* info) {
    if (info == NULL) {
        fprintf(stderr, RED "错误：书籍信息指针不能为NULL！\n" NONE);
        return root;
    }

    if (root == NULL) {
        Node* new_node = Init_Node(value, info);
        if (new_node == NULL) {
            fprintf(stderr, RED "错误：内存分配失败！\n" NONE);
        }
        return new_node;
    }

    if (value < root->value) {
        Node* new_left = Add_Node(root->left, value, info);
        if (new_left == NULL)
            return root;
        root->left = new_left;
        new_left->parent = root;
    } else if (value > root->value) {
        Node* new_right = Add_Node(root->right, value, info);
        if (new_right == NULL)
            return root;
        root->right = new_right;
        new_right->parent = root;
    } else {
        fprintf(stderr, RED "错误：书籍ID %04d 已存在，禁止重复添加！\n" NONE,
                value);
        return root;
    }

    Calc_Height(root);
    return AVLBalance(root);
}

Node* Search_Node(Node* root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value) {
        return Search_Node(root->left, value);
    } else {
        return Search_Node(root->right, value);
    }
}

Node* Min_Value_Node(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* Delete_Node_Without_Free(Node* root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->value) {
        root->left = Delete_Node_Without_Free(root->left, value);
        if (root->left)
            root->left->parent = root;
    } else if (value > root->value) {
        root->right = Delete_Node_Without_Free(root->right, value);
        if (root->right)
            root->right->parent = root;
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                free(root);
                return NULL;
            } else {
                root->value = temp->value;
                root->info = temp->info;
                root->left = temp->left;
                root->right = temp->right;

                if (root->left)
                    root->left->parent = root;
                if (root->right)
                    root->right->parent = root;

                free(temp);
            }
        } else {
            Node* successor = Min_Value_Node(root->right);
            root->value = successor->value;
            root->info = successor->info;
            root->right =
                Delete_Node_Without_Free(root->right, successor->value);
        }
    }

    Calc_Height(root);
    return AVLBalance(root);
}

Node* Delete_Node(Node* root, int value) {
    if (root == NULL) {
        printf(RED "错误：未找到书籍ID %04d\n" NONE, value);
        return NULL;
    }

    if (value < root->value) {
        root->left = Delete_Node(root->left, value);
        if (root->left)
            root->left->parent = root;
    } else if (value > root->value) {
        root->right = Delete_Node(root->right, value);
        if (root->right)
            root->right->parent = root;
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                free(root->info);
                free(root);
                return NULL;
            } else {
                free(root->info);  // 释放当前节点信息
                root->value = temp->value;
                root->info = temp->info;  // 接管子节点信息
                root->left = temp->left;
                root->right = temp->right;

                if (root->left)
                    root->left->parent = root;
                if (root->right)
                    root->right->parent = root;

                free(temp);
            }
        } else {
            Node* successor = Min_Value_Node(root->right);
            free(root->info);  // 释放当前节点信息
            root->value = successor->value;
            root->info = successor->info;  // 接管后继节点信息
            root->right =
                Delete_Node_Without_Free(root->right, successor->value);
        }
    }

    Calc_Height(root);
    return AVLBalance(root);
}

void InOrderTraversal(Node* root) {
    if (root == NULL)
        return;

    InOrderTraversal(root->left);

    printf(BLUE "┌───────────────────────────────────────┐\n" NONE);
    printf("│ 编号: %-34d │\n", root->value);
    printf("│ 书名: %-34s │\n", root->info->name);
    printf("│ 作者: %-34s │\n", root->info->author);
    printf("│ 数量: %-34d │\n", root->info->num);
    printf("│ 日期: %-34s │\n", root->info->date);
    printf(BLUE "└───────────────────────────────────────┘\n" NONE);

    InOrderTraversal(root->right);
}

void DisplayAllBooks(Node* root) {
    if (root == NULL) {
        printf(YELLOW "当前没有藏书信息！\n" NONE);
        return;
    }
    printf(GREEN "\n══════════════ 藏书清单 ══════════════\n" NONE);
    InOrderTraversal(root);
    printf(GREEN "═══════════════════════════════════════\n\n" NONE);
}

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