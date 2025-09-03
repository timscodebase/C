#include <stdio.h>

void printGrade(float average) {
    if (average >= 90) {
        printf("You got an A!\n");
    } else if (average >= 80) {
        printf("You got a B!\n");
    } else if (average >= 70) {
        printf("You got a C.\n");
    } else {
        printf("You need to work harder.\n");
    }
}

float calculateAverage(int arr[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
    }
    float average = (float)sum / count;
    return average;
}

int main() {
    int bowlingScores[4] = {88, 92, 75, 95};

    float avg = calculateAverage(bowlingScores, 4);
    printf("Your average score is: %.2f\n", avg);
    printGrade(avg);

    return 0;
}