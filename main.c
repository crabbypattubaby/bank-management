#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


enum { MAX_CHAR = 128 };

typedef struct {
    char name[MAX_CHAR];
    unsigned long long accNum;
    float balance;
    long long int PhoneNo;
} account;

// Function to merge two subarrays of arr[]
void mergeint(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Function to sort an array using merge sort algorithm
void mergeSortInt(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortInt(arr, left, mid);
        mergeSortInt(arr, mid + 1, right);

        mergeint(arr, left, mid, right);
    }
}

// Function to merge two subarrays of a string array
void mergeString(char arr[][20], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char leftArr[n1][20], rightArr[n2][20];

    for (int i = 0; i < n1; i++)
        strcpy(leftArr[i], arr[left + i]);
    for (int j = 0; j < n2; j++)
        strcpy(rightArr[j], arr[mid + 1 + j]);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(leftArr[i], rightArr[j]) <= 0) {
            strcpy(arr[k], leftArr[i]);
            i++;
        } else {
            strcpy(arr[k], rightArr[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(arr[k], leftArr[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(arr[k], rightArr[j]);
        j++;
        k++;
    }
}

// Function to perform merge sort on an array of strings
void mergeSortString(char arr[][20], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortString(arr, left, mid);
        mergeSortString(arr, mid + 1, right);

        mergeString(arr, left, mid, right);
    }
}

// Function to add a bank account
void addBankaccount(account *newaccount) {
    printf("\n************************************\nName:\n");
    fgets(newaccount->name, MAX_CHAR, stdin);
    newaccount->name[strcspn(newaccount->name, "\n")] = '\0'; // Remove newline character
    newaccount->accNum = 1000000000000000ULL + (rand() % 9000000000000000ULL);
    printf("Your account number is: %llu\n", newaccount->accNum);

    printf("\n************************************\nBalance:\n");
    scanf("%f", &newaccount->balance);

    printf("\n************************************\nPhone Number:\n");
    scanf("%d", &newaccount->PhoneNo);
}


void writeCSV(const char *filename, account acc) {
    FILE *file = fopen(filename, "a");  // Open file in write mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Directly store data in CSV format
    fprintf(file, "%s,%llu,%.2f,%d\n", acc.name, acc.accNum, acc.balance, acc.PhoneNo);

    fclose(file);
    printf("Data written to %s successfully!\n", filename);
}

void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    account acc;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%127[^,],%llu,%f,%d", acc.name, &acc.accNum, &acc.balance, &acc.PhoneNo) == 4) {
            printf("Name: %s\nAccount Number: %llu\nBalance: %.2f\nPhone Number: %d\n\n",
                   acc.name, acc.accNum, acc.balance, acc.PhoneNo);
        } else {
            printf("Error reading line: %s\n", line);
        }
    }

    fclose(file);  // Close the file
}

// Function to input account details
void inputAccountDetails(account *acc) {
    char buffer[256];

    printf("Enter name: ");
    fgets(acc->name, MAX_CHAR, stdin);
    acc->name[strcspn(acc->name, "\n")] = '\0'; // Remove newline character

    printf("Enter account number: ");
    fgets(buffer, sizeof(buffer), stdin);
    acc->accNum = strtoull(buffer, NULL, 10);

    printf("Enter balance: ");
    fgets(buffer, sizeof(buffer), stdin);
    acc->balance = strtof(buffer, NULL);

    printf("Enter phone number: ");
    fgets(buffer, sizeof(buffer), stdin);
    acc->PhoneNo = strtoll(buffer, NULL, 10);
}

// Function to print account details
void printAccountDetails(const account *acc) {
    printf("Name: %s\n", acc->name);
    printf("Account Number: %llu\n", acc->accNum);
    printf("Balance: %.2f\n", acc->balance);
    printf("Phone Number: %lld\n", acc->PhoneNo);
}
int binarySearch(const account *accounts, int accountCount, const char *name) {
    int left = 0;
    int right = accountCount - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparison = strcmp(accounts[mid].name, name);

        if (comparison == 0) {
            return mid; // Account found at index mid
        } else if (comparison < 0) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Account not found
}

void searchAccount(const account *accounts, int accountCount, const char *name) {
    int index = binarySearch(accounts, accountCount, name);
    if (index != -1) {
        printf("Account found:\n");
        printAccountDetails(&accounts[index]);
    } else {
        printf("Account not found.\n");
    }
}

int lengthCSV(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File not found :(");
        return -1;  // Indicate an error
    }

    int count = 0;
    char line[1024];  // Buffer to read lines

    while (fgets(line, sizeof(line), file)) {
        count++;  // Count each line
    }

    fclose(file);
    return count;
}



int main() {
    int option;
    bool escape = false;

    account accounts[MAX_CHAR];
    int accountCount = 0;
    char filename[] = "accounts.csv";

    do {
        printf("\n1. Add Account\n2. Write to CSV\n3. Read from CSV\n4. Search Account\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        getchar(); // Consume newline character left by scanf

        switch (option) {
            case 1:
                addBankaccount(accounts);
                writeCSV(filename, accounts[accountCount]);
                accountCount++;
            case 2:
            char name[MAX_CHAR];
            printf("Please enter your name: ");
            fgets(name, MAX_CHAR, stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove newline character
            searchAccount(accounts, accountCount, name);
            break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (!escape);
    return 0;
}
