#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int power(int base, int exponent) {
  int result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: convert hexadecimal or binary to int ./hex2int\n");
    return 0;
  }
  char* input = argv[1]; 
  int isBinary = 0;
  if (input[1] == 'b') {
    isBinary = 1;
  }
  char num[32] = " ";
  strncpy(num, input + 2, strlen(input) - 2);
  num[31] = '\0';
  if (isBinary) {
    int number = atoi(num);
    int transNum = 0;
    int base = 1;
    while(number) {
      int lastDigit = number % 10;
      number = number / 10;
      transNum += lastDigit * base;
      base = base * 2;
    }
    printf("%d", transNum);
  }
  else {
    char asciiLetters[] = {'A', 'B', 'C', 'D', 'E', 'F', '\0'};
    int transNum = 0;
    int pow = 0;
    for (int i = strlen(num) - 1; i >= 0; i--) {
      int digit = 0;
      char* location = strchr(asciiLetters, num[i]);
      if (location != NULL) {
        digit = 10 + (location - asciiLetters);
      }
      else {
        digit = num[i] - 0x30; 
      }
      transNum = transNum + (digit)*power((double)16, (double)pow); 
      pow++;
    }
    printf("%d", transNum);
  }
  return 0;
}
