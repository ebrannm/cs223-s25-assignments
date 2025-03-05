/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 3/06/25
 * Description: Reads in a single 64-bit unsigned integer and outputs
 * it as an 8x8 1bpp sprite
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  for (int i = 0; i < 8; i++) { //rows
    for (int j = 0; j < 8; j++) { //cols
      unsigned long mask = 0x1UL << (63 - (i * 8 + j));
      if (img & mask) {
        printf("%c ", '@');
      }
      else {
        printf("%c ", '.');
      }
    }
    printf("\n");
  }
  return 0;
}