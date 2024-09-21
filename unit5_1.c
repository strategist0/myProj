#include <stdio.h>
int main()
{
    int x,y;
    printf("Enter a number:");
    scanf("%d",&x);
    y=x;
    while(x<y+11)
    {
    printf("%d\n",x);
    x++;
    }
    getchar();
    return 0;
}