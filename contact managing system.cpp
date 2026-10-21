
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Contact {
    char name[50];
    char phone[20];
    char email[60];
    struct Contact *next;
};

struct Contact *hashTable[SIZE] = {NULL};

/* Hash function based on phone number */
int hashFunction(char phone[]) {
    unsigned int hash = 0;
    int i;

    for (i = 0; phone[i] != '\0'; i++) {
        hash = (hash * 31 + (unsigned char)phone[i]) % SIZE;
    }

    return hash;
}

/* Add a new contact */
void addContact() {
    struct Contact *newContact, *temp;
    int index;
    char phone[20];

    newContact = malloc(sizeof(struct Contact));

    if (newContact == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", newContact->name);

    printf("Enter Phone Number: ");
    scanf("%19s", phone);

    index = hashFunction(phone);

    /* Prevent duplicate phone numbers */
    temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->phone, phone) == 0) {
            printf("Phone number already exists!\n");
            free(newContact);
            return;
        }
        temp = temp->next;
    }

    strcpy(newContact->phone, phone);

    printf("Enter Email: ");
    scanf(" %59[^\n]", newContact->email);

    newContact->next = hashTable[index];
    hashTable[index] = newContact;

    printf("Contact added successfully!\n");
}

/* Display all contacts */
void displayContacts() {
    struct Contact *temp;
    int i, found = 0;

    printf("\n--- Contact List ---\n");

    for (i = 0; i < SIZE; i++) {
        temp = hashTable[i];

        while (temp != NULL) {
            printf("\nName: %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);

            temp = temp->next;
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts available!\n");
    }
}

/* Search a contact by phone number */
void searchContact() {
    char phone[20];
    int index;
    struct Contact *temp;

    printf("Enter Phone Number to Search: ");
    scanf("%19s", phone);

    index = hashFunction(phone);
    temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->phone, phone) == 0) {
            printf("\nContact Found!\n");
            printf("Name: %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);
            return;
        }

        temp = temp->next;
    }

    printf("Contact not found!\n");
}

/* Delete a contact by phone number */
void deleteContact() {
    char phone[20];
    int index;
    struct Contact *temp, *prev = NULL;

    printf("Enter Phone Number to Delete: ");
    scanf("%19s", phone);

    index = hashFunction(phone);
    temp = hashTable[index];

    while (temp != NULL && strcmp(temp->phone, phone) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Contact not found!\n");
        return;
    }

    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Contact deleted successfully!\n");
}

/* Release allocated memory */
void freeContacts() {
    int i;
    struct Contact *temp, *next;

    for (i = 0; i < SIZE; i++) {
        temp = hashTable[i];

        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }

        hashTable[i] = NULL;
    }
}

int main() {
    int choice;

    do {
        printf("\n===== CONTACT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                deleteContact();
                break;

            case 5:
                printf("Exiting Contact Management System...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    freeContacts();
    return 0;
}
