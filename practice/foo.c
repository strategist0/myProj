#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf env;

void foo() {
    printf("In foo function\n");
    longjmp(env, 1);
}

int main() {
    if (setjmp(env) != 0) {
        printf("Back in main after longjmp\n");
    } else {
        printf("Calling foo function\n");
        foo();
    }
    system("pause");
    return 0;
}
