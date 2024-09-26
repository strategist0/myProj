#include <stdio.h>
void cube(double y);
int main()
{
    double x;
    printf("please enter a number:");
    scanf("%lf",&x);
    cube(x);
    return 0;
}
void cube(double y)
{
    printf("the x cube should be %lf",y*y*y);
}