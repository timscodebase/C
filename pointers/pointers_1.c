#include <stdio.h>

int main() {
    int age = 40;     // A regular integer variable.
    int* p_age = NULL; // A pointer variable. Good practice to set it to NULL initially.

    // 1. Store the memory address of 'age' in our pointer 'p_age'.
    p_age = &age;

    // 2. Print everything to see the relationships.
    printf("--- INITIAL VALUES ---\n");
    printf("Value of the 'age' variable: %d\n", age);
    printf("Address of the 'age' variable: %p\n", &age);
    printf("Value of the 'p_age' pointer (it holds the address): %p\n", p_age);

    // 3. To get the value by using the pointer, we DEREFERENCE it with *.
    // This means "go to the address stored in p_age and get the value".
    printf("Value pointed to by 'p_age': %d\n", *p_age);

    // 4. Now, change the value of 'age' using ONLY the pointer.
    printf("\n--- CHANGING VALUE VIA POINTER ---\n");
    *p_age = 41; // Go to the address in p_age and set its value to 41.

    // 5. Print the original 'age' variable to prove it was changed.
    printf("The original 'age' variable is now: %d\n", age);

    return 0;
}