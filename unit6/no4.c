#include <stdio.h>
int main()
{
    int x,y,z;
    z=0;
    char p[27] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
    for(x=0;x<7;x++)
    {
        for(y=0;y<x;y++,z++)
        printf("%c",p[z]);
        printf("\n");
    }
    return 0;
}