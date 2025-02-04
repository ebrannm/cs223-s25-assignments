/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/07/25
 * Description: Asks the user for a string s and an integer n then
 * creates a new string that repeats s n times
 ---------------------------------------------*/
#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

int main() {
  printf("Enter a word: ");
  char word[32];
  scanf("%s", word);
  int count;
  printf("Enter a count: ");
  scanf("%d", &count);
  char *repeated = malloc(sizeof(char) * strlen(word) * count);
  if (repeated == NULL) {
    printf("Cannot allocate new string. Exiting...");
    exit(1);
  }
  for (int i = 0; i < sizeof(char) * strlen(word) * count; i = i + strlen(word)) {
    if (i == 0) {
      strcpy(repeated, word);
    }
    else {
      strcat(repeated, word);
    }
  }
  printf("%s", repeated);
  free(repeated);
  return 0;
}
