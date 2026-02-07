#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    srand(time(NULL)); // Seed for random number generation
    int guess = 0; // Random number between 1 and 100
    int tries = 0;
    int min = 1;
    int max = 100;
    int answer = (rand() % (max - min + 1)) + min; // Random number to be guessed
    printf("***Welcome to the Number Guessing Game***\n");
    printf("I have selected a number between %d and %d. Can you guess it?\n", min, max);
    // Loop until the user guesses the correct number
    do {
        printf("Guess a number between %d and %d: ", min, max);
        scanf("%d", &guess);
        tries++;
        if (guess < answer) {
            printf("Too low! Try again.\n");
        } 
        else if (guess > answer){
            printf("Too high! Try again.\n");
        }
        else {
            printf("Congratulations! You've guessed the correct number!\n");
        }
    } while (guess != answer);
    printf("The answer is %d\n", answer);
    printf("It took you %d tries", tries);
    printf("Thank you for playing the Number Guessing Game!\n");


    return 0;
}