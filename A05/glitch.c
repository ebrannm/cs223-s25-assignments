/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 2/21/25
 * Description: Reads in a PPM file and randomly "glitches" it.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <time.h>

int main(int numArg, char** argv) {
  srand(time(NULL));
  if (numArg < 2) {
    printf("Please enter a file!");
    return 1;
  }
  char* fileName = argv[1];
  int w, h;
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
  printf("Reading %s with width %d and height %d", argv[1], w, h);
  if (!pixels) {
    return 1;
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      pixels[i * w + j].blue = pixels[i * w + j].blue << (rand() % 5);
      pixels[i * w + j].red = pixels[i * w + j].red << (rand() % 1);
      pixels[i * w + j].green = pixels[i * w + j].green << (rand() % 2);
    }
  }
  char *end = strtok(fileName, ".");
  char *newFileName = strcat(end, "-glitched");
  newFileName = strcat(newFileName, ".ppm");
  printf("%s", newFileName);
  write_ppm(newFileName, pixels, w, h);
  free(pixels);
  return 0;
}
