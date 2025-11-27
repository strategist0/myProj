#include <stdio.h>

int main() {
    char stack[100];
    int i = 0;
    while ((stack[i] = getchar()) != '#') {
        printf("%c", &stack[i]);
        i++;
    }
}
