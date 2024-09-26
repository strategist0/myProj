#include <stdio.h>
int main()
{
    int start,end;
    printf("enter a start number:");
    scanf("%d",&start);
    printf("enter a end number:");
    scanf("%d",&end);
    printf("Ori: Square: Cube:\n");
    for(;start<=end;start++)
    {
        printf("%d,     %d,     %d",start,start*start,start*start*start);
        printf("\n");
    }
    return 0;
}