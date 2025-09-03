#include <stdio.h>

int main() {
    int bowlingScores[3] = {157, 182, 165};

    printf("Your bowling scores were:\n");

    for (int i = 0; i < 3; i++) {
        printf("Game %d: %d\n", i + 1, bowlingScores[i]);
    }

    return 0;
}