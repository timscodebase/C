#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h> // For emscripten_sleep

typedef struct {
    char name[100];
    char email[100];
    int age;
} Contact;

// A safe input function that uses emscripten_sleep to avoid freezing the browser.
void get_line_from_user(char* buffer, int size) {
    char c;
    int i = 0;
    // Loop to get input char by char from Emscripten's stdin buffer
    while (i < size - 1) {
        c = getchar();
        // If there's no input yet, getchar() returns -1 (EOF)
        if (c == -1 || c == '\n') {
            // If the buffer is still empty, it means we are waiting for user input.
            // We take a short nap to let the browser's event loop run.
            if (i == 0 && c == -1) {
                emscripten_sleep(100); // Sleep for 100ms
                continue; // Try getting a character again
            } else {
                break; // User pressed Enter or we got EOF after some characters
            }
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0'; // Null-terminate the string
}

void printMenu() {
    printf("\n--- Contact Manager ---\n");
    printf("1. Add Contact\n");
    printf("2. List All Contacts\n");
    printf("3. Delete Contact\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
    fflush(stdout);
}

void addContact(Contact** contactList, int* contactCount, int* capacity) {
    if (*contactCount >= *capacity) {
        *capacity *= 2;
        *contactList = (Contact*)realloc(*contactList, *capacity * sizeof(Contact));
        if (*contactList == NULL) { exit(1); }
        printf("Resized contact list capacity to %d.\n", *capacity);
        fflush(stdout);
    }
    
    printf("Enter name: ");
    fflush(stdout);
    get_line_from_user((*contactList)[*contactCount].name, 100);

    printf("Enter email: ");
    fflush(stdout);
    get_line_from_user((*contactList)[*contactCount].email, 100);

    printf("Enter age: ");
    fflush(stdout);
    char age_buffer[10];
    get_line_from_user(age_buffer, 10);
    (*contactList)[*contactCount].age = atoi(age_buffer);

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
    fflush(stdout);
}

void saveContacts(Contact* list, int count) {
    // Note: Emscripten's default file system is in-memory and does not persist.
    // For real persistence, you would need to use Emscripten's FS API.
    FILE* file = fopen("contacts.dat", "wb");
    if (file == NULL) { return; }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(list, sizeof(Contact), count, file);
    fclose(file);
    printf("Contacts saved successfully (in-memory filesystem).\n");
    fflush(stdout);
}

void loadContacts(Contact** list, int* count, int* capacity) {
    FILE* file = fopen("contacts.dat", "rb");
    if (file == NULL) {
        printf("No existing contact file found. Starting fresh.\n");
        fflush(stdout);
        return;
    }
    fread(count, sizeof(int), 1, file);
    if (*count > 0) {
        *capacity = *count;
        *list = (Contact*)realloc(*list, *capacity * sizeof(Contact));
        if (*list == NULL) { exit(1); }
        fread(*list, sizeof(Contact), *count, file);
        printf("Successfully loaded %d contacts.\n", *count);
        fflush(stdout);
    }
    fclose(file);
}

void deleteContact(Contact** list, int* count) {
    if (*count == 0) {
        printf("No contacts to delete.\n");
        fflush(stdout);
        return;
    }
    listAllContacts(*list, *count);
    
    int index = 0;
    char buffer[10];
    printf("Enter the contact number to delete: ");
    fflush(stdout);
    get_line_from_user(buffer, 10);
    index = atoi(buffer);

    if (index < 1 || index > *count) {
        printf("Invalid contact number.\n");
        fflush(stdout);
        return;
    }
    for (int i = index - 1; i < *count - 1; i++) {
        (*list)[i] = (*list)[i + 1];
    }
    (*count)--;
    printf("Contact deleted successfully.\n");
    fflush(stdout);
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
        char choice_buffer[10];
        get_line_from_user(choice_buffer, 10);
        choice = atoi(choice_buffer);

        switch (choice) {
            case 1: addContact(&contactList, &contactCount, &capacity); break;
            case 2: listAllContacts(contactList, contactCount); break;
            case 3: deleteContact(&contactList, &contactCount); break;
            case 4:
                saveContacts(contactList, contactCount);
                printf("Exiting...\n");
                fflush(stdout);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                fflush(stdout);
        }
    } while (choice != 4);

    free(contactList);
    return 0;
}