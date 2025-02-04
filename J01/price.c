#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    int price = rand() % (5000 - 3000 + 1) + 3000;
    int youGuess;
    printf("Welcome to the Price is Right! \n");
    printf("Enter a guess to win a luxurious dishwasher: $");
    scanf("%d", &youGuess);
    int AI_1 = rand() % (5000 - 3000 + 1) + 3000;
    int AI_2 = rand() % (5000 - 3000 + 1) + 3000;
    printf("AI contestant #1 guesses %d\n", AI_1);
    printf("AI contestant #2 guesses %d\n", AI_2);
    printf("The dishwasher costs %d\n", price);
    if (price < AI_1 && price < AI_2 && price < youGuess){
        printf("Sorry, nobody wins the dishwasher. I'm keeping it.");
    } else {
        if (AI_1 > AI_2) {
             if (AI_1 > youGuess) {
                 if(AI_1 < price) {
                     printf("AI contestant #1 wins the dishwasher");
                 }
                 else {
                 if (AI_2 > youGuess) {
                     if (AI_2 < price) {
                        printf("AI contestant #2 wins the dishwasher");
                     }
                    else {
                        printf("You win the dishwasher!");
                    }
                }
                else {
                    if (youGuess < price) {
                        printf("You win the dishwasher!");
                    }
                    else {
                        if (AI_1 < price) {
                             printf("AI contestant #1 wins the dishwasher");
                        }
                       printf("AI contestant #2 wins the dishwasher");
                    }
                }
             }
            }
        }
        else if (AI_2 > youGuess) {
            if (AI_2 < price) {
                printf("AI Contestant 2 wins the dishwasher");
               }
            else if (youGuess < price){
                printf("You win the dishwasher");
            }
            else {
                printf("AI contestant #1 wins the dishwasher");
            }
        }
            else if (youGuess < price) {
                printf("You win the dishwasher!");
            }
        else {
            if (AI_2 < price) {
              printf("AI Contestant #2 wins the dishwasher!");
            }
            else {
            printf("AI contestant #1 wins the dishwasher");
            }
        }   
    return 0;
    }
}

