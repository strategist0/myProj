#include <stdio.h>
#define MH 60
int main()
{
    int x,y,z;
    scanf("%d",&x);
    z=x/MH;
    y=x%MH;
    printf("%d hours %d minutes",z,y);
    getchar();
    return 0;
}