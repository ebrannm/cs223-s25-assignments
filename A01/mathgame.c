/***************************************************
 * mathgame.c
 * Author: Elisabeth Brann
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Welcome to Math Game!\n");
  printf("How many rounds do you want to play? ");
  int value;
  scanf("%d", &value);
  int questNum = 0;
  int numCorrect = 0;
  while (questNum < value) {
    int upper = 9;
    int lower = 1;
    int num1 = rand() % (upper - lower + 1) + lower;
    int num2 = rand() % (upper - lower + 1) + lower;
    printf("%d", num1);
    printf(" + ");
    printf("%d", num2);
    printf(" = ? ");
    int inputSum;
    scanf("%d", &inputSum);
    int realSum = num1 + num2;
    if (realSum == inputSum) {
      printf("Correct!\n");
      numCorrect = numCorrect + 1;
    }
    else {
      printf("Incorrect :(\n");
    }
    questNum = questNum + 1;
  }
  printf("You answered ");
  printf("%d", numCorrect); 
  printf("/");
  printf("%d", questNum);
  printf(" correctly.");
  return 0;
}