#include <stdio.h>
int main()
{
    int x,y,z;
    z=5;
    char p[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(x=1;x<7;x++)
    {
        for(y=0,z=5;y<x;y++,z--)
        printf("%c",p[z]);
        printf("\n");
    }
    return 0;
}