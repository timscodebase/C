#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    char email[100];
    int age;
} Contact;

// Helper function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    printf("\n--- Contact Manager ---\n");
    printf("1. Add Contact\n");
    printf("2. List All Contacts\n");
    printf("3. Delete Contact\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void addContact(Contact** contactList, int* contactCount, int* capacity) {
    if (*contactCount >= *capacity) {
        *capacity *= 2;
        *contactList = (Contact*)realloc(*contactList, *capacity * sizeof(Contact));
        if (*contactList == NULL) {
            exit(1);
        }
        printf("Resized contact list capacity to %d.\n", *capacity);
    }
    
    char buffer[100];

    printf("Enter name: ");
    fgets((*contactList)[*contactCount].name, 100, stdin);
    (*contactList)[*contactCount].name[strcspn((*contactList)[*contactCount].name, "\n")] = 0;

    printf("Enter email: ");
    fgets((*contactList)[*contactCount].email, 100, stdin);
    (*contactList)[*contactCount].email[strcspn((*contactList)[*contactCount].email, "\n")] = 0;

    printf("Enter age: ");
    fgets(buffer, 100, stdin);
    (*contactList)[*contactCount].age = atoi(buffer);

    (*contactCount)++;
}

void listAllContacts(Contact* contactList, int contactCount) {
    printf("\n--- All Contacts ---\n");
    if (contactCount == 0) {
        printf("No contacts to display.\n");
    }
    for (int i = 0; i < contactCount; i++) {
        printf("Contact %d:\n", i + 1);
        printf("  Name: %s\n", contactList[i].name);
        printf("  Email: %s\n", contactList[i].email);
        printf("  Age: %d\n", contactList[i].age);
    }
    printf("--------------------\n");
}

void saveContacts(Contact* list, int count) {
    FILE* file = fopen("contacts.dat", "wb");
    if (file == NULL) { return; }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(list, sizeof(Contact), count, file);
    fclose(file);
    printf("Contacts saved successfully.\n");
}

void loadContacts(Contact** list, int* count, int* capacity) {
    FILE* file = fopen("contacts.dat", "rb");
    if (file == NULL) {
        printf("No existing contact file found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    if (*count > 0) {
        *capacity = *count;
        *list = (Contact*)realloc(*list, *capacity * sizeof(Contact));
        if (*list == NULL) { exit(1); }
        fread(*list, sizeof(Contact), *count, file);
        printf("Successfully loaded %d contacts.\n", *count);
    }
    fclose(file);
}

void deleteContact(Contact** list, int* count) {
    if (*count == 0) {
        printf("No contacts to delete.\n");
        return;
    }
    listAllContacts(*list, *count);
    
    int index = 0;
    printf("Enter the contact number to delete: ");
    scanf("%d", &index);
    clearInputBuffer();

    if (index < 1 || index > *count) {
        printf("Invalid contact number.\n");
        return;
    }
    for (int i = index - 1; i < *count - 1; i++) {
        (*list)[i] = (*list)[i + 1];
    }
    (*count)--;
    printf("Contact deleted successfully.\n");
} 

int main() {
    int contactCount = 0;
    int capacity = 2;
    Contact* contactList = (Contact*)malloc(capacity * sizeof(Contact));
    if (contactList == NULL) { return 1; }
    
    loadContacts(&contactList, &contactCount, &capacity);

    int choice = 0;
    do {
        printMenu();
        scanf("%d", &choice);
        clearInputBuffer(); 

        switch (choice) {
            case 1: addContact(&contactList, &contactCount, &capacity); break;
            case 2: listAllContacts(contactList, contactCount); break;
            case 3: deleteContact(&contactList, &contactCount); break;
            case 4:
                saveContacts(contactList, contactCount);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    free(contactList);
    return 0;
}