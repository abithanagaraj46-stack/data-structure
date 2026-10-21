
#include <stdio.h>
#include <string.h>

#define MAX 100

char backStack[MAX][100];
char forwardStack[MAX][100];
char currentPage[100] = "Google";

int backTop = -1, forwardTop = -1;

void push(char stack[MAX][100], int *top, char page[]) {
    if (*top < MAX - 1) {
        strcpy(stack[++(*top)], page);
    }
}

void pop(char stack[MAX][100], int *top, char page[]) {
    if (*top >= 0) {
        strcpy(page, stack[(*top)--]);
    }
}

void visitPage(char page[]) {
    push(backStack, &backTop, currentPage);
    strcpy(currentPage, page);
    forwardTop = -1;
    printf("Current Page: %s\n", currentPage);
}

void goBack() {
    if (backTop >= 0) {
        push(forwardStack, &forwardTop, currentPage);
        pop(backStack, &backTop, currentPage);
        printf("Current Page: %s\n", currentPage);
    } else {
        printf("No previous page!\n");
    }
}

void goForward() {
    if (forwardTop >= 0) {
        push(backStack, &backTop, currentPage);
        pop(forwardStack, &forwardTop, currentPage);
        printf("Current Page: %s\n", currentPage);
    } else {
        printf("No forward page!\n");
    }
}

int main() {
    int choice;
    char page[100];

    do {
        printf("\n--- Browser Menu ---\n");
        printf("1. Visit New Page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Display Current Page\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter page name: ");
                scanf("%99s", page);
                visitPage(page);
                break;

            case 2:
                goBack();
                break;

            case 3:
                goForward();
                break;

            case 4:
                printf("Current Page: %s\n", currentPage);
                break;

            case 5:
                printf("Exiting Browser...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
