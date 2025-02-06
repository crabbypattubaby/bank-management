#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { MAX_CHAR = 128 };

typedef struct {
  char name[MAX_CHAR];
  unsigned long long accNum;
  float balance;
  char PhoneNo[MAX_CHAR];
  char Password[MAX_CHAR];
} account;

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
      arr[k++] = leftArr[i++];
    } else {
      arr[k++] = rightArr[j++];
    }
  }
  while (i < n1)
    arr[k++] = leftArr[i++];
  while (j < n2)
    arr[k++] = rightArr[j++];
}

void mergeSortint(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSortint(arr, left, mid);
    mergeSortint(arr, mid + 1, right);
    mergeint(arr, left, mid, right);
  }
}

void addBankaccount(account accounts[], int *accountCount) {
  printf("Enter name: ");
  fgets(accounts[*accountCount].name, MAX_CHAR, stdin);
  accounts[*accountCount].name[strcspn(accounts[*accountCount].name, "\n")] =
      '\0';

  accounts[*accountCount].accNum =
      ((unsigned long long)rand() << 32 | rand()) % 9000000000000000ULL +
      1000000000000000ULL;
  printf("Generated account number: %llu\n", accounts[*accountCount].accNum);

  printf("Enter balance: ");
  scanf("%f", &accounts[*accountCount].balance);
  getchar(); // Clear newline left in buffer

  printf("Enter phone number: ");
  fgets(accounts[*accountCount].PhoneNo, MAX_CHAR, stdin);
  accounts[*accountCount]
      .PhoneNo[strcspn(accounts[*accountCount].PhoneNo, "\n")] = '\0';

  bool rpass = false;
  char temp[MAX_CHAR];

  do {
    printf("Enter Password: ");
    fgets(accounts[*accountCount].Password, MAX_CHAR, stdin);
    accounts[*accountCount]
        .Password[strcspn(accounts[*accountCount].Password, "\n")] = '\0';

    printf("Reenter the Password: ");
    fgets(temp, MAX_CHAR, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if (strcmp(accounts[*accountCount].Password, temp) == 0) {
      printf("Your password has been set successfully :).\n");
      rpass = true;
    } else {
      printf("Your passwords do not match, please enter them again.\n");
    }
  } while (!rpass);

  (*accountCount)++;
}

void writeCSV(const char *filename, account acc) {
  FILE *file = fopen(filename, "a");
  if (file == NULL) {
    perror("Failed to open file");
    return;
  }

  fprintf(file, "%s,%llu,%.2f,%s\n", acc.name, acc.accNum, acc.balance,
          acc.PhoneNo);
  fclose(file);
  printf("Data written to %s successfully!\n", filename);
}

void readCSV(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char line[256];
  account acc;
  while (fgets(line, sizeof(line), file)) {
    if (sscanf(line, "%127[^,],%llu,%f,%127[^\n]", acc.name, &acc.accNum,
               &acc.balance, acc.PhoneNo) == 4) {
      printf(
          "Name: %s\nAccount Number: %llu\nBalance: %.2f\nPhone Number: %s\n\n",
          acc.name, acc.accNum, acc.balance, acc.PhoneNo);
    } else {
      printf("Error reading line: %s\n", line);
    }
  }

  fclose(file);
}

int binarySearch(const account *accounts, int accountCount, const char *name) {
  int left = 0, right = accountCount - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    int comparison = strcmp(accounts[mid].name, name);

    if (comparison == 0)
      return mid;
    else if (comparison < 0)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

void searchAccount(const account *accounts, int accountCount,
                   const char *name) {
  int index = binarySearch(accounts, accountCount, name);
  if (index != -1) {
    printf("Account found:\n");
    printf("Name: %s\nAccount Number: %llu\nBalance: %.2f\nPhone Number: %s\n",
           accounts[index].name, accounts[index].accNum,
           accounts[index].balance, accounts[index].PhoneNo);
  } else {
    printf("Account not found.\n");
  }
}

int lengthCSV(const char *filename, account accounts[], int maxAccounts) {
  FILE *file = fopen(filename, "r");
  char line[MAX_CHAR];
  if (file == NULL) {
    perror("File not found :(");
    return 0;
  }

  int count = 0;
  while (count < maxAccounts && fgets(line, sizeof(line), file)) {
    if (sscanf(line, "%127[^,],%llu,%f,%127[^\n]", accounts[count].name,
               &accounts[count].accNum, &accounts[count].balance,
               accounts[count].PhoneNo) == 4) {
      count++;
    }
  }

  fclose(file);
  return count;
}

int main() {
  srand(time(NULL));

  account accounts[100];
  char filename[] = "accounts.csv";
  int accountCount = lengthCSV(filename, accounts, 100);
  int option;
  bool escape = false;

  do {
    printf("\n1. Add Account\n2. Search Account\n3. Leave program\n");
    printf("Enter your choice: ");
    scanf("%d", &option);
    getchar(); // Clear buffer after scanf

    switch (option) {
    case 1:
      addBankaccount(accounts, &accountCount);
      writeCSV(filename, accounts[accountCount - 1]);
      break;
    case 2: {
      char name[MAX_CHAR];
      printf("Please enter your name: ");
      fgets(name, MAX_CHAR, stdin);
      name[strcspn(name, "\n")] = '\0';
      searchAccount(accounts, accountCount, name);
      break;
    }
    case 3:
      printf("Thank you for using the program :).\n");
      escape = true;
      break;
    default:
      printf("Invalid option. Please try again.\n");
    }
  } while (!escape);

  return 0;
}
