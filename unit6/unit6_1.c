#include <stdio.h>
int main()
{
    char num[26];
    int n;
    for(n=0;n<=25;n++)
        scanf("%c",&num[n]);
    for(n=0;n<=25;n++)
        printf("%c",num[n]);
        printf("\n");
        return 0;
}