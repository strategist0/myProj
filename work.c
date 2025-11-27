#include <stdio.h>

int main() {
    int LOC, n, SIZE;
    printf("输入基地址 LOC: ");
    scanf("%d", &LOC);

    printf("输入数组维数 n: ");
    scanf("%d", &n);

    int c[10], d[10], j[10];
    for (int i = 0; i < n; i++) {
        printf("输入第 %d 维的下限和上限: ", i + 1);
        scanf("%d %d", &c[i], &d[i]);
        if (c[i] > d[i]) {
            printf("错误：第 %d 维上下限无效，应满足 c%d <= d%d。\n", i + 1,
                   i + 1, i + 1);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("输入第 %d 维下标 j%d: ", i + 1, i + 1);
        scanf("%d", &j[i]);
        if (j[i] < c[i] || j[i] > d[i]) {
            printf("错误：第 %d 维下标 j%d 越界，应在 [%d, %d] 之间。\n", i + 1,
                   i + 1, c[i], d[i]);
            return 1;
        }
    }

    printf("输入数据类型大小 SIZE: ");
    scanf("%d", &SIZE);

    int offset = 0;
    for (int i = 0; i < n; i++) {
        int product = 1;
        for (int k = i + 1; k < n; k++) {
            product *= (d[k] - c[k] + 1);
        }
        offset += (j[i] - c[i]) * product;
    }

    int ADD = LOC + offset * SIZE;
    printf("目标元素的地址 ADD = %d\n", ADD);

    return 0;
}
