#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define NAME_MAX 64

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