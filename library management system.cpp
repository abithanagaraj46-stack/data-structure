
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int available;
    struct Book *next;
};

struct Book *head = NULL;

/* Search for a book by ID */
struct Book *searchBook(int id) {
    struct Book *temp = head;

    while (temp != NULL) {
        if (temp->id == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

/* Add a new book */
void addBook() {
    struct Book *newBook, *temp;

    newBook = malloc(sizeof(struct Book));

    if (newBook == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Book ID: ");
    if (scanf("%d", &newBook->id) != 1) {
        printf("Invalid input!\n");
        free(newBook);
        return;
    }

    if (searchBook(newBook->id) != NULL) {
        printf("Book ID already exists!\n");
        free(newBook);
        return;
    }

    printf("Enter Book Title: ");
    scanf(" %99[^\n]", newBook->title);

    printf("Enter Author Name: ");
    scanf(" %99[^\n]", newBook->author);

    newBook->available = 1;
    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    } else {
        temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newBook;
    }

    printf("Book added successfully!\n");
}

/* Display all books */
void displayBooks() {
    struct Book *temp = head;

    if (head == NULL) {
        printf("No books available!\n");
        return;
    }

    printf("\n--- Library Book List ---\n");

    while (temp != NULL) {
        printf("\nBook ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("Status: %s\n",
               temp->available ? "Available" : "Issued");

        temp = temp->next;
    }
}

/* Search for a book */
void searchBookMenu() {
    int id;
    struct Book *book;

    printf("Enter Book ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    book = searchBook(id);

    if (book == NULL) {
        printf("Book not found!\n");
    } else {
        printf("\nBook Found!\n");
        printf("Book ID: %d\n", book->id);
        printf("Title: %s\n", book->title);
        printf("Author: %s\n", book->author);
        printf("Status: %s\n",
               book->available ? "Available" : "Issued");
    }
}

/* Issue a book */
void issueBook() {
    int id;
    struct Book *book;

    printf("Enter Book ID to issue: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    book = searchBook(id);

    if (book == NULL) {
        printf("Book not found!\n");
    } else if (!book->available) {
        printf("Book is already issued!\n");
    } else {
        book->available = 0;
        printf("Book issued successfully!\n");
    }
}

/* Return a book */
void returnBook() {
    int id;
    struct Book *book;

    printf("Enter Book ID to return: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    book = searchBook(id);

    if (book == NULL) {
        printf("Book not found!\n");
    } else if (book->available) {
        printf("Book is already available!\n");
    } else {
        book->available = 1;
        printf("Book returned successfully!\n");
    }
}

/* Delete a book record */
void deleteBook() {
    int id;
    struct Book *temp = head;
    struct Book *prev = NULL;

    printf("Enter Book ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Book not found!\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Book deleted successfully!\n");
}

/* Free all allocated memory */
void freeBooks() {
    struct Book *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBookMenu();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                printf("Exiting Library Management System...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    freeBooks();
    return 0;
}
