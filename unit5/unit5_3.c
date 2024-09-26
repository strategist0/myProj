#include <stdio.h>
#define CF 0.03
#define CI 0.39
int main()
{
    int x;
    float y,z;
    printf("Please enter a height in centimeters:");
    scanf("%d",&x);
    y=x*CF;
    z=x*CI;
    while(x>0)
    {
    printf("%d cm = %g feet, %g inche\n",x,y,z);
    printf("Enter a height in centimeters(<=0 to quit):");
    scanf("%d",&x);
    y=x*CF;
    z=x*CI;
    }
    printf("bye\n");
    return 0;
}