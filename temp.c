#include <stdio.h>
#include <stdlib.h>

int main() {
    double exp = 0.00000001;
    double a, b;
    
    scanf("%lf %lf", &a, &b);
    
    printf("%lf/%lf = %lf\n", a, b, a / b);
    
    getchar();
    
    system("pause");
    
    return 0;
}