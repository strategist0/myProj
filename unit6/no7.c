#include <stdio.h>
#include <string.h>
int main()
{
    char word[30];
    printf("Enter words:");
    scanf("%s",word);
    printf("The word you enter is: %s\n",word);
    printf("The reserved word you enter is:");
    printf("%lld\n",strlen(word));
    for(int n=strlen(word)-1;n>=0;n--)
    printf("%c",word[n]);
    printf("\n");
    return 0;
}