#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char item[50];
    struct Node *next;
};

struct Node *head = NULL;

void addItem() {
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter shopping item: ");
    scanf(" %49[^\n]", newNode->item);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("Item added successfully!\n");
}

void displayItems() {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("Shopping list is empty!\n");
        return;
    }

    printf("\n--- Shopping List ---\n");

    while (temp != NULL) {
        printf("- %s\n", temp->item);
        temp = temp->next;
    }
}

void deleteItem() {
    char name[50];
    struct Node *temp = head;
    struct Node *prev = NULL;

    printf("Enter item to delete: ");
    scanf(" %49[^\n]", name);

    while (temp != NULL &&
           strcmp(temp->item, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Item not found!\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Item deleted successfully!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== SHOPPING LIST =====\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Delete Item\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;

            case 2:
                displayItems();
                break;

            case 3:
                deleteItem();
                break;

            case 4:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
