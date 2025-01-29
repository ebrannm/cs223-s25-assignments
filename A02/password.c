/***************************************************
 * password.c
 * Author: Elisabeth Brann
 * Date: 01/31/2025
 * Asks user for a word and creates a bad password from it
 */
#include <stdio.h>

int main() {
  printf("Enter a word: ");
  char word[50];
  scanf("%s", word);
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == 'e') {
      word[i] = '3';
    }
    else if (word[i] == 'i') {
      word[i] = '1';
    }
    else if (word[i] == 'a') {
      word[i] = '@';
    }
  }
  printf("%s %s", "Your bad password is", word);
  return 0;
}
