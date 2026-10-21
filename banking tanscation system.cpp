
#include <stdio.h>
#include <string.h>

#define MAX 100
#define QMAX 100

struct Account {
    int accNo;
    char name[50];
    float balance;
};

struct Transaction {
    int accNo;
    char type[20];
    float amount;
};

struct Account accounts[MAX];
struct Transaction queue[QMAX];

int count = 0;
int front = 0, rear = -1, qCount = 0;

void addTransaction(int accNo, char type[], float amount) {
    if (qCount == QMAX) {
        printf("Transaction queue is full!\n");
        return;
    }

    rear = (rear + 1) % QMAX;
    queue[rear].accNo = accNo;
    strcpy(queue[rear].type, type);
    queue[rear].amount = amount;
    qCount++;
}

int findAccount(int accNo) {
    int i;

    for (i = 0; i < count; i++) {
        if (accounts[i].accNo == accNo)
            return i;
    }

    return -1;
}

void createAccount() {
    int accNo;

    if (count == MAX) {
        printf("Account storage is full!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo) != -1) {
        printf("Account number already exists!\n");
        return;
    }

    accounts[count].accNo = accNo;

    printf("Enter account holder name: ");
    scanf(" %49[^\n]", accounts[count].name);

    printf("Enter initial balance: ");
    if (scanf("%f", &accounts[count].balance) != 1 ||
        accounts[count].balance < 0) {
        printf("Invalid balance!\n");
        return;
    }

    printf("Account created successfully!\n");
    count++;
}

void displayAccounts() {
    int i;

    if (count == 0) {
        printf("No accounts available!\n");
        return;
    }

    printf("\n--- Account Details ---\n");

    for (i = 0; i < count; i++) {
        printf("Account Number: %d\n", accounts[i].accNo);
        printf("Name: %s\n", accounts[i].name);
        printf("Balance: %.2f\n\n", accounts[i].balance);
    }
}

void deposit() {
    int accNo, index;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if (index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter deposit amount: ");
    if (scanf("%f", &amount) != 1 ||
        amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    accounts[index].balance += amount;
    addTransaction(accNo, "Deposit", amount);

    printf("Deposit successful!\n");
    printf("New balance: %.2f\n", accounts[index].balance);
}

void withdraw() {
    int accNo, index;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if (index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter withdrawal amount: ");
    if (scanf("%f", &amount) != 1 ||
        amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > accounts[index].balance) {
        printf("Insufficient balance!\n");
        return;
    }

    accounts[index].balance -= amount;
    addTransaction(accNo, "Withdrawal", amount);

    printf("Withdrawal successful!\n");
    printf("Remaining balance: %.2f\n",
           accounts[index].balance);
}

void searchAccount() {
    int accNo, index;

    printf("Enter account number: ");
    scanf("%d", &accNo);

    index = findAccount(accNo);

    if (index == -1) {
        printf("Account not found!\n");
    } else {
        printf("\nAccount Found!\n");
        printf("Account Number: %d\n", accounts[index].accNo);
        printf("Name: %s\n", accounts[index].name);
        printf("Balance: %.2f\n", accounts[index].balance);
    }
}

void displayTransactions() {
    int i, pos;

    if (qCount == 0) {
        printf("No transactions recorded!\n");
        return;
    }

    printf("\n--- Transaction History (Oldest First) ---\n");

    for (i = 0; i < qCount; i++) {
        pos = (front + i) % QMAX;

        printf("Account: %d | Type: %s | Amount: %.2f\n",
               queue[pos].accNo,
               queue[pos].type,
               queue[pos].amount);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== BANKING TRANSACTION SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Display Transaction History\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                searchAccount();
                break;
            case 6:
                displayTransactions();
                break;
            case 7:
                printf("Thank you for using our system!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}
