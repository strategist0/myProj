#include <stdio.h>
#include <stdlib.h>
int main() {
    float x, y, z, sum;
    scanf("%f %f %f", &x, &y, &z);
    sum = x + y + z;
    printf("The sum of three number is %g\n", sum);
    system("pause");
    return 0;
}