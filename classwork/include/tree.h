#ifndef TREE_H
#define TREE_H

#define max(a, b) ((a) > (b) ? (a) : (b))
#define NAME_MAX 64

#ifndef TREE_DEFINED
#define TREE_DEFINED

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

#endif

int Balance_Factor(Node* node);
void Calc_Height(Node* node);
void InOrderTraversal(Node* root);
void DisplayAllBooks(Node* root);
Node* Init_Node(int value, Info* info);
Node* RRotate(Node* R);
Node* LRotate(Node* R);
Node* AVLRR(Node* rr);
Node* AVLLL(Node* ll);
Node* AVLLR(Node* lr);
Node* AVLRL(Node* rl);
Node* AVLBalance(Node* node);
Node* Add_Node(Node* root, int value, Info* info);
Node* Search_Node(Node* root, int value);
Node* Min_Value_Node(Node* node);
Node* Delete_Node_Without_Free(Node* root, int value);
Node* Delete_Node(Node* root, int value);

#endif