#include <stdio.h>
int main()
{
    int x,y,z;
    printf("This program computes moduli.\n\
Enter an integer to serve as the second operand:");
    scanf("%d",&x);
    printf("Now enter the first operand:");
    scanf("%d",&y);
    while(y>0)
        {
        z=y%x;
        printf("%d %% %d is %d\n",y,x,z);
        printf("Enter the next number for first operand (<= 0 to quit):");
        scanf("%d",&y);
        }
    printf("done\n");
    return 0;
}