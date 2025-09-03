#include <stdio.h>

// This function takes a POINTER to an integer.
void addFive(int* number) {
    // Go to the address stored in 'number' and add 5 to the value there.
    *number = *number + 5; 
}

int main() {
    int myValue = 10;
    
    printf("Original value: %d\n", myValue);
    
    // We pass the ADDRESS of myValue to the function.
    addFive(&myValue); 
    
    printf("Value after function call: %d\n", myValue); // It's permanently changed!
    
    return 0;
}