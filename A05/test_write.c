/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (!pixels) {
    printf("Problem with original image!");
    return 1;
  }
  write_ppm("test.ppm", pixels, w, h);
  free(pixels);
  struct ppm_pixel* writtenPixels = read_ppm("test.ppm", &w, &h);
  if (!writtenPixels) {
    printf("Problem with written image!");
    return 1;
  }
  printf("Testing file %s: %d %d\n", "test.ppm", w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = writtenPixels[i * w + j];
      printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
    }
    printf("\n");
  }
  free(writtenPixels);
  return 0;
}
