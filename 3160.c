#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30
#define MAX_FRIENDS 100

char* readFriendList() {
    char* line = malloc(MAX_FRIENDS * MAX_NAME_LENGTH);
    scanf("%[^\n]%*c", line);
    return line;
}

int main() {
    char* currentFriends = readFriendList();
    char* newFriends = readFriendList();
    char friendName[MAX_NAME_LENGTH];
    scanf("%[^\n]%*c", friendName);

    char* updatedFriends = malloc(MAX_FRIENDS * MAX_NAME_LENGTH * 2);
    if (strcmp(friendName, "nao") == 0 ||
        strstr(currentFriends, friendName) == NULL) {
        sprintf(updatedFriends, "%s %s", currentFriends, newFriends);
    } else {
        char* friendPosition = strstr(currentFriends, friendName);
        strncpy(updatedFriends, currentFriends,
                friendPosition - currentFriends);
        sprintf(updatedFriends + (friendPosition - currentFriends), "%s %s",
                newFriends, friendPosition);
    }

    printf("%s\n", updatedFriends);

    free(currentFriends);
    free(newFriends);
    free(updatedFriends);

    return 0;
}