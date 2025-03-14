#ifndef USER_H
#define USER_H
#include <stdbool.h>

#define NAME_MAX 64
#define MAX_USERS 10
#define MAX_NAME_LEN 32
#define MAX_PASS_LEN 16
#define MIN_PASS_LEN 6

#ifndef USERS_DEFINED
#define USERS_DEFINED

typedef struct User {
    char id[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    struct TreeNode* library;
} user;

#endif

extern user users[MAX_USERS];
extern int usercount;

int findUser(const char* username);
int registerUser(user* u);
bool loginUser(user* u);
int passwordReset(user* u);

#endif