#ifndef ADMINI_H
#define ADMINI_H

#include <stdbool.h>
#include <stdio.h>

typedef struct admini {
    char id[33];
    char password[17];
} admini;

void SortUsers();
bool AdmPswReset();
bool AdminiManage();
void getPassword(char* password, const char* prompt);
void UserPswReset();

#endif