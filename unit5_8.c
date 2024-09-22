#include <stdio.h>
void Temperature(double f);
int main()
{
    double t;
    printf("Please enter a temperature in Fahrenheit:");
    while(scanf("%lf",&t) == 1)
    {
        Temperature(t);
        printf("Enter next temperature in Fahrenheit(or enter 'q' to quit):");
    }
    return 0;
}
void Temperature(double f)
{
    double c,k;
    const double r=32.0;
    const double y=273.15;
    c=5.0/9.0*(f-r);
    k=c+y;
    printf("The temperature in Celsius is %.3lf\n",c);
    printf("The temperature in Kelvin is %.3lf\n",k);
}