#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF 999999

typedef struct EdgeNode {
    int adjvex;
    struct EdgeNode* next;
} EdgeNode;

typedef struct VexNode {
    char data;
    EdgeNode* first;
} VexNode;

typedef struct {
    VexNode adjList[MAX_VERTICES];
    int vexNum;
    int arcNum;
} LGraph;

typedef struct {
    char vexs[MAX_VERTICES];
    int arc[MAX_VERTICES][MAX_VERTICES];
    int vexNum;
} MGraph;

int GetIndex(const LGraph* G, char v) {
    for (int i = 0; i < G->vexNum; ++i) {
        if (G->adjList[i].data == v) {
            return i;
        }
    }
    return -1;
}

void DestroyLGraph(LGraph* G) {
    for (int i = 0; i < G->vexNum; ++i) {
        EdgeNode* p = G->adjList[i].first;
        while (p) {
            EdgeNode* temp = p;
            p = p->next;
            free(temp);
        }
        G->adjList[i].first = NULL;
    }
}

void CreateLGraph(LGraph* G,
                  int n,
                  const char vexs[],
                  int numEdges,
                  const int edges[][2]) {
    G->vexNum = n;
    G->arcNum = numEdges;

    for (int i = 0; i < n; ++i) {
        G->adjList[i].data = vexs[i];
        G->adjList[i].first = NULL;
    }

    for (int k = 0; k < numEdges; ++k) {
        int i = edges[k][0];
        int j = edges[k][1];

        EdgeNode* newNode_j = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (newNode_j == NULL)
            return;
        newNode_j->adjvex = j;
        newNode_j->next = G->adjList[i].first;
        G->adjList[i].first = newNode_j;

        EdgeNode* newNode_i = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (newNode_i == NULL)
            return;
        newNode_i->adjvex = i;
        newNode_i->next = G->adjList[j].first;
        G->adjList[j].first = newNode_i;
    }
}

void CreateMGraph(MGraph* G,
                  int n,
                  const char vexs[],
                  int numEdges,
                  const int edges[][2]) {
    G->vexNum = n;

    for (int i = 0; i < n; ++i) {
        G->vexs[i] = vexs[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            G->arc[i][j] = 0;
        }
    }

    for (int k = 0; k < numEdges; ++k) {
        int i = edges[k][0];
        int j = edges[k][1];
        G->arc[i][j] = 1;
        G->arc[j][i] = 1;
    }
}

void DFS(const LGraph* G, int v, bool visited[]) {
    visited[v] = true;
    printf("%c ", G->adjList[v].data);

    EdgeNode* p = G->adjList[v].first;
    while (p) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w, visited);
        }
        p = p->next;
    }
}

void DFSTraverse(const LGraph* G) {
    printf("  深度优先搜索(DFS)结果: ");
    bool visited[MAX_VERTICES] = {false};

    for (int i = 0; i < G->vexNum; ++i) {
        if (!visited[i]) {
            DFS(G, i, visited);
        }
    }
    printf("\n");
}

void BFSTraverse(const LGraph* G) {
    printf("  广度优先搜索(BFS)结果: ");
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    for (int i = 0; i < G->vexNum; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            printf("%c ", G->adjList[i].data);
            queue[rear++] = i;
            while (front != rear) {
                int v = queue[front++];

                EdgeNode* p = G->adjList[v].first;
                while (p) {
                    int w = p->adjvex;
                    if (!visited[w]) {
                        visited[w] = true;
                        printf("%c ", G->adjList[w].data);
                        queue[rear++] = w;
                    }
                    p = p->next;
                }
            }
        }
    }
    printf("\n");
}

