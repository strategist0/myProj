#ifndef USER_H
#define USER_H
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_NAME_LEN 32
#define MAX_PASS_LEN 16
#define MIN_PASS_LEN 6

#ifndef USERS_DEFINED
#define USERS_DEFINED

typedef struct User {
    char id[MAX_NAME_LEN + 1];
    char password[MAX_PASS_LEN + 1];
    struct TreeNode* library;
} user;

#endif

extern user users[MAX_USERS];
extern int usercount;

int GetUsers(const char* filename, user* usersArray, int* usercount);
int findUser(const char* username,
             user* usersArray,
             int userCount,
             const char* filename);
int registerUser(user* u, int* usercount, user* users);
bool loginUser(user* u);
int passwordReset(user* u);
void saveUsersToFile(const char* filename, user* users, int usercount);

#endif