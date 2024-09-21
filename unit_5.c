#include <stdio.h>
int main()
{
    int x,count,sum;
    scanf("%d",&x);
    sum=0;
    count=0;
    while(count++<x)
        sum=sum+count*count;
    printf("sum = %d\n",sum);
    return 0;
}