int GetConnectedComponents(const LGraph* G) {
    printf("【3. 连通性判断及连通分量】\n");
    bool visited[MAX_VERTICES] = {false};
    int count = 0;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    for (int i = 0; i < G->vexNum; ++i) {
        if (!visited[i]) {
            count++;
            printf("  连通分量 %d: { ", count);

            visited[i] = true;
            printf("%c", G->adjList[i].data);
            queue[rear++] = i;

            while (front != rear) {
                int v = queue[front++];

                EdgeNode* p = G->adjList[v].first;
                while (p) {
                    int w = p->adjvex;
                    if (!visited[w]) {
                        visited[w] = true;
                        printf(", %c", G->adjList[w].data);
                        queue[rear++] = w;
                    }
                    p = p->next;
                }
            }

            front = rear = 0;
            printf(" }\n");
        }
    }

    if (count == 1) {
        printf("  -> **结论**: 图是连通图。\n");
    } else {
        printf("  -> **结论**: 图是非连通图，共有 %d 个连通分量。\n", count);
    }
    return count;
}

bool FindSimplePathUtil(const LGraph* G,
                        int v,
                        int u,
                        bool visited[],
                        int pathStack[],
                        int* pathTop) {
    visited[v] = true;
    pathStack[(*pathTop)++] = v;

    if (v == u) {
        return true;
    }

    EdgeNode* p = G->adjList[v].first;
    while (p) {
        int w = p->adjvex;
        if (!visited[w]) {
            if (FindSimplePathUtil(G, w, u, visited, pathStack, pathTop)) {
                return true;
            }
        }
        p = p->next;
    }

    (*pathTop)--;
    visited[v] = false;
    return false;
}

void FindSimplePath(const LGraph* G, char startVex, char endVex) {
    printf("【4. 查找简单路径: %c 到 %c】\n", startVex, endVex);
    int startIndex = GetIndex(G, startVex);
    int endIndex = GetIndex(G, endVex);

    if (startIndex == -1 || endIndex == -1) {
        printf("  顶点不存在。\n");
        return;
    }

    bool visited[MAX_VERTICES] = {false};
    int pathStack[MAX_VERTICES];
    int pathTop = 0;

    if (FindSimplePathUtil(G, startIndex, endIndex, visited, pathStack,
                           &pathTop)) {
        printf("  找到简单路径: ");
        for (int i = 0; i < pathTop; ++i) {
            printf("%c", G->adjList[pathStack[i]].data);
            if (i < pathTop - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("  不存在从 %c 到 %c 的简单路径。\n", startVex, endVex);
    }
}

void PrintDegrees(const LGraph* G) {
    printf("【5. 打印图的各顶点的度】\n");
    for (int i = 0; i < G->vexNum; ++i) {
        int degree = 0;
        EdgeNode* p = G->adjList[i].first;
        while (p) {
            degree++;
            p = p->next;
        }
        printf("  顶点 %c 的度为: %d\n", G->adjList[i].data, degree);
    }
}

int main() {
    const int VEX_COUNT = 4;
    const char vexs[] = {'A', 'B', 'C', 'D', 'E'};

    const int EDGES_COUNT = 1;
    const int edges[1][2] = {
        {0, 1},  // A-B
    };

    LGraph lGraph;
    MGraph mGraph;

    printf("============================================\n");
    printf("         实验6: 图的遍历及简单应用 (C语言)    \n");
    printf("============================================\n");
    printf("顶点集合: {A, B, C, D}, 边集合: {(A,B)}\n");

    printf("\n【1. 创建图】\n");

    CreateMGraph(&mGraph, VEX_COUNT, vexs, EDGES_COUNT, edges);
    printf("  -> 邻接矩阵表示图已创建 (mGraph)。\n");

    CreateLGraph(&lGraph, VEX_COUNT, vexs, EDGES_COUNT, edges);
    printf("  -> 邻接表表示图已创建 (lGraph)。\n");
    printf("--------------------------------------------\n");

    printf("【2. 图的深度和广度优先搜索结果】\n");
    DFSTraverse(&lGraph);
    BFSTraverse(&lGraph);
    printf("--------------------------------------------\n");

    GetConnectedComponents(&lGraph);
    printf("--------------------------------------------\n");

    FindSimplePath(&lGraph, 'A', 'B');

    FindSimplePath(&lGraph, 'C', 'D');
    printf("--------------------------------------------\n");

    PrintDegrees(&lGraph);
    printf("============================================\n");

    DestroyLGraph(&lGraph);

    getchar();

    return 0;
}