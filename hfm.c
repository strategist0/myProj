#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HTNode {
    char ch;
    int weight;
    struct HTNode *left, *right;
} HTNode;

typedef struct {
    HTNode* root;
} HuffmanTree;

typedef struct {
    char ch;
    char code[100];
} CodeMap;

HTNode* newNode(char c, int w) {
    HTNode* p = (HTNode*)malloc(sizeof(HTNode));
    p->ch = c;
    p->weight = w;
    p->left = p->right = NULL;
    return p;
}

HTNode* extractMin(HTNode* a[], int* n) {
    int i, minIndex = 0;
    for (i = 1; i < *n; i++)
        if (a[i]->weight < a[minIndex]->weight)
            minIndex = i;
    HTNode* t = a[minIndex];
    a[minIndex] = a[*n - 1];
    (*n)--;
    return t;
}

HuffmanTree buildTree(char chs[], int w[], int n) {
    HTNode* heap[200];
    int i;
    for (i = 0; i < n; i++)
        heap[i] = newNode(chs[i], w[i]);
    int m = n;
    while (m > 1) {
        HTNode* a = extractMin(heap, &m);
        HTNode* b = extractMin(heap, &m);
        HTNode* p = newNode(0, a->weight + b->weight);
        p->left = a;
        p->right = b;
        heap[m++] = p;
    }
    HuffmanTree t;
    t.root = heap[0];
    return t;
}

void getCodes(HTNode* r, char* buf, int depth, CodeMap map[], int* idx) {
    if (!r)
        return;
    if (!r->left && !r->right) {
        buf[depth] = '\0';
        map[*idx].ch = r->ch;
        strcpy(map[*idx].code, buf);
        (*idx)++;
        return;
    }
    buf[depth] = '0';
    getCodes(r->left, buf, depth + 1, map, idx);
    buf[depth] = '1';
    getCodes(r->right, buf, depth + 1, map, idx);
}

char* findCode(char c, CodeMap map[], int n) {
    int i;
    for (i = 0; i < n; i++)
        if (map[i].ch == c)
            return map[i].code;
    return "";
}

int main() {
    int n, i;
    char chs[200];
    int w[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf(" %c", &chs[i]);
    for (i = 0; i < n; i++)
        scanf("%d", &w[i]);

    HuffmanTree T = buildTree(chs, w, n);

    CodeMap map[200];
    int idx = 0;
    char buf[200];
    getCodes(T.root, buf, 0, map, &idx);

    for (i = 0; i < n; i++)
        printf("%c: %s\n", map[i].ch, map[i].code);

    char s[1000];
    scanf("%s", s);

    printf("Encoded: ");
    for (i = 0; i < strlen(s); i++)
        printf("%s", findCode(s[i], map, n));
    printf("\n");

    return 0;
}
