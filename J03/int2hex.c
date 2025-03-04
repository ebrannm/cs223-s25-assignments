#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: ./int2hex <int>\n");
        exit(1);
    }

    int val = atoi(argv[1]);

    printf("0b ");
    int num = 0;

    for (int i = 31; i >= 0; i--) {
      int mask = 1 << i;
      int bit = (val & mask) >> i;
      printf("%d", bit);
      num++;
      if (num % 4 == 0) {
        printf(" ");
      }
    }
    printf("\n");

    num = 0;
    char *hexLit = "0123456789ABCDEF";
    printf("0x ");
    for (int i = 7; i >= 0; i--) {
      int mask = 0xF << (i * 4);
      int bit = (val & mask) >> (i * 4);
      printf("%c", hexLit[bit]);
      num++;
      if (num % 2 == 0) {
        printf(" ");
      }
    }
    printf("\n");
}