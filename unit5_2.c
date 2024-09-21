#include <stdio.h>
#define DW 7
int main()
{
    int x,y,z;
    printf("Enter the number of days:");
    scanf("%d",&x);
    y=x/DW;
    z=x%DW;
    printf("%d days are %d weeks, %d days",x,y,z);
    getchar();
    return 0;
}