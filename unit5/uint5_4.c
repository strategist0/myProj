#include <stdio.h>
int main()
{
    int x,count,sum;
    scanf("%d",&x);
    count=0;
    sum=0;
    while(count++<x)
        sum=sum+count;
    printf("sum = %d\n",sum);
    return 0;
}