/***************************************************
 * cypher.c
 * Author: Elisabeth Brann
 * Date: 01/31/2025
 * Asks the user for a word and then encodes it using a shift cypher
 */
#include <stdio.h>

int main() {
  printf("Enter a word: ");
  char word[50];
  scanf("%s", word);
  printf("Enter a shift: ");
  int shift;
  scanf("%d", &shift);
  int i = 0;
  while (word[i] != '\0') {
    word[i] = word[i] + shift;
    if (word[i] < 97) {
      int overshoot = 97 - word[i];
      word[i] = 123 - overshoot;
    }
    else if (word[i] > 122) {
      int overshoot = word[i] - 122;
      word[i] = 96 + overshoot;
    }
    i = i + 1;
  }
  printf("Your cypher is %s", word);
  return 0;
}
