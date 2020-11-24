#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 20

typedef struct NODE {
    char data[MAX_NAME_LEN];
    struct NODE *next;
}node_t;

void appendFriend(node_t *target) {
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    
    char newName[MAX_NAME_LEN];

    printf("Enter your friend's name to append on your friendbook: ");
    scanf("%s", newName);

    // 연결 리스트에서의 노드가 하나도 없을 때, 새 노드를 head 옆에서 추가
    if ((target->next) == NULL) {
        target->next = newNode;
        strcpy(newNode->data, newName);
        newNode->next = NULL;
        return;
    }

    // 연결 리스트의 마지막 노드 (처음에는 head 바로 옆인 첫 번째 노드임)
    node_t *tail = target->next;

    // 연결 리스트에서의 마지막 노드 탐색
    while ((tail->next) != NULL) {
        tail = tail->next;
    }

    // 연결 리스트의 마지막 노드 바로 오른쪽에 새 노드 추가
    tail->next = newNode;
    strcpy(newNode->data, newName);
    newNode->next = NULL;
}

void showFriend(node_t *target, int numberOfFriends) {
    node_t *curr = target->next;
    
    printf("You have %d Friends\n", numberOfFriends);
    printf("-------------------\n");
    while (curr != NULL) {
        printf("\t%s\n", curr->data);
        curr = curr->next;
    }
    printf("-------------------\n\n");
}

bool deleteFriend(node_t *target) {
    if (target->next == NULL) {
        printf("There is no friends in your friendbook to delete\n");
        return false;
    }

    node_t *curr = target->next;

    char deleteName[MAX_NAME_LEN];

    printf("Input friend's name to delete: ");
    scanf("%s", deleteName);

    while (curr != NULL) {
        if (!(strcmp(curr->data, deleteName))) {
            target->next = curr->next;
            free(curr);
            return true;
        } else {
            target = curr;
            curr = curr->next;
        }
    }

    printf("Could not find the name\n");
    return false; 
}

bool insertFriend(node_t *target) {
    if ((target->next) == NULL) {
        printf("There is no friends in your friendbook to insert\n");
        return false;
    }

    node_t *curr = target->next;
    node_t *newNode = (node_t *)malloc(sizeof(node_t));

    if (newNode == NULL) {
        printf("Failed to allocate memory");
        return false;
    }

    char beforeName[MAX_NAME_LEN], newName[MAX_NAME_LEN];
    
    printf("Input new friends name: ");
    scanf("%s", newName);
    printf("Insert before name: ");
    scanf("%s", beforeName);

    while (curr != NULL) {
        if (!(strcmp(curr->data, beforeName))) {   // 두 문자열이 같으면 0을 반환하고, 그렇지 않으면 0이 아닌 값을 반환하므로
            strcpy(newNode->data, newName);        // 문자열이 다르면 True가 된다. 같으면 False가 된다.
            newNode->next = curr;
            target->next = newNode;
            return true;
        } else {
            target = curr;                     
            curr = curr->next;
        }
    }

    printf("Could not find the name\n");
    return false;
}

void freeLinkedList(node_t *target) {
    node_t *curr = target->next;
    
    while (curr != NULL) {
        free(target);
        target = curr;
        curr = curr->next;
    }
}

enum controlList {
    EXIT_PROGRAM = 0,
    ADD_FRIEND,
    SHOW_FRIEND,
    DELETE_FRIEND,
    INSERT_FRIEND
};

int main() {
    node_t *head = (node_t *)malloc(sizeof(node_t)); // 첫 번째 노드를 지칭 (head 바로 옆)

    if (head == NULL) {
        printf("Failed to allocate memory\n");
        return 0;
    }

    int numberOfFriend = 0;
    char name[MAX_NAME_LEN];

    enum controlList control;

    int flag = true;
    int decision = 0;

    while (flag) {
        printf("---- FriendBook ----\n");
        printf("1. Add new friend\n");
        printf("2. Show friends\n");
        printf("3. Delete friend\n");
        printf("4. Insert new friend\n");
        printf("0. Exit\n\n");

        printf("Select a menu: ");
        scanf("%d", &decision);
        control = decision;

        switch (control) {
            case ADD_FRIEND:
                appendFriend(head);
                numberOfFriend++;
                break;
            case SHOW_FRIEND:
                showFriend(head, numberOfFriend);
                break;
            case DELETE_FRIEND:
                if (deleteFriend(head))
                    numberOfFriend--;
                break;
            case INSERT_FRIEND:
                if (insertFriend(head))
                    numberOfFriend++;
                break;
            case EXIT_PROGRAM:
                freeLinkedList(head);
                flag = false;
                break;
            default:
                printf("Invalid Input");
        }
    }

    return 0;
}