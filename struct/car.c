#include <stdio.h>
#include <string.h> // We need this for strcpy

struct Car {
    char brand[50];
    char model[50];
    int year;
};

int main() {
    struct Car myCar;

    printf("Enter your car's make: ");
    fgets(myCar.brand, sizeof(myCar.brand), stdin);
    myCar.brand[strcspn(myCar.brand, "\n")] = 0;  // Remove newline character

    printf("Enter your car's model: ");
    fgets(myCar.model, sizeof(myCar.model), stdin);
    myCar.model[strcspn(myCar.model, "\n")] = 0;  // Remove newline character

    printf("Enter your car's year: ");
    scanf("%d", &myCar.year);

    printf("My car is a %d %s %s.\n", myCar.year, myCar.brand, myCar.model);

    return 0;
}