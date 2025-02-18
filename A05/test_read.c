/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/21/25
 * Description: Tests the read_ppm function.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (!pixels) {
    return 1;
  }
  printf("Testing file %s: %d %d\n", "feep-raw.ppm", w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
    }
    printf("\n");
  }
  free(pixels);
  return 0;
}

