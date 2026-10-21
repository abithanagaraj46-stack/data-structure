
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient *next;
};

struct Patient *head = NULL;

void addPatient() {
    struct Patient *newPatient, *temp;

    newPatient = (struct Patient *)malloc(sizeof(struct Patient));

    if (newPatient == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]", newPatient->name);

    printf("Enter Age: ");
    scanf("%d", &newPatient->age);

    printf("Enter Disease: ");
    scanf(" %49[^\n]", newPatient->disease);

    newPatient->next = NULL;

    if (head == NULL) {
        head = newPatient;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }

    printf("Patient added successfully!\n");
}

void displayPatients() {
    struct Patient *temp = head;

    if (temp == NULL) {
        printf("No patient records found!\n");
        return;
    }

    printf("\n--- Hospital Patient List ---\n");

    while (temp != NULL) {
        printf("\nPatient ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("Disease: %s\n", temp->disease);

        temp = temp->next;
    }
}

void searchPatient() {
    int id;
    struct Patient *temp = head;

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nPatient Found!\n");
            printf("ID: %d\n", temp->id);
            printf("Name: %s\n", temp->name);
            printf("Age: %d\n", temp->age);
            printf("Disease: %s\n", temp->disease);
            return;
        }

        temp = temp->next;
    }

    printf("Patient not found!\n");
}

void deletePatient() {
    int id;
    struct Patient *temp = head;
    struct Patient *prev = NULL;

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Patient not found!\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Patient record deleted successfully!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Hospital Management =====\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                deletePatient();
                break;

            case 5:
                printf("Exiting Hospital Management System...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    while (head != NULL) {
        struct Patient *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
